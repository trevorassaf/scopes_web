<?hh // strict

class ConfirmOrderMethod {

  public function __construct(
    private FetchByIdQuery<RsvdOrder> $fetchRsvdOrderQuery,
    private InsertConfirmedOrderQuery $confirmedOrderInsertQuery,
    private BatchInsertQuery<CellLabel> $cellLabelBatchInsertQuery,
    private DeleteByIdQuery $deleteByIdQuery,
    private CellLabelsTable $cellLabelsTable,
    private RsvdOrdersTable $rsvdOrdersTable
  ) {}

  public function confirm(
    UnsignedInt $rsvd_order_id,
    string $title,
    string $description,
    string $short_code,
    UnsignedInt $recording_duration,
    ImmVector<CreateCellLabelRequest> $cell_label_list
  ): ConfirmedOrder {
    try {
      // Fetch reserved order       
      $fetch_result = $this->fetchRsvdOrderQuery->fetch($rsvd_order_id);

      // Block until we fetch the reserved order 
      $rsvd_order = $fetch_result
        ->getWaitHandle()
        ->join();

      // Fail if we can't find reserved order
      if ($rsvd_order === null) {
        throw new NonextantObjectException();
      }

      // Fail if provided number of cell labels does not equal
      // numer of scopes in reserved order 
      if ($rsvd_order->getScopesCount()->getNumber() !== $cell_label_list->count()) {
        throw new InvalidCellLabelCountException(
          $rsvd_order->getScopesCount(),
          new UnsignedInt($cell_label_list->count())
        );
      }

      // Request passed checks! Insert new confirmed order...
      $confirmed_order_insert_result = $this->confirmedOrderInsertQuery->insert(
        $rsvd_order->getUserId(),
        $rsvd_order->getScopesCount(),
        $rsvd_order->getTimestampSegment()->getStart(),
        $rsvd_order->getTimestampSegment()->getEnd(),
        $title,
        $description,
        $short_code,
        $recording_duration
      );

      // Block until insert completes
      $confirmed_order = $confirmed_order_insert_result
        ->getWaitHandle()
        ->join();
      
      // Compose insert cell-labels query
      $cell_label_field_map_list = Vector{};
      $cell_number = 0;

      foreach ($cell_label_list as $cell_label_request) {
        $cell_label_field_map_list[] = ImmMap{
          $this->cellLabelsTable->getConfirmedOrderIdKey() => $confirmed_order->getId()->getNumber(),
          $this->cellLabelsTable->getLabelKey() => $cell_label_request->getLabel()->get(),
          $this->cellLabelsTable->getCellNumberKey() => $cell_number
        };

        ++$cell_number;
      } 

      // Execute insert cell-labels query
      $cell_label_insert_query_handle = $this
        ->cellLabelBatchInsertQuery->insert(
          $cell_label_field_map_list->toImmVector()
        );

      // Block until cell labels have been inserted
      // and rsvd orders have been deleted
      $cell_label_insert_query_handle
        ->getWaitHandle()
        ->join();

      // Delete rsvd order
      $delete_rsvd_order_query_handle = $this->deleteByIdQuery->delete(
        $this->rsvdOrdersTable,
        $rsvd_order->getId() 
      );

      $delete_rsvd_order_query_handle
        ->getWaitHandle()
        ->join();

      return $confirmed_order;

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }
}

<?hh // strict

class ConfirmOrderMethod {

  public function __construct(
    private FetchByIdQuery<RsvdOrder> $fetchRsvdOrderQuery,
    private InsertConfirmedOrderQuery $confirmedOrderInsertQuery,
    private BatchInsertQuery<CellLabel> $cellLabelBatchInsertQuery,
    private DeleteByIdQuery<RsvdOrder> $deleteRsvdOrderQuery,
    private CellLabelsTable $cellLabelsTable
  ) {}

  public function confirm(
    UnsignedInt $rsvd_order_id,
    string $title,
    string $description,
    string $short_code,
    UnsignedInt $recording_duration,
    ImmVector<CreateCellLabelRequest> $cell_label_list
  ): ConfirmedOrder {
    // 1. Fetch existing reserved order (ensure number
    //      of cell label requests matches scopes number)
    // 2. Insert new confirmed order
    // 3. Insert cell label requests
    // 4. Delete reserved order
    try {
      // Fetch reserved order       
      $fetch_result = $this->fetchRsvdOrderQuery->fetch(
        $rsvd_order_id
      );

      // Block until we fetch the reserved order 
      $rsvd_order = $fetch_result
        ->getWaitHandle()
        ->join();

      // Fail if user provided invalid reserved order
      if ($rsvd_order === null) {
        throw new NonextantObjectException();
      }

      // Fail if user provided incorrect cell label count
      if ($rsvd_order->getScopesCount() !== $cell_label_list->count()) {
        throw new InvalidCellLabelCountException(
          $rsvd_order->getScopesCount(),
          new UnsignedInt($cell_label_list->count())
        );
      }

      // Insert new confirmed order
      $confirmed_order_insert_result = $this->confirmedOrderInsertQuery->insert(
        $rsvd_order->getId(),
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
      
      // Insert cell labels
      $cell_label_field_map_list = Vector{};

      foreach ($cell_label_list as $cell_label_request) {
        $cell_label_field_map_list[] = ImmMap{
          $this->cellLabelsTable->getConfirmedOrderIdKey() => $confirmed_order->getId()->getNumber(),
          $this->cellLabelsTable->getLabelKey() => $cell_label_request->getLabel()->get(),
        };
      } 

      $cell_label_insert_query_handle = $this
        ->cellLabelBatchInsertQuery->insert(
          $cell_label_field_map_list->toImmVector()
        );

      // Delete rsvd order
      $delete_rsvd_order_query_handle = $this
        ->deleteRsvdOrderQuery
        ->delete(
          $rsvd_order->getId() 
        );

      // Block until cell labels have been inserted
      // and rsvd orders have been deleted
      $cell_label_insert_query_handle
        ->getWaitHandle()
        ->join();

      $delete_rsvd_order_query_handle
        ->getWaitHandle()
        ->join();

      return $confirmed_order;

    } catch (QueryException $ex) {
      throw new MethodException();
    } 
  }
}

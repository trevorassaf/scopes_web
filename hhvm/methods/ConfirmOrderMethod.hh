<?hh // strict

class ConfirmOrderMethod {

  public function __construct(
    private FetchByIdQuery<RsvdOrder> $fetchRsvdOrderQuery,
    private ConfirmedOrderInsertQuery $confirmedOrderInsertQuery,
    private BatchInsertQuery<CellLabel> $cellLabelBatchInsertQuery,
    private DeleteByIdQuery<RsvdOrder> $deleteRsvdOrderQuery,
    private CellLabelsTable $cellLabelsTable
  ) {}

  public function confirm(
    ConfirmOrderRequest $confirm_order_request
  ): void {
    // 1. Fetch existing reserved order (ensure number
    //      of cell label requests matches scopes number)
    // 2. Insert new confirmed order
    // 3. Insert cell label requests
    // 4. Delete reserved order
    try {
      // Fetch reserved order       
      $fetch_result = $this->fetchRsvdOrderQuery->fetch(
        $confirm_order_request->getRsvdOrderId()
      );

      // Block until we fetch the reserved order 
      $rsvd_order = $fetch_result
        ->getWaitHandle()
        ->join();

      // TODO handle case where no rsvd order exists
      invariant($rsvd_order !== null, "Rsvd order can't be null");

      // Insert new confirmed order
      $confirmed_order_insert_result = $this->confirmedOrderInsertQuery->insert(
        $rsvd_order->getId(),
        $rsvd_order->getScopesCount(),
        $rsvd_order->getLeaseStart(),
        $rsvd_order->getReservedMinutesCount(),
        $confirm_order_request->getTitle(),
        $confirm_order_request->getDescription(),
        $confirm_order_request->getShortCode(),
        $confirm_order_request->getRecordingDuration()
      );

      // Block until insert completes
      $confirmed_order = $confirmed_order_insert_result
        ->getWaitHandle()
        ->join();
      
      // Insert cell labels
      $cell_label_field_map_list = Vector{};
      $cell_label_list = $confirm_order_request
        ->getCellLabelRequests();

      foreach ($cell_label_list as $cell_label_request) {
        $cell_label_field_map_list[] = ImmMap{
          $this->cellLabelsTable->getConfirmedOrderIdKey() => $cell_label_request->getConfirmedOrderId()->getNumber(),
          $this->cellLabelsTable->getCellNumberKey() => $cell_label_request->getCellNumber()->getNumber(),
          $this->cellLabelsTable->getLabelKey() => $cell_label_request->getLabel(),
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

    } catch (QueryException $ex) {} 
  }
}

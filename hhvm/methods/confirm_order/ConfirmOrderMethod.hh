<?hh // strict

class ConfirmOrderMethod {

  public function __construct(
    private FetchByIdQuery<RsvdOrder> $fetchRsvdOrderQuery,
    private FetchIsUserOwnedShortCodeQuery $fetchIsUserOwnedShortCodeQuery,
    private InsertConfirmedOrderQuery $confirmedOrderInsertQuery,
    private InsertEditedVideoOrderQuery $editedVideoOrderInsertQuery,
    private BatchInsertQuery<CellLabel> $cellLabelBatchInsertQuery,
    private DeleteByIdQuery $deleteByIdQuery,
    private CellLabelsTable $cellLabelsTable,
    private RsvdOrdersTable $rsvdOrdersTable
  ) {}

  public function confirm(
    CreateConfirmOrderRequest $create_confirm_order_request
  ): ConfirmedOrder {
    try {
      // Fetch reserved order       
      $fetch_result = $this->fetchRsvdOrderQuery->fetch(
        $create_confirm_order_request->getReserveOrderId()
      );

      // Block until we fetch the reserved order 
      $rsvd_order = $fetch_result
        ->getWaitHandle()
        ->join();

      // Fail if we can't find reserved order
      if ($rsvd_order === null) {
        throw new NonextantObjectException();
      }

      // Fail if short code does not belong to this user
      $short_code_id = $create_confirm_order_request->getShortCodeId();

      $fetch_is_user_owned_short_code_handle = $this->fetchIsUserOwnedShortCodeQuery->fetch(
        $rsvd_order->getUserId(),
        $short_code_id
      );

      $is_user_owned_short_code = $fetch_is_user_owned_short_code_handle
        ->getWaitHandle()
        ->join();

      if (!$is_user_owned_short_code) {
        throw new UnownedShortCodeException(
          $rsvd_order->getUserId(),
          $short_code_id
        );
      }

      // Request passed checks! Insert new confirmed order...
      $confirmed_order_insert_result = $this->confirmedOrderInsertQuery->insert(
        $rsvd_order->getUserId(),
        $rsvd_order->getScopesCount(),
        $rsvd_order->getTimestampSegment()->getStart(),
        $rsvd_order->getTimestampSegment()->getEnd(),
        $create_confirm_order_request->getTitle(),
        $create_confirm_order_request->getDescription(),
        $short_code_id,
        new UnsignedFloat(0.0),
        $create_confirm_order_request->getTimeOrderMade()
      );

      // Block until insert completes
      $confirmed_order = $confirmed_order_insert_result
        ->getWaitHandle()
        ->join();

      // Handle edited-video-order request, if provided
      $edited_video_order_request = $create_confirm_order_request->getCreateEditedVideoOrderRequest();
      if ($edited_video_order_request !== null) {
        $this->handleCreateEditedVideoOrderRequest(
          $confirmed_order,
          $edited_video_order_request
        );
      }

      // Delete reserved order
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

  private function handleCreateEditedVideoOrderRequest(
    ConfirmedOrder $confirmed_order,
    CreateEditedVideoOrderRequest $edited_video_order_request
  ): void {
    // Check the number of cell-labels. Fail if cell-label count doesn't match
    // scopes count in confirmed-order
    $scopes_count = $confirmed_order->getScopesCount();
    $create_cell_label_request_list = $edited_video_order_request->getCellLabels();
    $cell_labels_count = $create_cell_label_request_list->count();

    if ($scopes_count->getNumber() !== $cell_labels_count) {
      throw new InvalidCellLabelCountException(
        $scopes_count,
        new UnsignedInt($cell_labels_count)
      );
    }

    // Insert edited-video-order into db
    $edited_video_order_insert_result = $this->editedVideoOrderInsertQuery->insert(
      $confirmed_order->getId(),
      $edited_video_order_request->getRecordingDurationMinutes()
    );      

    // Block until edited-video-order create query finishes
    $edited_video_order = $edited_video_order_insert_result
      ->getWaitHandle()
      ->join();

    // Insert cell-labels into db
    $cell_label_field_map_list = Vector{};
    $cell_number = 0;
    $edited_video_order_id = $edited_video_order->getId()->getNumber();

    foreach ($create_cell_label_request_list as $create_cell_label_request) {
      $cell_label_field_map_list[] = ImmMap{
        $this->cellLabelsTable->getEditedVideoOrderIdKey() => $edited_video_order_id,
        $this->cellLabelsTable->getLabelKey() => $create_cell_label_request->getLabel(),
        $this->cellLabelsTable->getCellNumberKey() => $cell_number
      };

      ++$cell_number;
    } 

    // Execute create cell-label query
    $cell_label_insert_query_handle = $this->cellLabelBatchInsertQuery->insert(
      $cell_label_field_map_list->toImmVector()
    );

    // Block until create cell-label query finishes
    $cell_label_insert_query_handle
      ->getWaitHandle()
      ->join();
  }
}

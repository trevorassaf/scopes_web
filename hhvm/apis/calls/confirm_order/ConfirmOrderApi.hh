<?hh // strict

class ConfirmOrderApi extends Api<ConfirmOrderApiRequest> {

  public function __construct(
    RequestFactory<ConfirmOrderApiRequest> $request_factory,
    private TimestampBuilder $timestampBuilder,
    private ConfirmOrderMethod $confirmOrderMethod,
    private Logger $logger
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    ConfirmOrderApiRequest $request
  ): ApiResult {
    // Log confirm order call
    $this->logger->info("Confirm order api call...");

    // Unpack api-request into internal request object
    $edited_video_order = null;

    // Translate edited-video-order api-request to internal request object 
    $edited_video_order_api_request = $request->getEditedVideoOrderApiRequest();
    $create_edited_video_order_request = null;

    if ($edited_video_order_api_request !== null) {
      // Translate cell-label api-requests to internal request objects
      $cell_label_api_requests = $edited_video_order_api_request->getCellLabels()->get();
      $create_cell_label_requests = Vector{};

      foreach ($cell_label_api_requests as $cell_label) {
        $create_cell_label_requests[] = new CreateCellLabelRequest(
          $cell_label->getLabel()->get()
        );
      }

      $create_edited_video_order_request = new CreateEditedVideoOrderRequest(
        $edited_video_order_api_request->getRecordingDurationMinutes()->get(),
        $create_cell_label_requests->toImmVector()
      );
    }

    // Translate create-confirm-order api-request to internal request object
    $create_confirm_order_request = new CreateConfirmOrderRequest(
      $request->getRsvdOrderId()->get(),
      $this->timestampBuilder->now(),
      $request->getTitle()->get(),
      $request->getDescription()->get(),
      $request->getShortCodeId()->get(),
      $create_edited_video_order_request
    );

    try {
      // Unpack edited-video-order-request into internal object
      $confirmed_order = $this->confirmOrderMethod->confirm(
        $create_confirm_order_request
      );

      // Log confirm order request completed
      $this->logger->info("Confirm order request completed!");

      return new ConfirmOrderApiResult($confirmed_order->getId());

    } catch (NonextantObjectException $ex) {
      $this->logger->info("Reserved order does not exist!");
      return new FailedConfirmOrderApiResult(
        FailedConfirmOrderApiResultType::NONEXTANT_RESERVED_ORDER
      );

    } catch (InvalidCellLabelCountException $ex) {
      $this->logger->info("Invalid cell label count! " . $ex->getMessage());
      return new FailedConfirmOrderApiResult(
        FailedConfirmOrderApiResultType::INVALID_CELL_LABEL_COUNT
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::CONFIRM_ORDER;
  }
}

<?hh // strict

class ConfirmedOrder implements Model {
  
  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $userId,
    private UnsignedInt $scopesCount,
    private TimestampSegment $timestampSegment,
    private ?string $title,
    private ?string $description,
    private UnsignedInt $shortCodeId,
    private UnsignedFloat $price,
    private Timestamp $timeOrdered,
    private UnsignedInt $orderStatusId,
    private UnsignedInt $paymentStatusId
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getUserId(): UnsignedInt {
    return $this->userId;
  }

  public function getScopesCount(): UnsignedInt {
    return $this->scopesCount;
  }

  public function getTimestampSegment(): TimestampSegment {
    return $this->timestampSegment;
  }

  public function getTitle(): ?string {
    return $this->title;
  }

  public function getDescription(): ?string {
    return $this->description;
  }

  public function getShortCodeId(): UnsignedInt {
    return $this->shortCodeId;
  }

  public function getPrice(): UnsignedFloat {
    return $this->price;
  }

  public function getTimeOrdered(): Timestamp {
    return $this->timeOrdered;
  }

  public function getOrderStatusId(): UnsignedInt {
    return $this->orderStatusId;
  }

  public function getPaymentStatusId(): UnsignedInt {
    return $this->paymentStatusId;
  }
}

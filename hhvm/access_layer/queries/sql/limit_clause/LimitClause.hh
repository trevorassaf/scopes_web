<?hh // strict

class LimitClause {

  public function __construct(
    private ?UnsignedInt $maxRowCount,
    private ?UnsignedInt $offset
  ) {
    invariant($this->maxRowCount != null || $this->offset == null, "Limit clause can't have only an offset!");
  }

  public function serialize(): string {
    if ($this->maxRowCount == null && $this->offset == null) {
      return "";
    }

    $limit_query_str = "LIMIT " . $this->maxRowCount->getNumber();
    if ($this->offset != null) {
      $limit_query_str .= ", " . $this->offset->getNumber();
    }

    return $limit_query_str;
  }
}

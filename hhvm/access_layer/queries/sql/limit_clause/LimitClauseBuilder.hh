<?hh // strict

class LimitClauseBuilder {

  private ?UnsignedInt $maxRowCount;
  private ?UnsignedInt $offset;

  public function setMaxRowCount(UnsignedInt $max_row_count): this {
    $this->maxRowsCount = $max_row_count;
    return $this;
  }

  public function setOffset(UnsignedInt $offset): this {
    $this->offset = $offset;
    return $this;
  }

  public function build(): LimitClause {
    invariant();
    return new LimitClause(
      $this->maxRowCount,
      $this->offset
    );
  }
}

<?hh // strict

class PriorityQueue<T> {

  const int DEFAULT_STARTING_SIZE = 10;

  private Vector<T> $heap;

  public function __construct(
    private Comparator<T> $comparator,
    private UnsignedInt $startingSize = new UnsignedInt(self::DEFAULT_STARTING_SIZE)
  ) {
    $this->heap = Vector{};
    $this->heap->reserve($this->startingSize->getNumber());
  }

  public function push(T $new_element): this {
    // Add element to end of binary heap array
    $this->heap[] = $new_element;
    
    // Restore heap property
    $this->fixUp($this->getCount() - 1);
    
    return $this;
  }

  public function pop(): T {
    invariant(!$this->isEmpty(), "Can't pop if empty!");
    $popped_element = $this->peek();

    // Overwrite root with right-most leaf
    $this->heap[0] = $this->pop();

    // Restore heap property
    $this->fixDown(0);

    return $popped_element;
  }

  /**
   * fixUp()
   * - Propagate the element at index 'idx' up the binary tree.
   */
  private function fixUp(int $idx): void {
    $element = $this->heap[$idx];
    $parent_idx = (int)(($idx - 1) / 2);

    while ($idx != 0 && $this->comparator->compare($this->heap[$idx], $this->heap[$parent_idx]) > 0) {
      // Swap elements
      $this->heap[$idx] = $this->heap[$parent_idx];
      $this->heap[$parent_idx] = $element;

      // Advance indices 
      $idx = $parent_idx;
      $parent_idx = (int)(($idx - 1)/ 2);
    }
  }

 /**
  * fixDown()
  * - Propagate the element at index 'idx' down the binary tree.
  */ 
  private function fixDown(int $idx): void {
    $element = $this->heap[$idx];

    while ($idx * 2 + 1 < $this->getCount()) {
      $left_idx = $idx * 2 + 1;
      
      // Swap left child if necessary
      if ($this->comparator->compare($this->heap[$idx], $this->heap[$left_idx]) < 0) {
        $this->heap[$idx] = $this->heap[$left_idx];
        $this->heap[$left_idx] = $element;
        $idx = $left_idx;
        continue;
      }

      // Make sure right child exists! Finish, otherwise...
      $right_idx = $idx * 2 + 2;
      if ($right_idx > $this->getCount()) {
        break;
      }

      // Swap right child if necessary
      if ($this->comparator->compare($this->heap[$idx], $this->heap[$right_idx]) < 0) {
        $this->heap[$idx] = $this->heap[$right_idx];
        $this->heap[$right_idx] = $element;
        $idx = $right_idx;
        continue;
      }

      // Finish because the element is greater than both of its children!
      break;
    }
  }

  public function peek(): T {
    invariant(!$this->isEmpty(), "Can't peek if empty!");
    return $this->heap[0];
  }

  public function isEmpty(): bool {
    return $this->heap->isEmpty();
  }

  public function getCount(): int {
    return $this->heap->count();
  }
}

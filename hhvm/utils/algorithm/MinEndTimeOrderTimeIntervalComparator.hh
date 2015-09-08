<?hh // strict

class MinEndTimeOrderTimeIntervalComparator implements Comparator<OrderTimeInterval> {

  public function compare(OrderTimeInterval $left, OrderTimeInterval $right): int {
    if ($left->getEndTime()->isBefore($right))  {
      return 1;
    } 
    
    if ($left->getEndTime()->isAfter($right)) {
      return -1;
    } 

    return 0;
  }
}

<?hh // strict

class MinEndTimeOrderTimestampIntervalComparator implements Comparator<OrderTimestampInterval> {

  public function compare(OrderTimestampInterval $left, OrderTimestampInterval $right): int {
    if ($left->getTimestampInterval()->getEndTime()->isBefore($right))  {
      return 1;
    } 
    
    if ($left->getTimestampInterval()->getEndTime()->isAfter($right)) {
      return -1;
    } 

    return 0;
  }
}

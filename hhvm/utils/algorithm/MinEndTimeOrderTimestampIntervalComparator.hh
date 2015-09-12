<?hh // strict

class MinEndTimeOrderTimestampIntervalComparator implements Comparator<OrderTimestampInterval> {

  public function compare(OrderTimestampInterval $left, OrderTimestampInterval $right): int {
    if ($left->getTimestampInterval()->getEnd()->isBefore($right->getTimestampInterval()->getEnd()))  {
      return 1;
    } 
    
    if ($left->getTimestampInterval()->getEnd()->isAfter($right->getTimestampInterval()->getEnd())) {
      return -1;
    } 

    return 0;
  }
}

<?hh // strict

class MinEndTimeOrderTimestampSegmentComparator implements Comparator<OrderTimestampSegment> {

  public function compare(OrderTimestampSegment $left, OrderTimestampSegment $right): int {
    if ($left->getTimestampSegment()->getEnd()->isBefore($right->getTimestampSegment()->getEnd()))  {
      return 1;
    } 
    
    if ($left->getTimestampSegment()->getEnd()->isAfter($right->getTimestampSegment()->getEnd())) {
      return -1;
    } 

    return 0;
  }
}

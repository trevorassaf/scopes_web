<?hh // strict

interface Comparator<T> {

  /**
   * compare()
   * @return -1 : 'left' < 'right',
   *          0 : 'left' == 'right',
   *         +1 : 'left' > 'right'
   */
  public function compare(T $left, T $right): int;

}

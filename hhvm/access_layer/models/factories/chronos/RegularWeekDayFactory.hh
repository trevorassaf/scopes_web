<?hh // strict

class RegularWeekDayFactory extends ConcreteModelFactory<RegularWeekDay> {

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): RegularWeekDay {
    return new RegularWeekDay($id);
  }
}

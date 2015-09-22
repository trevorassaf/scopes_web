<?hh // strict

interface RequestFactory<+Trequest> {

  public function make(ImmMap<string, mixed> $raw_field_map): Trequest;
}

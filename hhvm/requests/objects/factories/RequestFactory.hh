<?hh // strict

interface RequestFactory<Trequest> {

  public function get(ImmMap<string, mixed> $raw_field_map): Trequest;
}

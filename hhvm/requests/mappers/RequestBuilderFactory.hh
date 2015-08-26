<?hh // strict

interface RequestBuilderFactory<Trequest> {

  public function get(): RequestBuilder<Trequest>;
}

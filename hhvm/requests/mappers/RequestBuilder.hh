<?hh // strict

/**
 * RequestBuilder: directs mapping of request field maps to request objects.
 * @throw: RequestBuilderException
 */
interface RequestBuilder<Trequest> {

  public function isValidKey(string $key): bool;
  public function bind(string $key, mixed $value): this;
  public function build(): Trequest;
}

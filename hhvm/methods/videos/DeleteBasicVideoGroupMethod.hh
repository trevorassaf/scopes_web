<?hh // strict

class DeleteBasicVideoGroupMethod {

  public function __construct(
    private DeleteBasicVideoMethod $deleteBasicVideoMethod,
    private FetchQuery<BasicVideo> $fetchBasicVideosQuery
  ) {}

  public function delete(
    UnsignedInt $confirmed_order
  ): void {
    
  }
}

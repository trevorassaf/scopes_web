<?hh // strict

class AliasableFromTerm implements FromTerm {

  public function __construct(
    private string $originalFromTermString,
    private ?string $alias
  ) {}

  public function 

  public function serialize(): string {
    return ($this->alias == null)
      ? $this->originalFromTermString
      : $this->originalFromTermString . " " . self::ALIAS_TOKEN . " " . $this->alias;
  }
}

<?hh // strict

class DateToDayOfTheWeekConverterLazyLoader extends LazyLoader<DateToDayOfTheWeekConverter> {

  public function __construct(
    private LazyLoader<DateSerializer> $dateSerializerLoader
  ) {} 

  protected function make(): DateToDayOfTheWeekConverter {
    return new DateToDayOfTheWeekConverter(
      $this->dateSerializerLoader->load()
    );
  }
}

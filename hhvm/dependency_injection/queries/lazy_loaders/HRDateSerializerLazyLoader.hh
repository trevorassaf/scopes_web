<?hh // strict

class HRDateSerializerLazyLoader extends LazyLoader<HRDateSerializer> {

  protected function make(): HRDateSerializer {
    return new HRDateSerializer();
  }
}

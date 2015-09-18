<?hh // strict

class HRTimeSerializerLazyLoader extends LazyLoader<HRTimeSerializer> {

  protected function make(): HRTimeSerializer {
    return new HRTimeSerializer();
  }
}

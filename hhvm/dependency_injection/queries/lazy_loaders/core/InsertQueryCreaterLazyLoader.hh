<?hh // strict

class InsertQueryCreaterLazyLoader extends LazyLoader<InsertQueryCreater> {

  protected function make(): InsertQueryCreater {
    return new InsertQueryCreater();
  }
}

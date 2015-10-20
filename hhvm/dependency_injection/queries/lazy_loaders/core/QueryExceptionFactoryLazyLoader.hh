<?hh // strict

class QueryExceptionFactoryLazyLoader extends LazyLoader<QueryExceptionFactory> {

  protected function make(): QueryExceptionFactory {
    return new QueryExceptionFactory();
  }
}

<?hh // strict

class VideoMimeTypesTableLazyLoader extends LazyLoader<VideoMimeTypesTable> {
  
  protected function make(): VideoMimeTypesTable {
    return new VideoMimeTypesTable();
  } 
}

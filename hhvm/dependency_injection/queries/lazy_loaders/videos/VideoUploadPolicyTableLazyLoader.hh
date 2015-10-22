<?hh // strict

class VideoUploadPolicyTableLazyLoader extends LazyLoader<VideoUploadPolicyTable> {

  protected function make(): VideoUploadPolicyTable {
    return new VideoUploadPolicyTable();
  }
}

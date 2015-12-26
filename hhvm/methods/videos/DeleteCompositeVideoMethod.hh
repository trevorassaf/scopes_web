<?hh // strict

class DeleteCompositeVideoMethod {

  public function __construct(
    private FetchByIdQuery<CompositeVideo> $fetchCompositeVideoByIdQuery,
    private DeleteByIdQuery $deleteByIdQuery,
    private CompositeVideoTable $compositeVideoTable,
    private MakeCompositeVideoPathMethod $makeCompositeVideoPathMethod,
    private DeleteFileMethod $deleteFileMethod
  ) {}

  public function delete(
    VideoUploadPolicy $video_upload_policy,
    UnsignedInt $composite_video_id
  ): void {
    // Fetch composite video
    $fetch_composite_video_handle = $this->fetchCompositeVideoByIdQuery->fetch(
      $composite_video_id
    ); 

    $composite_video = $fetch_composite_video_handle
      ->getWaitHandle()
      ->join();

    if ($composite_video === null) {
      throw new NonextantObjectException();
    }

    $this->deleteWithCompositeVideo(
      $video_upload_policy,
      $composite_video
    );
  }

  public function deleteWithCompositeVideo(
    VideoUploadPolicy $video_upload_policy,
    CompositeVideo $composite_video
  ): void {
    // Delete composite video record
    $delete_handle = $this->deleteByIdQuery->delete(
      $this->compositeVideoTable,
      $composite_video->getId()
    );

    $delete_handle->getWaitHandle()->join();

    // Delete composite video file
    $composite_video_path = $this->makeCompositeVideoPathMethod->makePathWithPolicy(
      $composite_video,
      $video_upload_policy
    );

    $this->deleteFileMethod->delete($composite_video_path);
  }
}

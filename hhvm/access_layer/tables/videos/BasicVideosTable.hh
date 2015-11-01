<?hh // strict

class BasicVideosTable extends Table {

  const string TABLE_NAME = "BasicVideos";
  const string COMPLETED_BASIC_VIDEO_SET_ID_KEY = "completedBasicVideoSetId";
  const string SCOPE_INDEX_KEY = "scopeIndex";
  const string TITLE_KEY = "title";
  const string DURATION_KEY = "duration";
  const string DESCRIPTION_KEY = "description";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getCompletedBasicVideoSetIdKey(): string {
    return self::COMPLETED_BASIC_VIDEO_SET_ID_KEY;
  }

  public function getScopeIndexKey(): string {
    return self::SCOPE_INDEX_KEY;
  }

  public function getTitleKey(): string {
    return self::TITLE_KEY;
  }

  public function getVideoDurationKey(): string {
    return self::DURATION_KEY;
  }

  public function getDescriptionKey(): string {
    return self::DESCRIPTION_KEY;
  }
}

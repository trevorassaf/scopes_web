-- DELETE TABLES SCRIPT --

use Scopes;

-- Model tables
-- Video
drop table BasicVideoDownloadReceipts;
drop table BasicVideos;
drop table CompletedBasicVideoSet;
drop table CompletedEditedVideo;
drop table CompositeVideos;
drop table VideoEditingPricePolicy;
drop table VideoStoragePricePolicy;
drop table VideoUploadPolicy;
drop table VideoMimeTypes;

-- Available dates/times
drop table IrregularDates;
drop table IrregularTimes;
drop table RegularWeekDays;
drop table RegularTimes;
drop table RegularWeekDayRegularTimeEdges;

-- Confirmed orders
drop table ConfirmedOrderTransactions;
drop table ConfirmedOrderFailedTransactions;

drop table CellLabels;
drop table EditedVideoOrders;

drop table CompletedOrders;
drop table ConfirmedOrders;

drop table OrderConfiguration;

-- Reserved orders
drop table RsvdOrders;
drop table ReservedOrderPolicy;

-- Short Codes
drop table ShortCodeValidationChecks;
drop table ShortCodes;

-- Users
drop table UserUserPrivilegeEdges;
drop table UserPrivileges;
drop table Users;

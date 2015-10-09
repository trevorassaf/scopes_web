-- DELETE TABLES SCRIPT --

use Scopes;

-- Model tables
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
drop table CompositeVideos;
drop table EditedVideoOrders;

drop table BasicVideos;
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

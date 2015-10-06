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
drop table CellLabels;

drop table ConfirmedOrderTransactions;
drop table ConfirmedOrderFailedTransactions;
drop table ConfirmedOrderShortCodeValidationChecks;

drop table ConfirmedOrders;
drop table ShortCodes;
drop table OrderConfiguration;

-- Reserved orders
drop table RsvdOrders;
drop table ReservedOrderPolicy;

-- Users
drop table UserUserPrivilegeEdges;
drop table UserPrivileges;
drop table Users;

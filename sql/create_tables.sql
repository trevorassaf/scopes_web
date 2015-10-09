-- CREATE TABLES SCRIPT --
-- Users
source create_tables/users.sql
source create_tables/user_privileges.sql
source create_tables/user_user_privilege_edges.sql

-- Reserved orders
source create_tables/rsvd_order_policy.sql

source create_tables/rsvd_orders.sql

-- Confirmed orders
source create_tables/order_configuration.sql

source create_tables/short_codes.sql
source create_tables/confirmed_orders.sql

source create_tables/short_code_validation_checks.sql
source create_tables/confirmed_order_transactions.sql
source create_tables/failed_confirmed_order_transactions.sql

source create_tables/cell_labels.sql

-- Available dates/times
source create_tables/irregular_dates.sql
source create_tables/irregular_times.sql

source create_tables/regular_times.sql
source create_tables/regular_week_days.sql
source create_tables/regular_week_day_regular_time_edges.sql

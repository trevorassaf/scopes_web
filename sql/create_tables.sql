-- CREATE TABLES SCRIPT --
-- Users
source create_tables/users/users.sql
source create_tables/users/user_privileges.sql
source create_tables/users/user_user_privilege_edges.sql

-- Short Codes
source create_tables/short_codes/short_codes.sql
source create_tables/short_codes/short_code_validation_checks.sql

-- Order Payment Policies
source create_tables/payments/gen0/gen0_order_price_policies.sql

-- Reserved orders
source create_tables/orders/rsvd_order_policy.sql
source create_tables/orders/rsvd_orders.sql
source create_tables/orders/reserved_order_scope_mappings.sql

-- Confirmed orders
source create_tables/orders/order_configuration.sql

source create_tables/orders/confirmed_orders.sql
source create_tables/orders/confirmed_order_scope_mappings.sql
source create_tables/orders/completed_orders.sql

source create_tables/orders/edited_video_orders.sql
source create_tables/orders/cell_labels.sql

source create_tables/orders/confirmed_order_transactions.sql
source create_tables/orders/failed_confirmed_order_transactions.sql

-- Available dates/times
source create_tables/chronos/irregular_dates.sql
source create_tables/chronos/irregular_times.sql

source create_tables/chronos/regular_times.sql
source create_tables/chronos/regular_week_days.sql
source create_tables/chronos/regular_week_day_regular_time_edges.sql

-- Videos
source create_tables/videos/video_mime_types.sql
source create_tables/videos/completed_basic_video_set.sql
source create_tables/videos/basic_videos.sql
source create_tables/videos/basic_video_download_receipts.sql
source create_tables/videos/completed_edited_video.sql
source create_tables/videos/composite_videos.sql
source create_tables/videos/video_editing_price_policy.sql
source create_tables/videos/video_storage_price_policy.sql
source create_tables/videos/video_upload_policy.sql

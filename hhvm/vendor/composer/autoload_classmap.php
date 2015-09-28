<?php

// autoload_classmap.php @generated by Composer

$vendorDir = dirname(dirname(__FILE__));
$baseDir = dirname($vendorDir);

return array(
    'AndWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/logical/AndWhereClause.hh',
    'Api' => $baseDir . '/apis/Api.hh',
    'ApiFieldType' => $baseDir . '/apis/ApiFieldType.hh',
    'ApiInjector' => $baseDir . '/dependency_injection/apis/ApiInjector.hh',
    'ApiInjectorFactory' => $baseDir . '/dependency_injection/apis/ApiInjectorFactory.hh',
    'ApiRequestDeserializer' => $baseDir . '/apis/deserializers/ApiRequestDeserializer.hh',
    'ApiResult' => $baseDir . '/apis/results/ApiResult.hh',
    'ApiResultSerializer' => $baseDir . '/apis/serializers/ApiResultSerializer.hh',
    'ApiRouter' => $baseDir . '/apis/router/ApiRouter.hh',
    'ApiRouterFactory' => $baseDir . '/apis/router/ApiRouterFactory.hh',
    'ApiRunner' => $baseDir . '/apis/runners/ApiRunner.hh',
    'ApiRunnerFactory' => $baseDir . '/apis/runners/ApiRunnerFactory.hh',
    'ApiType' => $baseDir . '/apis/ApiType.hh',
    'ApiTypeFieldConverter' => $baseDir . '/requests/fields/converters/ApiTypeFieldConverter.hh',
    'ApiTypeRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/ApiTypeRequestFieldFactoryBuilder.hh',
    'AscOrderByTerm' => $baseDir . '/access_layer/queries/sql/order_by_clause/AscOrderByTerm.hh',
    'AsyncMysqlConnectionFactory' => $baseDir . '/access_layer/db/async_mysql/AsyncMysqlConnectionFactory.hh',
    'AsyncMysqlConnectionLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/AsyncMysqlConnectionLazyLoader.hh',
    'BatchInsertQuery' => $baseDir . '/access_layer/queries/insert/BatchInsertQuery.hh',
    'BoolFieldConverter' => $baseDir . '/requests/fields/converters/BoolFieldConverter.hh',
    'BoolRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/BoolRequestFieldFactoryBuilder.hh',
    'CellLabel' => $baseDir . '/access_layer/models/objects/CellLabel.hh',
    'CellLabelFactory' => $baseDir . '/access_layer/models/factories/CellLabelFactory.hh',
    'CellLabelModelFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/CellLabelModelFactoryLazyLoader.hh',
    'CellLabelRequest' => $baseDir . '/requests/objects/models/cell_label/CreateCellLabelRequest.hh',
    'CellLabelRequestBuilder' => $baseDir . '/requests/objects/models/cell_label/CreateCellLabelRequest.hh',
    'CellLabelRequestFactory' => $baseDir . '/requests/objects/factories/cell_labels/CellLabelRequestFactory.hh',
    'CellLabelVectorRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/CellLabelVectorRequestFieldFactoryBuilder.hh',
    'CellLabelsTable' => $baseDir . '/access_layer/tables/CellLabelsTable.hh',
    'CellLabelsTableLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/CellLabelsTableLazyLoader.hh',
    'Comparator' => $baseDir . '/utils/algorithm/Comparator.hh',
    'ComparisonWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/ComparisonWhereClause.hh',
    'ConcreteModelFactory' => $baseDir . '/access_layer/models/factories/ConcreteModelFactory.hh',
    'ConfirmOrderApi' => $baseDir . '/apis/calls/confirm_order/ConfirmOrderApi.hh',
    'ConfirmOrderApiResult' => $baseDir . '/apis/results/confirm_order/ConfirmOrderApiResult.hh',
    'ConfirmOrderMethod' => $baseDir . '/methods/confirm_order/ConfirmOrderMethod.hh',
    'ConfirmOrderRequest' => $baseDir . '/requests/objects/models/confirmed_orders/ConfirmOrderRequest.hh',
    'ConfirmOrderRequestBuilder' => $baseDir . '/requests/objects/models/confirmed_orders/ConfirmOrderRequest.hh',
    'ConfirmOrderRequestFactory' => $baseDir . '/requests/objects/factories/confirmed_orders/ConfirmOrderRequestFactory.hh',
    'ConfirmOrderRequestFactoryLazyLoader' => $baseDir . '/dependency_injection/apis/lazy_loaders/ConfirmOrderRequestFactoryLazyLoader.hh',
    'ConfirmOrderWithCellLabelResultStruct' => $baseDir . '/apis/results/confirm_order/ConfirmOrderWithCellLabelResultStruct.hh',
    'ConfirmedOrder' => $baseDir . '/access_layer/models/objects/ConfirmedOrder.hh',
    'ConfirmedOrderFactory' => $baseDir . '/access_layer/models/factories/ConfirmedOrderFactory.hh',
    'ConfirmedOrderModelFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/ConfirmedOrderModelFactoryLazyLoader.hh',
    'ConfirmedOrderWithCellLabels' => $baseDir . '/access_layer/models/objects/ConfirmedOrderWithCellLabels.hh',
    'ConfirmedOrdersTable' => $baseDir . '/access_layer/tables/ConfirmedOrdersTable.hh',
    'ConfirmedOrdersTableLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/ConfirmedOrdersTableLazyLoader.hh',
    'ConflictingReservedOrderRequestException' => $baseDir . '/methods/exceptions/ConflictingReservedOrderRequestException.hh',
    'ConnectionConfig' => $baseDir . '/access_layer/db/async_mysql/ConnectionConfig.hh',
    'ConnectionConfigBuilder' => $baseDir . '/access_layer/db/async_mysql/ConnectionConfigBuilder.hh',
    'ConstraintMapToConjunctiveWhereClauseTranslator' => $baseDir . '/access_layer/queries/util/ConstraintMapToConjunctiveWhereClauseTranslator.hh',
    'ConstraintMapToConjunctiveWhereClauseTranslatorLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/ConstraintMapToConjunctiveWhereClauseTranslatorLazyLoader.hh',
    'CreateCellLabelRequest' => $baseDir . '/requests/objects/models/cell_label/CellLabelRequest.hh',
    'CreateCellLabelRequestBuilder' => $baseDir . '/requests/objects/models/cell_label/CellLabelRequest.hh',
    'CreateCellLabelRequestFactory' => $baseDir . '/requests/objects/factories/cell_labels/CreateCellLabelRequestFactory.hh',
    'CreateCellLabelVectorRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/CreateCellLabelVectorRequestFieldFactoryBuilder.hh',
    'CreateIrregularDateMethod' => $baseDir . '/methods/chronos/CreateIrregularDateMethod.hh',
    'CreateIrregularTimeMethod' => $baseDir . '/methods/chronos/CreateIrregularTimeMethod.hh',
    'CreateRegularTimeMethod' => $baseDir . '/methods/chronos/CreateRegularTimeMethod.hh',
    'CreateRegularWeekDayMethod' => $baseDir . '/methods/chronos/CreateRegularWeekDayMethod.hh',
    'CreateRegularWeekDayRegularTimeEdgeMethod' => $baseDir . '/methods/chronos/CreateRegularWeekDayRegularTimeEdgeMethod.hh',
    'CreateReservedOrderPolicyMethod' => $baseDir . '/methods/rsvd_orders/CreateReservedOrderPolicyMethod.hh',
    'CreateUserApi' => $baseDir . '/apis/calls/create_user/CreateUserApi.hh',
    'CreateUserApiFailureType' => $baseDir . '/apis/results/create_user/CreateUserApiFailureType.hh',
    'CreateUserApiResult' => $baseDir . '/apis/results/create_user/CreateUserApiResult.hh',
    'CreateUserDuplicateEmailException' => $baseDir . '/methods/user/exceptions/CreateUserDuplicateEmailException.hh',
    'CreateUserMethod' => $baseDir . '/methods/user/CreateUserMethod.hh',
    'CreateUserRequest' => $baseDir . '/requests/objects/models/users/CreateUserRequest.hh',
    'CreateUserRequestBuilder' => $baseDir . '/requests/objects/models/users/CreateUserRequest.hh',
    'CreateUserRequestFactory' => $baseDir . '/requests/objects/factories/users/CreateUserRequestFactory.hh',
    'CreateUserRequestFactoryLazyLoader' => $baseDir . '/dependency_injection/apis/lazy_loaders/CreateUserRequestFactoryLazyLoader.hh',
    'Date' => $baseDir . '/utils/data_types/chronos/date/objects/Date.hh',
    'DateBuilder' => $baseDir . '/utils/data_types/chronos/date/objects/DateBuilder.hh',
    'DateSegment' => $baseDir . '/utils/data_types/chronos/date/objects/DateSegment.hh',
    'DateSegmentExpander' => $baseDir . '/utils/data_types/chronos/date/expanders/DateSegmentExpander.hh',
    'DateSerializer' => $baseDir . '/utils/data_types/chronos/date/serializers/DateSerializer.hh',
    'DateToDayOfTheWeekConverter' => $baseDir . '/utils/data_types/chronos/date/converters/DateToDayOfTheWeekConverter.hh',
    'DateToDayOfTheWeekConverterLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/DateToDayOfTheWeekConverterLazyLoader.hh',
    'Day' => $baseDir . '/utils/data_types/chronos/date/objects/Day.hh',
    'DayOfTheWeekType' => $baseDir . '/utils/data_types/chronos/date/objects/DayOfTheWeekType.hh',
    'DbErrorType' => $baseDir . '/access_layer/db/exception/DbErrorType.hh',
    'DbException' => $baseDir . '/access_layer/db/exception/DbException.hh',
    'DebugApiRunnerFactory' => $baseDir . '/apis/runners/DebugApiRunnerFactory.hh',
    'DeleteByIdQuery' => $baseDir . '/access_layer/queries/deletes/DeleteByIdQuery.hh',
    'DeleteCellLabelApi' => $baseDir . '/apis/calls/cell_label/DeleteCellLabelApi.hh',
    'DeleteCellLabelMethod' => $baseDir . '/methods/cell_label/DeleteCellLabelMethod.hh',
    'DeleteCellLabelRequest' => $baseDir . '/requests/objects/models/cell_label/DeleteCellLabelRequest.hh',
    'DeleteCellLabelRequestBuilder' => $baseDir . '/requests/objects/models/cell_label/DeleteCellLabelRequest.hh',
    'DeleteCellLabelRequestFactory' => $baseDir . '/requests/objects/factories/cell_labels/DeleteCellLabelRequestFactory.hh',
    'DeleteCellLabelRequestFactoryLazyLoader' => $baseDir . '/dependency_injection/apis/lazy_loaders/DeleteCellLabelRequestFactoryLazyLoader.hh',
    'DeleteConfirmedOrderApi' => $baseDir . '/apis/calls/confirm_order/DeleteConfirmedOrderApi.hh',
    'DeleteConfirmedOrderMethod' => $baseDir . '/methods/confirm_order/DeleteConfirmedOrderMethod.hh',
    'DeleteConfirmedOrderRequest' => $baseDir . '/requests/objects/models/confirmed_orders/DeleteConfirmedOrderRequest.hh',
    'DeleteConfirmedOrderRequestBuilder' => $baseDir . '/requests/objects/models/confirmed_orders/DeleteConfirmedOrderRequest.hh',
    'DeleteConfirmedOrderRequestFactory' => $baseDir . '/requests/objects/factories/confirmed_orders/DeleteConfirmedOrderRequestFactory.hh',
    'DeleteConfirmedOrderRequestFactoryLazyLoader' => $baseDir . '/dependency_injection/apis/lazy_loaders/DeleteConfirmedOrderRequestFactoryLazyLoader.hh',
    'DeleteQuery' => $baseDir . '/access_layer/queries/deletes/DeleteQuery.hh',
    'DeleteReservedOrderApi' => $baseDir . '/apis/calls/reserve_order/DeleteReservedOrderApi.hh',
    'DeleteReservedOrderMethod' => $baseDir . '/methods/rsvd_orders/DeleteReservedOrderMethod.hh',
    'DeleteReservedOrderRequest' => $baseDir . '/requests/objects/models/rsvd_orders/DeleteReservedOrderRequest.hh',
    'DeleteReservedOrderRequestBuilder' => $baseDir . '/requests/objects/models/rsvd_orders/DeleteReservedOrderRequest.hh',
    'DeleteReservedOrderRequestFactory' => $baseDir . '/requests/objects/factories/rsvd_orders/DeleteReservedOrderRequestFactory.hh',
    'DeleteReservedOrderRequestFactoryLazyLoader' => $baseDir . '/dependency_injection/apis/lazy_loaders/DeleteReservedOrderRequestFactoryLazyLoader.hh',
    'DescOrderByTerm' => $baseDir . '/access_layer/queries/sql/order_by_clause/DescOrderByTerm.hh',
    'DoesExistConflictingOrderMethod' => $baseDir . '/methods/confirm_order/DoesExistConflictingOrderMethod.hh',
    'DuplicateEmailException' => $baseDir . '/methods/exceptions/DuplicateEmailException.hh',
    'DuplicateUniqueKeyQueryException' => $baseDir . '/access_layer/queries/sql/exceptions/DuplicateUniqueKeyQueryException.hh',
    'Email' => $baseDir . '/utils/data_types/Email.hh',
    'EmailFieldConverter' => $baseDir . '/requests/fields/converters/EmailFieldConverter.hh',
    'EmailRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/EmailRequestFieldFactoryBuilder.hh',
    'EqualsWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/EqualsWhereClause.hh',
    'FailedApiResult' => $baseDir . '/apis/results/FailedApiResult.hh',
    'FailedConfirmOrderApiResult' => $baseDir . '/apis/results/confirm_order/FailedConfirmOrderApiResult.hh',
    'FailedConfirmOrderApiResultType' => $baseDir . '/apis/results/confirm_order/FailedConfirmOrderApiResultType.hh',
    'FailedCreateUserApiResult' => $baseDir . '/apis/results/create_user/FailedCreateUserApiResult.hh',
    'FailedGetUserByEmailApiResult' => $baseDir . '/apis/results/get_user/FailedGetUserByEmailApiResult.hh',
    'FailedGetUserByEmailApiResultType' => $baseDir . '/apis/results/get_user/FailedGetUserByEmailApiResultType.hh',
    'FailedGetUsersConfirmedOrdersApiResult' => $baseDir . '/apis/results/confirm_order/FailedGetUsersConfirmedOrdersApiResult.hh',
    'FailedGetUsersConfirmedOrdersApiResultType' => $baseDir . '/apis/results/confirm_order/FailedGetUsersConfirmedOrdersApiType.hh',
    'FailedQueryApiResult' => $baseDir . '/apis/results/FailedQueryApiResult.hh',
    'FailedQueryMethodException' => $baseDir . '/methods/exceptions/FailedQueryMethodException.hh',
    'FetchByIdQuery' => $baseDir . '/access_layer/queries/fetches/core/FetchByIdQuery.hh',
    'FetchByUniqueKeyQuery' => $baseDir . '/access_layer/queries/fetches/core/FetchByUniqueKeyQuery.hh',
    'FetchConfirmedOrderCellLabelsQuery' => $baseDir . '/access_layer/queries/fetches/FetchConfirmedOrderCellLabelsQuery.hh',
    'FetchConfirmedOrdersByTimeQuery' => $baseDir . '/access_layer/queries/fetches/FetchConfirmedOrdersByTimeQuery.hh',
    'FetchIrregularTimesQuery' => $baseDir . '/access_layer/queries/fetches/FetchIrregularTimesQuery.hh',
    'FetchParams' => $baseDir . '/access_layer/queries/fetches/core/FetchParams.hh',
    'FetchParamsBuilder' => $baseDir . '/access_layer/queries/fetches/core/FetchParamsBuilder.hh',
    'FetchQuery' => $baseDir . '/access_layer/queries/fetches/core/FetchQuery.hh',
    'FetchQueryMaker' => $baseDir . '/access_layer/queries/fetches/core/FetchQueryMaker.hh',
    'FetchQueryString' => $baseDir . '/access_layer/queries/fetches/core/FetchQueryString.hh',
    'FetchRegularTimesQuery' => $baseDir . '/access_layer/queries/fetches/FetchRegularTimesQuery.hh',
    'FetchReservedOrdersByTimeQuery' => $baseDir . '/access_layer/queries/fetches/FetchReservedOrdersByTimeQuery.hh',
    'FetchSingletonQuery' => $baseDir . '/access_layer/queries/fetches/FetchSingletonQuery.hh',
    'FetchUsersConfirmedOrdersQuery' => $baseDir . '/access_layer/queries/fetches/FetchUsersConfirmedOrdersQuery.hh',
    'FetchUsersRsvdOrdersQuery' => $baseDir . '/access_layer/queries/fetches/FetchUsersRsvdOrdersQuery.hh',
    'FloatFieldConverter' => $baseDir . '/requests/fields/converters/FloatFieldConverter.hh',
    'FloatRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/FloatRequestFieldFactoryBuilder.hh',
    'GeneralApiFailureType' => $baseDir . '/apis/results/general/GeneralApiFailureType.hh',
    'GeneralFailedApiResult' => $baseDir . '/apis/results/general/GeneralFailedApiResult.hh',
    'GetUserByEmailApi' => $baseDir . '/apis/calls/get_user/GetUserByEmailApi.hh',
    'GetUserByEmailMethod' => $baseDir . '/methods/user/GetUserByEmailMethod.hh',
    'GetUserByEmailRequest' => $baseDir . '/requests/objects/models/users/GetUserByEmailRequest.hh',
    'GetUserByEmailRequestBuilder' => $baseDir . '/requests/objects/models/users/GetUserByEmailRequest.hh',
    'GetUserByEmailRequestFactory' => $baseDir . '/requests/objects/factories/users/GetUserByEmailRequestFactory.hh',
    'GetUserByEmailRequestFactoryLazyLoader' => $baseDir . '/dependency_injection/apis/lazy_loaders/GetUserByEmailRequestLazyLoader.hh',
    'GetUserByUniqueKeyApiResult' => $baseDir . '/apis/results/get_user/GetUserByUniqueKeyApiResult.hh',
    'GetUsersConfirmedOrdersAndCellLabelsMethod' => $baseDir . '/methods/confirm_order/GetUsersConfirmedOrdersAndCellLabelsMethod.hh',
    'GetUsersConfirmedOrdersApi' => $baseDir . '/apis/calls/confirm_order/GetUsersConfirmedOrdersApi.hh',
    'GetUsersConfirmedOrdersApiResult' => $baseDir . '/apis/results/confirm_order/GetUsersConfirmedOrdersApiResult.hh',
    'GetUsersConfirmedOrdersMethod' => $baseDir . '/methods/confirm_order/GetUsersConfirmedOrdersMethod.hh',
    'GetUsersConfirmedOrdersRequest' => $baseDir . '/requests/objects/models/confirmed_orders/GetUsersConfirmedOrdersRequest.hh',
    'GetUsersConfirmedOrdersRequestBuilder' => $baseDir . '/requests/objects/models/confirmed_orders/GetUsersConfirmedOrdersRequest.hh',
    'GreaterThanOrEqualToWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/GreaterThanOrEqualToWhereClause.hh',
    'GreaterThanWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/GreaterThanWhereClause.hh',
    'HRDateSerializer' => $baseDir . '/utils/data_types/chronos/date/serializers/HRDateSerializer.hh',
    'HRDateSerializerLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/HRDateSerializerLazyLoader.hh',
    'HRTimeSerializer' => $baseDir . '/utils/data_types/chronos/time/serializers/HRTimeSerializer.hh',
    'HRTimeSerializerLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/HRTimeSerializerLazyLoader.hh',
    'HRTimestampSerializer' => $baseDir . '/utils/data_types/chronos/timestamp/serializers/HRTimestampSerializer.hh',
    'HRTimestampSerializerLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/HRTimestampSerializerLazyLoader.hh',
    'Hour' => $baseDir . '/utils/data_types/chronos/time/objects/Hour.hh',
    'HttpParamsFetcher' => $baseDir . '/apis/HttpParamsFetcher.hh',
    'HttpServer' => $baseDir . '/apis/HttpServer.hh',
    'InsertCellLabelQuery' => $baseDir . '/access_layer/queries/insert/InsertCellLabelQuery.hh',
    'InsertConfirmedOrderQuery' => $baseDir . '/access_layer/queries/insert/InsertConfirmedOrderQuery.hh',
    'InsertIrregularDateQuery' => $baseDir . '/access_layer/queries/insert/InsertIrregularDateQuery.hh',
    'InsertIrregularTimeQuery' => $baseDir . '/access_layer/queries/insert/InsertIrregularTimeQuery.hh',
    'InsertQuery' => $baseDir . '/access_layer/queries/insert/InsertQuery.hh',
    'InsertQueryCreater' => $baseDir . '/access_layer/queries/insert/InsertQueryCreater.hh',
    'InsertQueryCreaterLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/InsertQueryCreaterLazyLoader.hh',
    'InsertRegularTimeQuery' => $baseDir . '/access_layer/queries/insert/InsertRegularTimeQuery.hh',
    'InsertRegularWeekDayQuery' => $baseDir . '/access_layer/queries/insert/InsertRegularWeekDayQuery.hh',
    'InsertRegularWeekDayRegularTimeEdgeQuery' => $baseDir . '/access_layer/queries/insert/InsertRegularWeekDayRegularTimeEdgeQuery.hh',
    'InsertReservedOrderPolicyQuery' => $baseDir . '/access_layer/queries/insert/InsertReservedOrderPolicyQuery.hh',
    'InsertReservedOrderQuery' => $baseDir . '/access_layer/queries/insert/InsertReservedOrderQuery.hh',
    'InsertUserQuery' => $baseDir . '/access_layer/queries/insert/InsertUserQuery.hh',
    'IntFieldConverter' => $baseDir . '/requests/fields/converters/IntFieldConverter.hh',
    'IntRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/IntRequestFieldFactoryBuilder.hh',
    'InvalidCellLabelCountException' => $baseDir . '/methods/exceptions/InvalidCellLabelCountException.hh',
    'InvalidReservedOrderRequestException' => $baseDir . '/methods/exceptions/InvalidReservedOrderRequestException.hh',
    'IrregularDate' => $baseDir . '/access_layer/models/objects/IrregularDate.hh',
    'IrregularDateFactory' => $baseDir . '/access_layer/models/factories/IrregularDateFactory.hh',
    'IrregularDateModelFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/IrregularDateModelFactoryLazyLoader.hh',
    'IrregularDatesTable' => $baseDir . '/access_layer/tables/IrregularDatesTable.hh',
    'IrregularDatesTableLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/IrregularDatesTableLazyLoader.hh',
    'IrregularTime' => $baseDir . '/access_layer/models/objects/IrregularTime.hh',
    'IrregularTimeFactory' => $baseDir . '/access_layer/models/factories/IrregularTimeFactory.hh',
    'IrregularTimeModelFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/IrregularTimeModelFactoryLazyLoader.hh',
    'IrregularTimesTable' => $baseDir . '/access_layer/tables/IrregularTimesTable.hh',
    'IrregularTimesTableLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/IrregularTimesTableLazyLoader.hh',
    'IsConflictingReservedOrderMethod' => $baseDir . '/methods/rsvd_orders/IsConflictingReservedOrderMethod.hh',
    'IsValidReservedOrderMethod' => $baseDir . '/methods/rsvd_orders/IsValidReservedOrderMethod.hh',
    'JsonApiRequestDeserializer' => $baseDir . '/apis/deserializers/JsonApiRequestDeserializer.hh',
    'JsonApiResultSerializer' => $baseDir . '/apis/serializers/JsonApiResultSerializer.hh',
    'LazyLoader' => $baseDir . '/dependency_injection/core/LazyLoader.hh',
    'LessThanOrEqualToWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/LessThanOrEqualToWhereClause.hh',
    'LessThanWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/LessThanWhereClause.hh',
    'LogicalWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/logical/LogicalWhereClause.hh',
    'MalformedApiRequestException' => $baseDir . '/apis/deserializers/exception/MalformedApiRequestException.hh',
    'MapRequestFieldFactory' => $baseDir . '/requests/fields/MapRequestFieldFactory.hh',
    'MapRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/MapRequestFieldFactoryBuilder.hh',
    'MaxLengthConstraint' => $baseDir . '/requests/fields/validators/constraints/MaxLengthConstraint.hh',
    'MaxValueConstraint' => $baseDir . '/requests/fields/validators/constraints/MaxValueConstraint.hh',
    'MethodException' => $baseDir . '/methods/exceptions/MethodException.hh',
    'MethodInjector' => $baseDir . '/dependency_injection/methods/MethodInjector.hh',
    'MethodInjectorFactory' => $baseDir . '/dependency_injection/methods/MethodInjectorFactory.hh',
    'MinEndTimeOrderTimestampSegmentComparator' => $baseDir . '/utils/algorithm/MinEndTimeOrderTimestampSegmentComparator.hh',
    'MinLengthConstraint' => $baseDir . '/requests/fields/validators/constraints/MinLengthConstraint.hh',
    'MinValueConstraint' => $baseDir . '/requests/fields/validators/constraints/MinValueConstraint.hh',
    'Minute' => $baseDir . '/utils/data_types/chronos/time/objects/Minute.hh',
    'Model' => $baseDir . '/access_layer/models/objects/Model.hh',
    'ModelFactory' => $baseDir . '/access_layer/models/factories/ModelFactory.hh',
    'Month' => $baseDir . '/utils/data_types/chronos/date/objects/Month.hh',
    'NonextantObjectException' => $baseDir . '/methods/exceptions/NonextantObjectException.hh',
    'NotEqualsWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/NotEqualsWhereClause.hh',
    'NullableRequestField' => $baseDir . '/requests/fields/NullableRequestField.hh',
    'NullableRequestFieldFactory' => $baseDir . '/requests/fields/factories/NullableRequestFieldFactory.hh',
    'NullableRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/NullableRequestFieldFactoryBuilder.hh',
    'NullableStringRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/NullableStringRequestFieldFactoryBuilder.hh',
    'NullableUnsignedIntRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/NullableUnsignedIntRequestFieldFactoryBuilder.hh',
    'ObjectVectorRequestField' => $baseDir . '/requests/fields/ObjectVectorRequestField.hh',
    'ObjectVectorRequestFieldFactory' => $baseDir . '/requests/fields/factories/ObjectVectorRequestFieldFactory.hh',
    'ObjectVectorRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/ObjectVectorRequestFieldFactoryBuilder.hh',
    'OrWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/logical/OrWhereClause.hh',
    'Order' => $baseDir . '/access_layer/models/objects/Order.hh',
    'OrderByClause' => $baseDir . '/access_layer/queries/sql/order_by_clause/OrderByClause.hh',
    'OrderByClauseBuilder' => $baseDir . '/access_layer/queries/sql/order_by_clause/OrderByClauseBuilder.hh',
    'OrderByTerm' => $baseDir . '/access_layer/queries/sql/order_by_clause/OrderByTerm.hh',
    'OrderConfiguration' => $baseDir . '/access_layer/models/objects/OrderConfiguration.hh',
    'OrderConfigurationFactory' => $baseDir . '/access_layer/models/factories/OrderConfigurationFactory.hh',
    'OrderConfigurationInsertQuery' => $baseDir . '/access_layer/queries/insert/OrderConfigurationInsertQuery.hh',
    'OrderConfigurationTable' => $baseDir . '/access_layer/tables/OrderConfigurationTable.hh',
    'OrderStatus' => $baseDir . '/access_layer/models/objects/OrderStatus.hh',
    'OrderStatusType' => $baseDir . '/access_layer/models/objects/OrderStatus.hh',
    'OrderTimestampSegment' => $baseDir . '/access_layer/models/objects/OrderTimestampInterval.hh',
    'PriorityQueue' => $baseDir . '/utils/data_structures/priority_queue/PriorityQueue.hh',
    'ProductionApiInjectorFactory' => $baseDir . '/dependency_injection/apis/ProductionApiInjectorFactory.hh',
    'ProductionApiRouter' => $baseDir . '/apis/router/ProductionApiRouter.hh',
    'ProductionApiRouterFactory' => $baseDir . '/apis/router/ProductionApiRouterFactory.hh',
    'ProductionApiRunnerFactory' => $baseDir . '/apis/runners/ProductionApiRunnerFactory.hh',
    'ProductionAsyncMysqlConnectionFactory' => $baseDir . '/access_layer/db/async_mysql/ProductionAsyncMysqlConnectionFactory.hh',
    'ProductionMethodInjectorFactory' => $baseDir . '/dependency_injection/methods/ProductionMethodInjectorFactory.hh',
    'ProductionQueryInjectorFactory' => $baseDir . '/dependency_injection/queries/ProductionQueryInjectorFactory.hh',
    'QueryErrorType' => $baseDir . '/access_layer/queries/sql/exceptions/QueryErrorType.hh',
    'QueryException' => $baseDir . '/access_layer/queries/sql/exceptions/QueryException.hh',
    'QueryExceptionFactory' => $baseDir . '/access_layer/queries/sql/exceptions/QueryExceptionFactory.hh',
    'QueryExceptionFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/QueryExceptionFactoryLazyLoader.hh',
    'QueryInjector' => $baseDir . '/dependency_injection/queries/QueryInjector.hh',
    'QueryInjectorFactory' => $baseDir . '/dependency_injection/queries/QueryInjectorFactory.hh',
    'RegularTime' => $baseDir . '/access_layer/models/objects/RegularTime.hh',
    'RegularTimeFactory' => $baseDir . '/access_layer/models/factories/RegularTimeFactory.hh',
    'RegularTimeModelFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/RegularTimeModelFactoryLazyLoader.hh',
    'RegularTimesTable' => $baseDir . '/access_layer/tables/RegularTimesTable.hh',
    'RegularTimesTableLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/RegularTimesTableLazyLoader.hh',
    'RegularWeekDay' => $baseDir . '/access_layer/models/objects/RegularWeekDay.hh',
    'RegularWeekDayFactory' => $baseDir . '/access_layer/models/factories/RegularWeekDayFactory.hh',
    'RegularWeekDayModelFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/RegularWeekDayModelFactoryLazyLoader.hh',
    'RegularWeekDayRegularTimeEdge' => $baseDir . '/access_layer/models/objects/RegularWeekDayRegularTimeEdge.hh',
    'RegularWeekDayRegularTimeEdgeFactory' => $baseDir . '/access_layer/models/factories/RegularWeekDayRegularTimeEdgeFactory.hh',
    'RegularWeekDayRegularTimeEdgeModelFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/RegularWeekDayRegularTimeEdgeModelFactoryLazyLoader.hh',
    'RegularWeekDayRegularTimeEdgesTable' => $baseDir . '/access_layer/tables/RegularWeekDayRegularTimeEdgesTable.hh',
    'RegularWeekDayRegularTimeEdgesTableLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/RegularWeekDayRegularTimeEdgesTableLazyLoader.hh',
    'RegularWeekDaysTable' => $baseDir . '/access_layer/tables/RegularWeekDaysTable.hh',
    'RegularWeekDaysTableLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/RegularWeekDaysTableLazyLoader.hh',
    'RequestException' => $baseDir . '/requests/exceptions/RequestException.hh',
    'RequestFactory' => $baseDir . '/requests/objects/factories/RequestFactory.hh',
    'RequestField' => $baseDir . '/requests/fields/RequestField.hh',
    'RequestFieldConstraint' => $baseDir . '/requests/fields/validators/constraints/RequestFieldConstraint.hh',
    'RequestFieldConstraintException' => $baseDir . '/requests/fields/validators/constraints/exceptions/RequestFieldConstraintException.hh',
    'RequestFieldConstraintType' => $baseDir . '/requests/fields/validators/constraints/RequestFieldConstraintType.hh',
    'RequestFieldFactory' => $baseDir . '/requests/fields/factories/RequestFieldFactory.hh',
    'RequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/RequestFieldFactoryBuilder.hh',
    'RequestFieldType' => $baseDir . '/requests/fields/RequestFieldType.hh',
    'RequestFieldTypeConversionException' => $baseDir . '/requests/fields/converters/exceptions/RequestFieldTypeConversionException.hh',
    'RequestFieldTypeConverter' => $baseDir . '/requests/fields/converters/RequestFieldTypeConverter.hh',
    'RequestFieldValidator' => $baseDir . '/requests/fields/validators/RequestFieldValidator.hh',
    'RequestWrapper' => $baseDir . '/requests/objects/models/RequestWrapper.hh',
    'RequestWrapperBuilder' => $baseDir . '/requests/objects/models/RequestWrapper.hh',
    'RequestWrapperFactory' => $baseDir . '/requests/objects/factories/wrapper/RequestWrapperFactory.hh',
    'ReserveOrderApi' => $baseDir . '/apis/calls/reserve_order/ReserveOrderApi.hh',
    'ReserveOrderApiResult' => $baseDir . '/apis/results/reserve_order/ReserveOrderApiResult.hh',
    'ReserveOrderMethod' => $baseDir . '/methods/rsvd_orders/ReserveOrderMethod.hh',
    'ReserveOrderRequest' => $baseDir . '/requests/objects/models/rsvd_orders/ReserveOrderRequest.hh',
    'ReserveOrderRequestBuilder' => $baseDir . '/requests/objects/models/rsvd_orders/ReserveOrderRequest.hh',
    'ReserveOrderRequestFactory' => $baseDir . '/requests/objects/factories/rsvd_orders/ReserveOrderRequestFactory.hh',
    'ReserveOrderRequestFactoryLazyLoader' => $baseDir . '/dependency_injection/apis/lazy_loaders/ReserveOrderRequestFactoryLazyLoader.hh',
    'ReservedOrderModelFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/ReservedOrderModelFactoryLazyLoader.hh',
    'ReservedOrderPolicy' => $baseDir . '/access_layer/models/objects/ReservedOrderPolicy.hh',
    'ReservedOrderPolicyFactory' => $baseDir . '/access_layer/models/factories/ReservedOrderPolicyFactory.hh',
    'ReservedOrderPolicyModelFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/ReservedOrderPolicyModelFactoryLazyLoader.hh',
    'ReservedOrderPolicyTable' => $baseDir . '/access_layer/tables/ReservedOrderPolicyTable.hh',
    'ReservedOrderPolicyTableLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/ReservedOrderPolicyTableLazyLoader.hh',
    'ReservedOrdersTableLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/ReservedOrdersTableLazyLoader.hh',
    'RsvdOrder' => $baseDir . '/access_layer/models/objects/RsvdOrder.hh',
    'RsvdOrderFactory' => $baseDir . '/access_layer/models/factories/RsvdOrderFactory.hh',
    'RsvdOrdersTable' => $baseDir . '/access_layer/tables/RsvdOrdersTable.hh',
    'Second' => $baseDir . '/utils/data_types/chronos/time/objects/Second.hh',
    'ServerState' => $baseDir . '/utils/server/ServerState.hh',
    'SingleDayTimeSegment' => $baseDir . '/utils/data_types/chronos/time/objects/SingleDayTimeInterval.hh',
    'SingletonMethodInjectorFactory' => $baseDir . '/dependency_injection/methods/SingletonMethodInjectorFactory.hh',
    'SingletonQueryInjectorFactory' => $baseDir . '/dependency_injection/queries/SingletonQueryInjectorFactory.hh',
    'StaticServerState' => $baseDir . '/utils/server/StaticServerState.hh',
    'StringFieldConverter' => $baseDir . '/requests/fields/converters/StringFieldConverter.hh',
    'StringRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/StringRequestFieldFactoryBuilder.hh',
    'SuccessfulApiResult' => $baseDir . '/apis/results/SuccessfulApiResult.hh',
    'Table' => $baseDir . '/access_layer/tables/Table.hh',
    'Time' => $baseDir . '/utils/data_types/chronos/time/objects/Time.hh',
    'TimeBuilder' => $baseDir . '/utils/data_types/chronos/time/objects/TimeBuilder.hh',
    'TimeSegment' => $baseDir . '/utils/data_types/chronos/time/objects/TimeSegment.hh',
    'TimeSerializer' => $baseDir . '/utils/data_types/chronos/time/serializers/TimeSerializer.hh',
    'Timestamp' => $baseDir . '/utils/data_types/chronos/timestamp/objects/Timestamp.hh',
    'TimestampBuilder' => $baseDir . '/utils/data_types/chronos/timestamp/objects/TimestampBuilder.hh',
    'TimestampBuilderLazyLoader' => $baseDir . '/dependency_injection/queries/TimestampBuilderLazyLoader.hh',
    'TimestampFieldConverter' => $baseDir . '/requests/fields/converters/TimestampFieldConverter.hh',
    'TimestampRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/TimestampRequestFieldFactoryBuilder.hh',
    'TimestampSegment' => $baseDir . '/utils/data_types/chronos/timestamp/objects/TimestampSegment.hh',
    'TimestampSegmentExpander' => $baseDir . '/utils/data_types/chronos/timestamp/expanders/TimestampSegmentExpander.hh',
    'TimestampSegmentExpanderLazyLoader' => $baseDir . '/dependency_injection/methods/lazy_loaders/TimestampSegmentExpanderLazyLoader.hh',
    'TimestampSerializer' => $baseDir . '/utils/data_types/chronos/timestamp/serializers/TimestampSerializer.hh',
    'UnexpectedRequestFieldKeyException' => $baseDir . '/requests/objects/factories/UnexpectedRequestFieldKeyException.hh',
    'UniqueElementViolationException' => $baseDir . '/requests/exceptions/UniqueElementViolationException.hh',
    'UnknownFailedApiResult' => $baseDir . '/apis/results/general/UnknownFailedApiResult.hh',
    'UnknownQueryException' => $baseDir . '/access_layer/queries/sql/exceptions/UnknownQueryException.hh',
    'UnsetRequestFieldException' => $baseDir . '/requests/objects/models/exceptions/UnsetRequestFieldException.hh',
    'UnsignedInt' => $baseDir . '/utils/data_types/UnsignedInt.hh',
    'UnsignedIntFieldConverter' => $baseDir . '/requests/fields/converters/UnsignedIntFieldConverter.hh',
    'UnsignedIntRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/UnsignedIntRequestFieldFactoryBuilder.hh',
    'UpdateByIdQuery' => $baseDir . '/access_layer/queries/updates/UpdateByIdQuery.hh',
    'UpdateByUniqueKeyQuery' => $baseDir . '/access_layer/queries/updates/UpdateByUniqueKeyQuery.hh',
    'UpdateCellLabelApi' => $baseDir . '/apis/calls/cell_label/UpdateCellLabelApi.hh',
    'UpdateCellLabelMethod' => $baseDir . '/methods/cell_label/UpdateCellLabelMethod.hh',
    'UpdateCellLabelRequest' => $baseDir . '/requests/objects/models/cell_label/UpdateCellLabelRequest.hh',
    'UpdateCellLabelRequestBuilder' => $baseDir . '/requests/objects/models/cell_label/UpdateCellLabelRequest.hh',
    'UpdateCellLabelRequestFactory' => $baseDir . '/requests/objects/factories/cell_labels/UpdateCellLabelRequestFactory.hh',
    'UpdateCellLabelRequestFactoryLazyLoader' => $baseDir . '/dependency_injection/apis/lazy_loaders/UpdateCellLabelRequestFactoryLazyLoader.hh',
    'UpdateConfirmedOrderApi' => $baseDir . '/apis/calls/confirm_order/UpdateConfirmedOrderApi.hh',
    'UpdateConfirmedOrderMethod' => $baseDir . '/methods/confirm_order/UpdateConfirmedOrderMethod.hh',
    'UpdateConfirmedOrderRequest' => $baseDir . '/requests/objects/models/confirmed_orders/UpdateConfirmedOrderRequest.hh',
    'UpdateConfirmedOrderRequestBuilder' => $baseDir . '/requests/objects/models/confirmed_orders/UpdateConfirmedOrderRequest.hh',
    'UpdateConfirmedOrderRequestFactory' => $baseDir . '/requests/objects/factories/confirmed_orders/UpdateConfirmedOrderRequestFactory.hh',
    'UpdateConfirmedOrderRequestFactoryLazyLoader' => $baseDir . '/dependency_injection/apis/lazy_loaders/UpdateConfirmedOrderRequestFactoryLazyLoader.hh',
    'UpdateQuery' => $baseDir . '/access_layer/queries/updates/UpdateQuery.hh',
    'UpdateUserMethod' => $baseDir . '/methods/user/UpdateUserMethod.hh',
    'User' => $baseDir . '/access_layer/models/objects/User.hh',
    'UserFactory' => $baseDir . '/access_layer/models/factories/UserFactory.hh',
    'UserModelFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/UserModelFactoryLazyLoader.hh',
    'UserPrivilege' => $baseDir . '/access_layer/models/objects/UserPrivilege.hh',
    'UserPrivilegeFactory' => $baseDir . '/access_layer/models/factories/UserPrivilegeFactory.hh',
    'UserPrivilegeType' => $baseDir . '/access_layer/models/objects/UserPrivilege.hh',
    'UserPrivilegesTable' => $baseDir . '/access_layer/tables/UserPrivilegesTable.hh',
    'UserUserPrivilegeEdgesTable' => $baseDir . '/access_layer/tables/UserUserPrivilegeEdgesTable.hh',
    'UsersTable' => $baseDir . '/access_layer/tables/UsersTable.hh',
    'UsersTableLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/UsersTableLazyLoader.hh',
    'VectorRequestFieldConstraint' => $baseDir . '/requests/fields/validators/constraints/VectorRequestFieldConstraint.hh',
    'WebParamsFetcher' => $baseDir . '/utils/web/WebParamsFetcher.hh',
    'WhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/core/WhereClause.hh',
    'WhereClauseVector' => $baseDir . '/access_layer/queries/sql/where_clause/core/WhereClauseVector.hh',
    'WhereClauseVectorBuilder' => $baseDir . '/access_layer/queries/sql/where_clause/core/WhereClauseVectorBuilder.hh',
    'Year' => $baseDir . '/utils/data_types/chronos/date/objects/Year.hh',
);

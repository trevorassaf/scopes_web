<?php

// autoload_classmap.php @generated by Composer

$vendorDir = dirname(dirname(__FILE__));
$baseDir = dirname($vendorDir);

return array(
    'AndWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/logical/AndWhereClause.hh',
    'Api' => $baseDir . '/apis/Api.hh',
    'ApiFieldType' => $baseDir . '/apis/ApiFieldType.hh',
    'ApiRequestDeserializer' => $baseDir . '/apis/deserializers/ApiRequestDeserializer.hh',
    'ApiResult' => $baseDir . '/apis/results/ApiResult.hh',
    'ApiResultSerializer' => $baseDir . '/apis/serializers/ApiResultSerializer.hh',
    'ApiRouter' => $baseDir . '/apis/router/ApiRouter.hh',
    'ApiRunner' => $baseDir . '/apis/runners/ApiRunner.hh',
    'ApiRunnerFactory' => $baseDir . '/apis/runners/ApiRunnerFactory.hh',
    'ApiType' => $baseDir . '/apis/ApiType.hh',
    'ApiTypeFieldConverter' => $baseDir . '/requests/fields/converters/ApiTypeFieldConverter.hh',
    'ApiTypeRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/ApiTypeRequestFieldFactoryBuilder.hh',
    'ApplicationSerializerFactory' => $baseDir . '/apis/serializers/ApplicationSerializerFactory.hh',
    'AscOrderByTerm' => $baseDir . '/access_layer/queries/sql/order_by_clause/AscOrderByTerm.hh',
    'AsyncMysqlConnectionFactory' => $baseDir . '/access_layer/db/async_mysql/AsyncMysqlConnectionFactory.hh',
    'AsyncMysqlConnectionLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/AsyncMysqlConnectionLazyLoader.hh',
    'BatchInsertQuery' => $baseDir . '/access_layer/queries/insert/BatchInsertQuery.hh',
    'BoolFieldConverter' => $baseDir . '/requests/fields/converters/BoolFieldConverter.hh',
    'BoolRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/BoolRequestFieldFactoryBuilder.hh',
    'CellLabel' => $baseDir . '/access_layer/models/objects/CellLabel.hh',
    'CellLabelFactory' => $baseDir . '/access_layer/models/factories/CellLabelFactory.hh',
    'CellLabelModelFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/CellLabelModelFactoryLazyLoader.hh',
    'CellLabelRequest' => $baseDir . '/requests/objects/models/CellLabelRequest.hh',
    'CellLabelsTable' => $baseDir . '/access_layer/tables/CellLabelsTable.hh',
    'CellLabelsTableLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/CellLabelsTableLazyLoader.hh',
    'Comparator' => $baseDir . '/utils/algorithm/Comparator.hh',
    'ComparisonWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/ComparisonWhereClause.hh',
    'ConcreteModelFactory' => $baseDir . '/access_layer/models/factories/ConcreteModelFactory.hh',
    'ConfirmOrderMethod' => $baseDir . '/methods/ConfirmOrderMethod.hh',
    'ConfirmOrderRequest' => $baseDir . '/requests/objects/models/ConfirmOrderRequest.hh',
    'ConfirmedOrder' => $baseDir . '/access_layer/models/objects/ConfirmedOrder.hh',
    'ConfirmedOrderFactory' => $baseDir . '/access_layer/models/factories/ConfirmedOrderFactory.hh',
    'ConfirmedOrderModelFactoryLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/ConfirmedOrderModelFactoryLazyLoader.hh',
    'ConfirmedOrdersTable' => $baseDir . '/access_layer/tables/ConfirmedOrdersTable.hh',
    'ConfirmedOrdersTableLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/ConfirmedOrdersTableLazyLoader.hh',
    'ConnectionConfig' => $baseDir . '/access_layer/db/async_mysql/ConnectionConfig.hh',
    'ConnectionConfigBuilder' => $baseDir . '/access_layer/db/async_mysql/ConnectionConfigBuilder.hh',
    'ConstraintMapToConjunctiveWhereClauseTranslator' => $baseDir . '/access_layer/queries/util/ConstraintMapToConjunctiveWhereClauseTranslator.hh',
    'ConstraintMapToConjunctiveWhereClauseTranslatorLazyLoader' => $baseDir . '/dependency_injection/queries/lazy_loaders/ConstraintMapToConjunctiveWhereClauseTranslatorLazyLoader.hh',
    'CreateIrregularDateMethod' => $baseDir . '/methods/create/CreateIrregularDateMethod.hh',
    'CreateIrregularTimeMethod' => $baseDir . '/methods/create/CreateIrregularTimeMethod.hh',
    'CreateRegularTimeMethod' => $baseDir . '/methods/create/CreateRegularTimeMethod.hh',
    'CreateRegularWeekDayMethod' => $baseDir . '/methods/create/CreateRegularWeekDayMethod.hh',
    'CreateRegularWeekDayRegularTimeEdgeMethod' => $baseDir . '/methods/create/CreateRegularWeekDayRegularTimeEdgeMethod.hh',
    'CreateReservedOrderPolicyMethod' => $baseDir . '/methods/CreateReservedOrderPolicyMethod.hh',
    'CreateUserApi' => $baseDir . '/apis/calls/create_user/CreateUserApi.hh',
    'CreateUserApiFailureType' => $baseDir . '/apis/results/create_user/CreateUserApiFailureType.hh',
    'CreateUserApiResult' => $baseDir . '/apis/results/create_user/CreateUserApiResult.hh',
    'CreateUserDuplicateEmailException' => $baseDir . '/methods/create_user/exceptions/CreateUserDuplicateEmailException.hh',
    'CreateUserMethod' => $baseDir . '/methods/create_user/CreateUserMethod.hh',
    'CreateUserRequest' => $baseDir . '/requests/objects/models/CreateUserRequest.hh',
    'CreateUserRequestBuilder' => $baseDir . '/requests/objects/models/CreateUserRequest.hh',
    'CreateUserRequestFactory' => $baseDir . '/requests/objects/factories/CreateUserRequestFactory.hh',
    'Date' => $baseDir . '/utils/data_types/Date.hh',
    'DayOfTheWeekType' => $baseDir . '/utils/data_types/DayOfTheWeekType.hh',
    'DbErrorType' => $baseDir . '/access_layer/db/exception/DbErrorType.hh',
    'DbException' => $baseDir . '/access_layer/db/exception/DbException.hh',
    'DebugApiRunnerFactory' => $baseDir . '/apis/runners/DebugApiRunnerFactory.hh',
    'DeleteByIdQuery' => $baseDir . '/access_layer/queries/deletes/DeleteByIdQuery.hh',
    'DeleteConfirmedOrderMethod' => $baseDir . '/methods/DeleteConfirmedOrderMethod.hh',
    'DeleteQuery' => $baseDir . '/access_layer/queries/deletes/DeleteQuery.hh',
    'DeleteReservedOrderMethod' => $baseDir . '/methods/DeleteReservedOrderMethod.hh',
    'DescOrderByTerm' => $baseDir . '/access_layer/queries/sql/order_by_clause/DescOrderByTerm.hh',
    'DoesExistConflictingOrderMethod' => $baseDir . '/methods/DoesExistConflictingOrderMethod.hh',
    'DuplicateEmailException' => $baseDir . '/methods/exceptions/DuplicateEmailException.hh',
    'Email' => $baseDir . '/utils/data_types/Email.hh',
    'EmailFieldConverter' => $baseDir . '/requests/fields/converters/EmailFieldConverter.hh',
    'EmailRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/EmailRequestFieldFactoryBuilder.hh',
    'EqualsWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/EqualsWhereClause.hh',
    'FailedApiResult' => $baseDir . '/apis/results/FailedApiResult.hh',
    'FailedCreateUserApiResult' => $baseDir . '/apis/results/create_user/FailedCreateUserApiResult.hh',
    'FailedGetUserByEmailApiResult' => $baseDir . '/apis/results/get_user/FailedGetUserByEmailApiResult.hh',
    'FailedGetUserByEmailApiResultType' => $baseDir . '/apis/results/get_user/FailedGetUserByEmailApiResultType.hh',
    'FetchByIdQuery' => $baseDir . '/access_layer/queries/fetches/core/FetchByIdQuery.hh',
    'FetchByUniqueKeyQuery' => $baseDir . '/access_layer/queries/fetches/core/FetchByUniqueKeyQuery.hh',
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
    'GetUserByEmailApi' => $baseDir . '/apis/calls/get_user/GetUserApi.hh',
    'GetUserByEmailMethod' => $baseDir . '/methods/GetUserByEmailMethod.hh',
    'GetUserByEmailRequest' => $baseDir . '/requests/objects/models/GetUserByEmailRequest.hh',
    'GetUserByEmailRequestBuilder' => $baseDir . '/requests/objects/models/GetUserByEmailRequest.hh',
    'GetUserByEmailRequestFactory' => $baseDir . '/requests/objects/factories/GetUserByEmailRequestFactory.hh',
    'GetUserByUniqueKeyApiResult' => $baseDir . '/apis/results/get_user/GetUserByUniqueKeyApiResult.hh',
    'GetUsersConfirmedOrdersMethod' => $baseDir . '/methods/GetUsersConfirmedOrdersMethod.hh',
    'GreaterThanOrEqualToWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/GreaterThanOrEqualToWhereClause.hh',
    'GreaterThanWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/GreaterThanWhereClause.hh',
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
    'InvalidRequestFieldKeyException' => $baseDir . '/requests/objects/factories/InvalidRequestFieldKeyException.hh',
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
    'IsConflictingReservedOrderMethod' => $baseDir . '/methods/IsConflictingReservedOrderMethod.hh',
    'IsValidReservedOrderMethod' => $baseDir . '/methods/IsValidReservedOrderMethod.hh',
    'JsonSerializer' => $baseDir . '/apis/serializers/JsonSerializer.hh',
    'LazyLoader' => $baseDir . '/dependency_injection/core/LazyLoader.hh',
    'LessThanOrEqualToWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/LessThanOrEqualToWhereClause.hh',
    'LessThanWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/LessThanWhereClause.hh',
    'LogicalWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/logical/LogicalWhereClause.hh',
    'MaxLengthConstraint' => $baseDir . '/requests/fields/validators/constraints/MaxLengthConstraint.hh',
    'MaxValueConstraint' => $baseDir . '/requests/fields/validators/constraints/MaxValueConstraint.hh',
    'MethodException' => $baseDir . '/methods/exceptions/MethodException.hh',
    'MethodInjector' => $baseDir . '/dependency_injection/methods/MethodInjector.hh',
    'MethodInjectorFactory' => $baseDir . '/dependency_injection/methods/MethodInjectorFactory.hh',
    'MinEndTimeOrderTimestampIntervalComparator' => $baseDir . '/utils/algorithm/MinEndTimeOrderTimestampIntervalComparator.hh',
    'MinLengthConstraint' => $baseDir . '/requests/fields/validators/constraints/MinLengthConstraint.hh',
    'MinValueConstraint' => $baseDir . '/requests/fields/validators/constraints/MinValueConstraint.hh',
    'Model' => $baseDir . '/access_layer/models/objects/Model.hh',
    'ModelFactory' => $baseDir . '/access_layer/models/factories/ModelFactory.hh',
    'MultiDayTimeInterval' => $baseDir . '/methods/MultiDayTimeInterval.hh',
    'NonextantObjectException' => $baseDir . '/methods/exceptions/NonextantObjectException.hh',
    'NotEqualsWhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/comparison/NotEqualsWhereClause.hh',
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
    'OrderTimestampInterval' => $baseDir . '/access_layer/models/objects/OrderTimestampInterval.hh',
    'PriorityQueue' => $baseDir . '/utils/data_structures/priority_queue/PriorityQueue.hh',
    'ProductionApiRunnerFactory' => $baseDir . '/apis/runners/ProductionApiRunnerFactory.hh',
    'ProductionAsyncMysqlConnectionFactory' => $baseDir . '/access_layer/db/async_mysql/ProductionAsyncMysqlConnectionFactory.hh',
    'ProductionMethodInjectorFactory' => $baseDir . '/dependency_injection/methods/ProductionMethodInjectorFactory.hh',
    'ProductionQueryInjectorFactory' => $baseDir . '/dependency_injection/queries/ProductionQueryInjectorFactory.hh',
    'QueryError' => $baseDir . '/access_layer/queries/exception/QueryError.hh',
    'QueryErrorBuilder' => $baseDir . '/access_layer/queries/exception/QueryErrorBuilder.hh',
    'QueryErrorType' => $baseDir . '/access_layer/queries/exception/QueryErrorType.hh',
    'QueryException' => $baseDir . '/access_layer/queries/exception/QueryException.hh',
    'QueryExceptionBuilder' => $baseDir . '/access_layer/queries/exception/QueryExceptionBuilder.hh',
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
    'RequestWrapperFactory' => $baseDir . '/requests/objects/factories/RequestWrapperFactory.hh',
    'ReserveOrderApi' => $baseDir . '/apis/calls/reserve_order/ReserveOrderApi.hh',
    'ReserveOrderApiResult' => $baseDir . '/apis/results/reserve_order/ReserveOrderApiResult.hh',
    'ReserveOrderMethod' => $baseDir . '/methods/ReserveOrderMethod.hh',
    'ReserveOrderRequest' => $baseDir . '/requests/objects/models/ReserveOrderRequest.hh',
    'ReserveOrderRequestBuilder' => $baseDir . '/requests/objects/models/ReserveOrderRequest.hh',
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
    'SameDayTimeInterval' => $baseDir . '/utils/data_types/SameDayTimeInterval.hh',
    'Serializer' => $baseDir . '/apis/serializers/Serializer.hh',
    'SerializerFactory' => $baseDir . '/apis/serializers/SerializerFactory.hh',
    'ServerState' => $baseDir . '/utils/server/ServerState.hh',
    'SingletonMethodInjectorFactory' => $baseDir . '/dependency_injection/methods/SingletonMethodInjectorFactory.hh',
    'SingletonQueryInjectorFactory' => $baseDir . '/dependency_injection/queries/SingletonQueryInjectorFactory.hh',
    'StaticServerState' => $baseDir . '/utils/server/StaticServerState.hh',
    'StringFieldConverter' => $baseDir . '/requests/fields/converters/StringFieldConverter.hh',
    'StringRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/StringRequestFieldFactoryBuilder.hh',
    'SuccessfulApiResult' => $baseDir . '/apis/results/SuccessfulApiResult.hh',
    'Table' => $baseDir . '/access_layer/tables/Table.hh',
    'Time' => $baseDir . '/utils/data_types/Time.hh',
    'TimeInterval' => $baseDir . '/utils/data_types/TimeInterval.hh',
    'Timestamp' => $baseDir . '/utils/data_types/Timestamp.hh',
    'TimestampBuilder' => $baseDir . '/utils/data_types/TimestampBuilder.hh',
    'TimestampFieldConverter' => $baseDir . '/requests/fields/converters/TimestampFieldConverter.hh',
    'TimestampInterval' => $baseDir . '/access_layer/models/objects/TimestampInterval.hh',
    'TimestampRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/TimestampRequestFieldFactoryBuilder.hh',
    'UnknownFailedApiResult' => $baseDir . '/apis/results/general/UnknownFailedApiResult.hh',
    'UnsetRequestFieldException' => $baseDir . '/requests/objects/models/exceptions/UnsetRequestFieldException.hh',
    'UnsignedInt' => $baseDir . '/utils/data_types/UnsignedInt.hh',
    'UnsignedIntFieldConverter' => $baseDir . '/requests/fields/converters/UnsignedIntFieldConverter.hh',
    'UnsignedIntRequestFieldFactoryBuilder' => $baseDir . '/requests/fields/factories/UnsignedIntRequestFieldFactoryBuilder.hh',
    'UpdateByIdQuery' => $baseDir . '/access_layer/queries/updates/UpdateByIdQuery.hh',
    'UpdateByUniqueKeyQuery' => $baseDir . '/access_layer/queries/updates/UpdateByUniqueKeyQuery.hh',
    'UpdateCellLabelMethod' => $baseDir . '/methods/UpdateCellLabelMethod.hh',
    'UpdateConfirmedOrderMethod' => $baseDir . '/methods/UpdateConfirmedOrderMethod.hh',
    'UpdateQuery' => $baseDir . '/access_layer/queries/updates/UpdateQuery.hh',
    'UpdateUserMethod' => $baseDir . '/methods/UpdateUserMethod.hh',
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
    'WebParamsFetcher' => $baseDir . '/utils/web/WebParamsFetcher.hh',
    'WhereClause' => $baseDir . '/access_layer/queries/sql/where_clause/core/WhereClause.hh',
    'WhereClauseVector' => $baseDir . '/access_layer/queries/sql/where_clause/core/WhereClauseVector.hh',
    'WhereClauseVectorBuilder' => $baseDir . '/access_layer/queries/sql/where_clause/core/WhereClauseVectorBuilder.hh',
);

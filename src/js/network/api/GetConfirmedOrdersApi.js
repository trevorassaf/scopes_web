GetConfirmedOrdersApi.prototype = new ScopesApi();
GetConfirmedOrdersApi.prototype.constructor = GetConfirmedOrdersApi;

function GetConfirmedOrdersApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x9;
};

GetConfirmedOrdersApi.prototype.getApiKeys = function() {
  return {
    orders: 'orders',
    confirmed_order: {
      id: 'id',
      scopes_count: 'scopes-count',
      start_time: 'start-time',
      end_time: 'end-time',
      title: 'title',
      description: 'description',
      time_ordered: 'time-ordered',
      price: 'price',
      short_code: 'short-code'
    },
    short_code: {
      id: 'id',
      code: 'code',
      alias: 'alias'
    }
  };
};

GetStartupDataApi.prototype = new ScopesApi();
GetStartupDataApi.prototype.constructor = GetStartupDataApi;

function GetStartupDataApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x15;
}

GetStartupDataApi.prototype.getApiKeys = function() {
  return {
    first_name: 'first_name',
    last_name: 'last_name',
    email: 'email',
    hourly_price: 'hourly_price',
    short_codes: 'short_codes',
    max_scopes: 'max_scopes',
    max_hours: 'max_hours',
    short_code_fields: {
      alias: 'alias',
      code: 'code',
      id: 'id'
    },
    start_time: 'start-time',
    end_time: 'end-time',
    time: {
      hours: 'hours',
      minutes: 'minutes',
      seconds: 'seconds'
    },
    start_time_interval: 'start-time-interval',
    min_days_in_advance: 'min-days-in-advance',
    max_months_in_advance: 'max-months-in-advance'
  };
};

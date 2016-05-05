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
    } 
  };
};

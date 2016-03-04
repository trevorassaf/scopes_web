GetStartupDataApi.prototype = new ScopesApi();
GetStartupDataApi.prototype.constructor = GetStartupDataApi;

function GetStartupDataApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x15;
}

GetStartupDataApi.prototype.getFirstNameKey = function() {
  return "first_name";
};

GetStartupDataApi.prototype.getShortCodesKey = function() {
  return "short_codes";
};

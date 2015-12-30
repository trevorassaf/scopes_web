CreateUserApi.prototype = new ScopesApi();
CreateUserApi.prototype.constructor = CreateUserApi;

function CreateUserApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x0;
  
  // Api param keys
  this.firstNameKey = "first-name";
  this.lastNameKey = "last-name";
  this.emailKey = "email";
}

CreateUserApi.prototype.setFirstName = function(first_name) {
  this.data[this.firstNameKey] = first_name; 
  return this;
}

CreateUserApi.prototype.setLastName = function(last_name) {
  this.data[this.lastNameKey] = last_name; 
  return this;
}

CreateUserApi.prototype.setEmail = function(email) {
  this.data[this.emailKey] = email; 
  return this;
}

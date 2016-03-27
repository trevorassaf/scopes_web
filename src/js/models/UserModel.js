var UserModel = function() {

  // User state
  this.id = null;
  this.firstName = null;
  this.lastName = null;
  this.email = null;

  // State change event listeners
  this.firstNameChangeListeners = [];
  this.lastNameChangeListeners = [];
  this.emailChangeListeners = [];
};

/**
 * User state getters
 */
UserModel.prototype.getId = function() {
  return this.id;
};

UserModel.prototype.getFirstName = function() {
  return this.firstName;
};

UserModel.prototype.getLastName = function() {
  return this.lastName;
};

UserModel.prototype.getEmail = function() {
  return this.email;
};

/**
 * User state setters w/callbacks
 */
UserModel.prototype.setId = function(id) {
  this.id = id;
  return this;
};

UserModel.prototype.setFirstName = function(first_name) {
  this.firstName = first_name;

  for (var i = 0; i < this.firstNameChangeListeners.length; ++i) {
    this.firstNameChangeListeners[i](firstName);
  }

  return this;
};

UserModel.prototype.setLastName = function(last_name) {
  this.lastName = last_name;

  for (var i = 0; i < this.lastNameChangeListeners.length; ++i) {
    this.lastNameChangeListeners[i](lastName);
  }

  return this;
};

UserModel.prototype.setEmail = function(email) {
  this.email = email;

  for (var i = 0; i < this.emailChangeListeners.length; ++i) {
    this.emailChangeListeners[i](email);
  }

  return this;
};

/**
 * Register event listeners 
 */
UserModel.prototype.bindFirstName = function(callback) {
  this.firstNameChangeListeners.push(callback); 
  return this;
};

UserModel.prototype.bindLastName = function(callback) {
  this.lastNameChangeListeners.push(callback); 
  return this;
};

UserModel.prototype.bindEmail = function(callback) {
  this.emailChangeListeners.push(callback); 
  return this;
};

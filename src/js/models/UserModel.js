var UserModel = function() {

  // User state
  this.id = null;
  this.firstName = null;
  this.lastName = null;
  this.email = null;

  // State set event listeners
  this.nameSetListeners = [];
  this.emailSetListeners = [];

  // State change event listeners
  this.nameChangeListeners = [];
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

UserModel.prototype.setName = function(first_name, last_name) {
  this.firstName = first_name;
  this.lastName = last_name;

  for (var i = 0; i < this.nameSetListeners.length; ++i) {
    this.nameSetListeners[i](this.firstName, this.lastName);
  }

  return this;
};

UserModel.prototype.setEmail = function(email) {
  this.email = email;

  for (var i = 0; i < this.emailSetListeners.length; ++i) {
    this.emailSetListeners[i](this.email);
  }

  return this;
};

/**
 * Bind "field set" event listeners 
 */
UserModel.prototype.bindSetName = function(callback) {
  this.nameSetListeners.push(callback); 
  return this;
};

UserModel.prototype.bindSetEmail = function(callback) {
  this.emailSetListeners.push(callback); 
  return this;
};

/**
 * "Field change" functions
 */
UserModel.prototype.changeName = function(first_name, last_name) {
  this.firstName = first_name;
  this.lastName = last_name;
  
  // Notify 'set listeners'
  for (var i = 0; i < this.nameSetListeners.length; ++i) {
    this.nameSetListeners[i](this.firstName, this.lastName);
  }

  // Notify 'change listeners'
  for (var i = 0; i < this.nameChangeListeners.length; ++i) {
    this.nameChangeListeners[i](this.firstName, this.lastName);
  }
  
  return this;
};

UserModel.prototype.changeEmail = function(email) {
  this.email = email;
  
  // Notify 'set' listeners
  for (var i = 0; i < this.emailSetListeners.length; ++i) {
    this.emailSetListeners[i](this.email);
  }

  // Notify 'change' listeners
  for (var i = 0; i < this.emailChangeListeners.length; ++i) {
    this.emailChangeListeners[i](this.email);
  }

  return this;
};

/**
 * Bind "field change" event listeners 
 */
UserModel.prototype.bindChangeName = function(callback) {
  this.nameChangeListeners.push(callback); 
  return this;
};

UserModel.prototype.bindChangeEmail = function(callback) {
  this.emailChangeListeners.push(callback); 
  return this;
};

var ApplicationModel = function() {
  
  /**
   * Private state
   */
  var userModel = null;
  var centerPageModel = null;

  /**
   * Private functions
   */
  var initUserModel = function() {
    userModel = new UserModel(); 
  };

  var initCenterPageModel = function() {
    centerPageModel = new CenterPageModel();
    centerPageModel.init();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    initUserModel();
    initCenterPageModel();
  };

  // Getters
  this.getUserModel = function() {
    return userModel;
  };

  this.getCenterPageModel = function() {
    return centerPageModel;
  };
};

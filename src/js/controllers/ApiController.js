var ApiController = function() {

  /**
   * Private state
   */
  // Apis
  var getStartupDataApiController = null;

  // Event listeners
  var lostConnectionListeners = [];
  var badRequestListeners = [];

  /**
   * Private functions
   */
  // Bind generic event listeners
  var initApiController = function(api) {};

  var configureGetStartupDataApi = function() {
    // Initialize api controller and bind generic handler logic
    getStartupDataApiController = new GetStartupDataApiController();
    initApiController(getStartupDataApiController);
  };

  var configureApis = function() {
    configureGetStartupDataApi(); 
  };

  /**
   * Public functions
   */
  // Lazy loader api controllers
  this.getGetStartupDataApiController = function() {
    return getStartupDataApiController;
  };

  // Register event listeners
  this.bindLostConnection = function(callback) {
    lostConnectionListeners.push(callback);
    return this;
  };

  this.bindBadRequest = function(callback) {
    badRequestListeners.push(callback);
    return this;
  };

  this.init = function() {
    configureApis();
  };
};

var MyExperimentsLogicController = (function() {

  /**
   * Private state
   */
  var myExperiments = [];
  var getConfirmedOrdersApiWrapper = null;
  var myExperimentsView = null;

  /**
   * Private functions
   */
  var initApi = function() {
    console.assert(getConfirmedOrdersApiWrapper === null); 

    // Initialize get-confirmed-order api
    var get_confirmed_order_api = new GetConfirmedOrdersApi(ScopesNetwork);
    getConfirmedOrdersApiWrapper = new ApiControllerWrapper(get_confirmed_order_api);

    // Bind event listeners to get-confirmed-orders api
    getConfirmedOrdersApiWrapper.registerSuccessfulApiCallback(function(json_response, response_keys) {
      clearConfirmedOrders();
      var orders = json_response[response_keys.orders];
      var order_response_keys = response_keys.confirmed_order;
      var short_code_response_keys = response_keys.short_code;
      
      for (var i = 0; i < orders.length; ++i) {
        var order = orders[i];
        var short_code = order[order_response_keys.short_code];

        var short_code = new ShortCode(
          short_code[short_code_response_keys.id],
          short_code[short_code_response_keys.code],
          short_code[short_code_response_keys.alias]
        );

        var confirmed_order = new ConfirmedOrder(
          order[order_response_keys.id],
          order[order_response_keys.scopes_count],
          order[order_response_keys.start_time],
          order[order_response_keys.end_time],
          order[order_response_keys.title],
          order[order_response_keys.description],
          order[order_response_keys.time_ordered],
          order[order_response_keys.price],
          short_code
        );

        addConfirmedOrder(confirmed_order); 
      }
    });

    getConfirmedOrdersApiWrapper.registerLogicalFailedApiCallback(function(response) {
      console.log(response);
      console.log('ERROR: failed to get confirmed orders'); 
    });

    getConfirmedOrdersApiWrapper.registerNonLogicalFailedApiCallback(function(response) {
      console.log(response);
      console.log('ERROR: failed to get confirmed orders due to network error'); 
    });
  };

  var addConfirmedOrder = function(confirm_order) {
    // Store in local cache
    myExperiments.push(confirm_order);  

    // Update MyExperiments view
    myExperimentsView.pushPendingOrder(confirm_order);
  };

  var clearConfirmedOrders = function() {
    // Clear local cache
    myExperiments = [];

    // Clear MyExperiments view
    // TODO...   
  };

  var init = function(my_experiments_view) {
    myExperimentsView = my_experiments_view;

    // Initialize api module
    initApi();

    refreshData(); 
  };

  var refreshData = function() {
    getConfirmedOrdersApiWrapper.fetch(); 
  };

  var getMyExperiments = function() {
    return myExperiments;
  };

  return {
    init: init,
    refreshData: refreshData,
    getMyExperiments: getMyExperiments
  };
})();

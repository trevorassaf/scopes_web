var MyExperimentsPageControllerBackup = function() {

  /**
   * Private state
   */
  var isActive = false;
  var templateStore = null;
  var parentNode = null;
  var getConfirmedOrdersApiWrapper = null;
  var myExperimentControllers = []; // unordered_map keyed on experiment-id
  var myExperimentsPageView = null;

  /**
   * Private functions
   */
  var update = function(experiment_controller) {};

  var updateLocalExperiment = function(fresh_experiment, stale_experiment_controller) {
    var stale_model = stale_experiment_controller.getModel();

    // Check: must be same experiment!
    console.assert(fresh_experiment.getId() == stale_model.getId());

    // Diff fields and update accordingly
    if (fresh_experiment.getTitle() != stale_model.getTitle()) {
      stale_model.setTitle(fresh_experiment.getTitle());    
    }
    
    if (fresh_experiment.getDescription() != stale_model.getDescription()) {
      stale_model.setDescription(fresh_experiment.getDescription());    
    }

    if (fresh_experiment.getPrice() != stale_model.getPrice()) {
      stale_model.setPrice(fresh_experiment.getPrice());    
    }

    if (fresh_experiment.getScopesCount() != stale_model.getScopesCount()) {
      stale_model.setScopesCount(fresh_experiment.getScopesCount());    
    }

    if (fresh_experiment.getExperimentDuration() != stale_model.getExperimentDuration()) {
      stale_model.setExperimentDuration(fresh_experiment.getExperimentDuration());    
    }

    if (fresh_experiment.getStartTime() != stale_model.getStartTime()) {
      stale_model.setStartTime(fresh_experiment.getStartTime());    
    }

    if (fresh_experiment.getStartDate() != stale_model.getStartDate()) {
      stale_model.setStartDate(fresh_experiment.getStartDate());    
    }
    
    if (fresh_experiment.getPaymentStatus() != stale_model.getPaymentStatus()) {
      stale_model.setPaymentStatus(fresh_experiment.getPaymentStatus());    
    }
  };

  var createNewLocalExperiment = function(fresh_experiment) {
    // Check: can't have order with this id!
    console.assert(!myExperimentController.has(fresh_experiment.getId()));

    // Initialize new model
    var model = (new MyExperimentModel())
      .setId(fresh_experiment.getId())
      .setTitle(fresh_experiment.getTitle())
      .setDescription(fresh_experiment.getDescription())
      .setPrice(fresh_experiment.getPrice())
      .setScopesCount(fresh_experiment.getScopesCount())
      .setExperimentDuration(fresh_experiment.getExperimentDuration())
      .setStartTime(fresh_experiment.getStartTime())
      .setStartDate(fresh_experiment.getStartDate())
      .setPaymentStatus(fresh_experiment.getPaymentStatus())
      .setShortCode(fresh_experiment.getShortCode());

    // Create controller, initialize it, add it to local list
    var controller = new MyExperimentController();
    
    controller.init(
      templateStore,
      parentNode,
      model
    );

    myExperimentControllers.set(model.getId(), controller);
  };

  var fetchExperimentsCallback = function(experiments) {
    for (var i = 0; i < experiments.length; ++i) {
      var fresh_experiment = experiments[i];
      if (myExperimentControllers.has(fresh_experiment.getId())) {
        updateLocalExperiment(fresh_experiment, myExperimentControllers[fresh_experiment.getId()]);   
      } else {
      createNewLocalExperiment(fresh_experiment); 
      }
    }
  };

  var initApi = function() {
    console.assert(getConfirmedOrdersApiWrapper === null); 

    // Initialize get-confirmed-order api
    var get_confirmed_order_api = new GetConfirmedOrdersApi(ScopesNetwork);
    getConfirmedOrdersApiWrapper = new ApiControllerWrapper(get_confirmed_order_api);

    getConfirmedOrdersApiWrapper.registerSuccessfulApiCallback(function(json_response, response_keys) {
      // Deserialize orders
      var orders = json_response[response_keys.orders];
      var order_response_keys = response_keys.confirmed_order;
      var short_code_response_keys = response_keys.short_code;
     
      var confirmed_orders = [];

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
        
        confirmed_orders.push(confirmed_order);
      }

      fetchExperimentsCallback(confirmed_orders);
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

  /**
   * Privileged functions
   */
  this.refresh = function() {
    var successful_callback = function(experiments) {
      // TODO...
    };

    // Make api call
    fetchExperiments(successful_callback);
  };

  this.init = function(
    template_store,
    parent_node,
    is_displayed_initially
  ) {
    // Check: view must be inactive to initialize!
    console.assert(!isActive);
    isActive = true;

    templateStore = template_store;
    parentNode = parent_node;

    // Initialize view
    myExperimentsPageView = new MyExperimentsPageView(
      template_store,
      parent_node,
      is_displayed_initially
    );
  };

  this.show = function() {};
  this.hide = function() {};
};

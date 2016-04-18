var MyExperimentController = function() {

  /**
   * Private state
   */
  var myExperimentView = null;
  var myExperimentModel = null; 

  // Page controllers
  var frontPageController = null;

  /**
   * Protected functions
   */
  var handleModelTitleChange = function(title) {
    if (title == null) {
      myExperimentView.setTitlePlaceholder(); 
    } else {
      myExperimentView.setTitle(title);
    }
  };

  var handleViewTitleChange = function(new_title) {
    if (new_title == null || Utils.isWhiteSpace(new_title)) {
      // User removed title. Now, delete title in model and 
      // update ui with default title
      myExperimentModel.setTitle(null);
    } else {
      // Update model
      myExperimentModel.setTitle(new_title.trim());
    }
  };

  var configureCallbacks = function() {
    /**
     * Model --> view data pathways
     */
    myExperimentModel
      .bindTitle(handleModelTitleChange);

    /**
     * View --> model data pathways
     */
    // Attach title change listeners
    myExperimentView.bindTitle(handleViewTitleChange);

    // Attach page nav event listeners
    myExperimentView.bindFrontPageNav(function() {
      myExperimentView.showFrontPage();
    });

    myExperimentView.bindDescriptionNav(function() {
      myExperimentView.showDescriptionPage();
    });

    myExperimentView.bindMonitorNav(function() {
      myExperimentView.showMonitorPage();
    });

    myExperimentView.bindRecordingNav(function() {
      myExperimentView.showRecordingPage();
    });
  };

  var initPageControllers = function() {
    frontPageController = new MyExperimentFrontPageController();
    frontPageController.init(
      myExperimentView.getFrontPageView(),
      myExperimentModel
    );
  };

  /**
   * Privileged functions
   */
  this.init = function(
    view,
    model
  ) {
    myExperimentView = view;
    myExperimentModel = model;

    // Initialize controllers for pages, e.g. front, description
    initPageControllers();

    // Set up data pathways
    configureCallbacks();
  };
};

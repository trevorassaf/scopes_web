var SidePanelController = function(
    template_store,
    new_experiment_page_controller,
    my_experiments_page_controller,
    feedback_page_controller,
    technician_page_controller
) {

  /**
   * Private state
   */
  var sidePanelView = null;
  var templateStore = template_store;

  var newExperimentPageController = new_experiment_page_controller;
  var myExperimentsPageController = my_experiments_page_controller;
  var feedbackPageController = feedback_page_controller;
  var technicianPageController = technician_page_controller;

  /**
   * Privileged functions
   */
  this.init = function() {
    /**
     * Initialize the tab views
     */
    sidePanelView = new SidePanelView(templateStore);
    sidePanelView.init();
  };
};

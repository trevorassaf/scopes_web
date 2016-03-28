var NewExperimentPageView = function(
  template_store,
  parent_node
) {

  /**
   * Page title
   */
  var PAGE_TITLE = 'Add Experiment';

  /**
   * New Experiments Template Id
   */
  var NEW_EXPERIMENT_PAGE_TEMPLATE_ID = 'new-experiment-page-template';

  /**
   * New Experiments Wrapper Class
   */
  var NEW_EXPERIMENT_WRAPPER_CLASS = 'new-experiment-page-wrapper';

  /**
   * Scopes count form view
   */
  var scopesCountNode = {
    className: 'scopes-count-form',
    node: null
  };

  var SCOPES_COUNT_TITLE_LABEL = 'How many scopes would you like?';

  var SCOPES_COUNT_UNIT_LABELS = {
    singular: 'scope',
    plural: 'scopes'
  };

  var SCOPES_COUNT_VALUE_RANGE = {
    min: 0,
    max: 15,
    step: 1
  };

  /**
   * Experiment duration form node 
   */
  var experimentDurationNode = {
    className: 'experiment-duration-form',
    node: null
  };

  /**
   * Experiment time form node
   */
  var experimentTimeNode = {
    className: 'experiment-time-form',
    node: null
  };

  var EXPERIMENT_DURATION_TITLE_LABEL = 'How long is your experiment?';

  var EXPERIMENT_DURATION_UNIT_LABELS = {
    singular: 'hour',
    plural: 'hours'
  };

  var EXPERIMENT_DURATION_VALUE_RANGE = {
    min: 0,
    max: 12,
    step: 1
  };

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var rootNode = null;

  var scopesCountFormView = null;
  var experimentDurationFormView = null;
  var experimentTimeFormView = null;

  /**
   * Private functions
   */
  var initScopeCountView = function() {
    var slider_form_view = new SliderFormView(
      templateStore,
      SCOPES_COUNT_TITLE_LABEL,
      SCOPES_COUNT_UNIT_LABELS,
      SCOPES_COUNT_VALUE_RANGE
    ); 

    slider_form_view.init(scopesCountNode.node);
    slider_form_view.setValue(0);
    return slider_form_view;
  };

  var initExperimentDurationView = function() {
    var slider_form_view = new SliderFormView(
      templateStore,    
      EXPERIMENT_DURATION_TITLE_LABEL,
      EXPERIMENT_DURATION_UNIT_LABELS,
      EXPERIMENT_DURATION_VALUE_RANGE
    );

    slider_form_view.init(experimentDurationNode.node);
    slider_form_view.setValue(0);
    return slider_form_view;
  };

  var initExperimentTimeFormView = function() {
    var form_view = new ExperimentTimeFormView(
      templateStore,
      experimentTimeNode.node
    );

    form_view.init();
    return form_view;
  };

  var bindNodes = function() {
    scopesCountNode.node = Utils.bindNode(
      rootNode,
      scopesCountNode.className
    );

    experimentDurationNode.node = Utils.bindNode(
      rootNode,
      experimentDurationNode.className
    );

    experimentTimeNode.node = Utils.bindNode(
      rootNode,
      experimentTimeNode.className
    );
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      NEW_EXPERIMENT_PAGE_TEMPLATE_ID,
      parentNode,
      NEW_EXPERIMENT_WRAPPER_CLASS
    );

    // Bind all ui dom nodes
    bindNodes();
    
    // Initialize child views
    scopesCountFormView = initScopeCountView(); 
    experimentDurationFormView = initExperimentDurationView();
    experimentTimeFormView = initExperimentTimeFormView();
  };

  this.getTitle = function() {
    return PAGE_TITLE;
  };

  this.hide = function() {
    Utils.hideNode(rootNode);
  };

  this.show = function() {
    Utils.showNode(rootNode);
  };
};

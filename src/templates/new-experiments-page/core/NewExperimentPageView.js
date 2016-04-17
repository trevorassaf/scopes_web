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

  var experimentDurationController = null;
  
  /**
   * Experiment time form node
   */
  var experimentTimeNode = {
    className: 'experiment-time-form',
    node: null
  };

  /**
   * Short code picker input field
   */
  var shortCodePickerNode = {
    className: 'short-code-form', 
    node: null
  };

  var SHORT_CODE_TITLE_LABEL = 'Select a payment method';

  /**
   * Confirm order form view dom node
   */
  var confirmOrderFormViewNode = {
    className: 'confirm-order-form',
    node: null
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
  var shortCodePickerFormView = null;
  var confirmExperimentFormView = null;

  /**
   * Private functions
   */
  var initScopeCountView = function() {
    var slider_form_view = new SliderFormView(
      templateStore,
      scopesCountNode.node,
      SCOPES_COUNT_TITLE_LABEL,
      SCOPES_COUNT_UNIT_LABELS
    ); 

    slider_form_view.init();
    return slider_form_view;
  };

  var initExperimentDurationView = function() {
    var slider_form_view = new SliderFormView(
      templateStore,    
      experimentDurationNode.node,
      EXPERIMENT_DURATION_TITLE_LABEL,
      EXPERIMENT_DURATION_UNIT_LABELS
    );

    slider_form_view.init();
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

  var initShortCodePickerFormView = function() {
    // Initialize form view
    var form_view = new ShortCodeFormView(
      templateStore,
      shortCodePickerNode.node
    );
    form_view.init();
   
    // Initialize drop-down model
    // var drop_down_model = new DropDownModel();
    // var drop_down_items = [
    //   new DropDownItemModel("SHORT", "SHORT", {}),
    //   new DropDownItemModel("CODE", "CODE", {}),
    //   new DropDownItemModel("SHIT", "SHIT", {})
    // ];
    // drop_down_model.setDropDownItems(drop_down_items);
    //
    // // Initialize drop-down model controller
    // var drop_down_controller = new DropDownController();
    // drop_down_controller.setModel(drop_down_model);
    //
    // form_view.init(drop_down_controller);

    return form_view;
  };

  var initConfirmExperimentFormView = function() {
    // Initialize form view
    var form_view = new ConfirmOrderFormView(
      templateStore,
      confirmOrderFormViewNode.node
    );

    form_view.init();

    // Initialize form controller
    // var form_controller = new ConfirmOrderFormController();
    // form_controller.init(
    //   form_view,
    //   experimentDurationController.getModel()
    // );
    return form_view;
  };

  var bindNodes = function() {
    Utils.bindNodeInfo(rootNode, scopesCountNode);
    Utils.bindNodeInfo(rootNode, experimentDurationNode);
    Utils.bindNodeInfo(rootNode, experimentTimeNode);
    Utils.bindNodeInfo(rootNode, shortCodePickerNode);
    Utils.bindNodeInfo(rootNode, confirmOrderFormViewNode);
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
    shortCodePickerFormView = initShortCodePickerFormView();
    confirmExperimentFormView = initConfirmExperimentFormView();
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

  this.getScopesCountFormView = function() {
    return scopesCountFormView;
  };
  
  this.getExperimentDurationFormView = function() {
    return experimentDurationFormView;
  };

  this.getExperimentTimeFormView = function() {
    return experimentTimeFormView;   
  };
  
  this.getShortCodeFormView = function() {
    return shortCodePickerFormView;
  };

  this.getConfirmExperimentFormView = function() {
    return confirmExperimentFormView;
  };
};

var ExperimentTimeFormView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'experiment-time-form-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'experiment-time-form-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  var experimentTimePickerView = null;
  var experimentTimePickerModel = null;
  var experimentTimePickerController = null;

  var experimentDatePickerView = null;

  /**
   * Dom nodes
   */
  var experimentTimePickerNode = {
    className: 'exp-time-picker',
    node: null
  };
  
  var experimentDatePickerNode = {
    className: 'exp-date-picker',
    node: null
  };

  /**
   * Private functions
   */
  var initExperimentTimePickerView = function() {
    // Bind nodes
    Utils.bindNodeInfo(rootNode, experimentTimePickerNode);


    // Create data model
    var drop_down_items = [
      new DropDownItemModel("10:00", "10:00", {}),
      new DropDownItemModel("10:30", "10:30", {}),
      new DropDownItemModel("11:00", "11:00", {})
    ];

    experimentTimePickerModel = new DropDownModel();
    experimentTimePickerModel.setDropDownItems(drop_down_items);

    // Create view
    experimentTimePickerView = new DropDownView(
      templateStore,
      experimentTimePickerNode.node
    );

    experimentTimePickerView.init(
      experimentTimePickerModel,
      'device:access-time'
    );

    // Create controller
    experimentTimePickerController = new DropDownController();
    experimentTimePickerController
      .setModel(experimentTimePickerModel)
      .setView(experimentTimePickerView);

    // Initialize view
    // experimentTimePickerView = new TimePicker(
    //   templateStore,
    //   experimentTimePickerNode.node,
    //   {minutes: 0, hours: 10},
    //   {minutes: 0, hours: 19},
    //   30
    // ); 
    //
    // experimentTimePickerView.init();
  };

  var initExperimentDatePickerView = function() {
    // Bind nodes
    Utils.bindNodeInfo(rootNode, experimentDatePickerNode);

    // Create data model
    var min_advance_day_count = 14;
    var max_advance_month_count = 4;
    var invalid_days_of_the_week = [0, 6];
    var invalid_dates = [
      new Date(2016, 4, 3),
      new Date(2016, 4, 4),
      new Date(2016, 4, 5)
    ];

    // Create model
    var date_picker_model = new DatePickerModel();
    date_picker_model
      .setSelectedDate(6)
      .setSelectedMonth(3)
      .setSelectedYear(2016)
      .setViewedMonthAndYear(3, 2016)
      .setMinAdvanceDayCount(min_advance_day_count)
      .setMaxAdvanceMonthCount(max_advance_month_count)
      .setInvalidDaysOfTheWeek(invalid_days_of_the_week)
      .setInvalidDates(invalid_dates);

    // Create view
    var date_picker_view = new DatePickerView(
      templateStore,
      experimentDatePickerNode.node
    );

    date_picker_view.init(date_picker_model);
  };

  var initFormElements = function() {
    initExperimentTimePickerView();
    initExperimentDatePickerView();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Synthesize template into document
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS
    ); 

    // Initialize form elements 
    initFormElements();
  };
};

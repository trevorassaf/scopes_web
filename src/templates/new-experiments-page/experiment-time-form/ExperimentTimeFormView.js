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

  var experimentDatePickerController = null;

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

    // Determine first open date
    var starting_date = new Date();
    starting_date.setDate(
        starting_date.getDate() + min_advance_day_count
    );

    while (
      Utils.contains(starting_date.getDay(), invalid_days_of_the_week) ||
      Utils.contains(starting_date, invalid_dates)    
    ) {
      starting_date.setDate(starting_date.getDate() + 1); 
      // TODO handle case in which NO legal starting dates exist!
    }

    
    // Create model
    var date_picker_model = new DatePickerModel();
    date_picker_model
      .setSelectedDate(starting_date.getDate())
      .setSelectedMonth(starting_date.getMonth())
      .setSelectedYear(starting_date.getFullYear())
      .setViewedMonthAndYear(
        starting_date.getMonth(),
        starting_date.getFullYear()
      )
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

    // Initialize controller
    experimentDatePickerController = new DatePickerController();   
    experimentDatePickerController
      .setModel(date_picker_model)
      .setView(date_picker_view);
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

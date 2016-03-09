function StaticCalendar(
  template_store,
  parent_node,
  selected_date_timestamp
) {

  /**
   * Template name constants
   */
  var TEMPLATE_ID = '#static-calendar-template';

  /**
   * Html class names
   */
  var DATE_CLASS = 'date';
  var DATE_LABEL_CLASS = 'date-label';
  var WEEK_CLASS = 'week';
  var SELECTABLE_DATE_CLASS = 'selectable-date';
  
  /**
   * Html attribute names
   */
  var SELECTED_DATE_ATTR = 'selected-date';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var selectedDateTimestamp = selected_date_timestamp;
  var staticCalendar = null;

  /**
   * Dom nodes
   */
  var rootNode = {
    className: 'static-calendar-wrapper',
    node: null
  };

  var selectedDateDisplayNode = {
    className: 'selected-date-label',
    node: null
  };

  var domContainerNode = {
    className: 'dom-container',
    node: null
  }; 

  /**
   * Private functions
   */
  var bindClassBoundNode = function(node_info) {
    elements = parentNode.getElementsByClassName(node_info.className);
    console.assert(elements.length === 1);
    node_info.node = elements[0];
  };

  var synthesizeTemplate = function() {
    // Copy and bind template
    var static_calendar_template = templateStore.import.querySelector(TEMPLATE_ID);
    var static_calendar_clone = document.importNode(static_calendar_template.content, true);
    parentNode.appendChild(static_calendar_clone);
  };

  var bindInternalNodes = function() {
    // Bind static html nodes
    bindClassBoundNode(rootNode);
    bindClassBoundNode(selectedDateDisplayNode);
    bindClassBoundNode(domContainerNode);
  };

  var generateDateLabelNode = function(date) {
    var date_label_node = document.createElement('div');
    var label = document.createElement('span');
    label.className = DATE_LABEL_CLASS;
    label.innerHTML = date;
    date_label_node.appendChild(label);
    return date_label_node;
  };

  var generateSelectableDateNode = function(date) {
    var selectable_date_node = generateDateNode();
    var date_label_node = generateDateLabelNode(date);
    date_label_node.className = SELECTABLE_DATE_CLASS;
    selectable_date_node.appendChild(date_label_node);
    return selectable_date_node; 
  };
  
  var generateDateNode = function() {
    var date_node = document.createElement('div');
    date_node.className = DATE_CLASS;
    return date_node;
  };

  var generateBlankDateNode = function() {
    return generateDateNode();
  };
  
  /**
   * generateWeekNode()
   * - dynamically generate the node for 1 row in the calendar
   */
  function generateWeekNode() {
    var week_node = document.createElement('div');
    week_node.className = WEEK_CLASS;
    return week_node;
  };

  /**
   * setMonthDisplayGrid()
   * @param DateObj selected_date: {year, month, date}
   */
  var setMonthDisplayGrid = function(year, month, selected_date) {
    // Clear existing children nodes 
    Utils.removeDomChildren(domContainerNode.node);

    // Assemble dynamic month display grid
    var new_date = new Date(year, month);
    var starting_day_idx = new_date.getUTCDay();

    // Get number of days in month
    var num_days_in_month_obj = new Date(year, month + 1, 0); // hacky :/
    var num_days_in_month = num_days_in_month_obj.getDate();

    // Generate dynamic html nodes for days in last week of previous month that appear
    // in first week of this month, e.g. last few days
    var current_week = generateWeekNode();
    domContainerNode.node.appendChild(current_week);

    console.log('starting day idx');
    console.log(starting_day_idx);

    for (var i = 0; i < starting_day_idx; ++i) {
      var blank_node = generateBlankDateNode();
      current_week.appendChild(blank_node);
    }
    
    // Generate dynamic html nodes for displaying selectable days in month
    for (var i = 1; i <= num_days_in_month; ++i) { // fewer ops with these loop conditions
      // Insert rows for calendar weeks
      if (current_week.childNodes.length == 7) {
        current_week = generateWeekNode();
        domContainerNode.node.appendChild(current_week);
      }
     
      var selectable_date = generateSelectableDateNode(i);

      if (i == selected_date) {
        selectable_date.setAttribute(SELECTED_DATE_ATTR, '');
        console.log(selectable_date);
      }

      current_week.appendChild(selectable_date);
    }
  };

  var initUi = function() {
    // Generate timestamp string and copy into display ui node
    selectedDateDisplayNode.node.innerHTML = Utils.makeDateString(selectedDateTimestamp);

    // Configure dynamic ui nodes
    var js_date = new Date(selectedDateTimestamp);
    setMonthDisplayGrid(
      js_date.getUTCFullYear(),
      js_date.getUTCMonth(),
      js_date.getUTCDate()
    );
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    synthesizeTemplate();
    bindInternalNodes();
    initUi();
  };
};

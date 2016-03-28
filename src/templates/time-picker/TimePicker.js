function TimePicker(
  template_store,
  parent_node,
  start_time, // {minute, hour}
  end_time,   // {minute, hour}
  time_interval // min
) {
  /**
   * Html dom attributes
   */
  var HIDDEN_ATTR = 'hidden-dropdown';
  var SHADOW_BORDER_ATTR = 'shadow-border';
  var TIME_ATTR = 'time';

  /**
   * Html class names
   */
  var TIME_LABEL_CLASS = 'time-label';
  var TIME_PICKER_OPTION_CLASS = 'time-picker-option';
  var ROOT_WRAPPER_CLASS = 'time-picker-wrapper';

  /**
   * Html template id name
   */
  var MAIN_TEMPLATE_ID = 'time-picker-template';
  var OPTION_TEMPLATE_ID = 'time-picker-option-template';

  /**
   * Meridian designations 
   */
  var HOUR_MIN_SEPARATOR = ':';
  var AM_DESIGNATION = 'am';
  var PM_DESIGNATION = 'pm';

  /**
   * Initial state
   */
  var INITIAL_IS_DROP_DOWN_OPEN = false;

  // Private state
  var templateStore = template_store;
  var parentNode = parent_node;

  var startTime = start_time;
  var endTime = end_time;
  var timeInterval = time_interval; 
  var isDropDownOpen = false;
  var currentTime = null; // hours * 60 + minutes

  /**
   * Internal dom nodes
   */
  var inputFieldNode = {
    className: 'input-field',
    node: null
  };

  var inputFieldWrapperNode = {
    className: 'input-field-wrapper',
    node: null
  };

  var dropDownNode = {
    className: 'time-dropdown',
    node: null
  };

  // Private functions
  var openDropDown = function() {
    isDropDownOpen = true;    
    rootNode.removeAttribute(HIDDEN_ATTR);
    inputFieldNode.node.setAttribute(SHADOW_BORDER_ATTR, '');
  };

  var closeDropDown = function() {
    isDropDownOpen = false;    
    rootNode.setAttribute(HIDDEN_ATTR, '');
    inputFieldNode.node.removeAttribute(SHADOW_BORDER_ATTR);
  };

  /**
   * configureAvailableTimes()
   * - compute available times and initialize ui elements
   * @pre-condition: root initialized and dom synthesized
   */
  var configureAvailableTimes = function() {
    var current_time = startTime.hours * 60 + startTime.minutes;
    var next_time = current_time + time_interval;
    var end_time = endTime.hours * 60 + endTime.minutes;

    while (next_time <= end_time) {
      // Synthesize time-picker-option template
      var time_picker_option = Utils.synthesizeTemplateIntoList(
        templateStore,
        OPTION_TEMPLATE_ID,
        dropDownNode.node,
        TIME_PICKER_OPTION_CLASS
      );

      // Hack!
      time_picker_option.setAttribute(TIME_ATTR, current_time);
      var time_label = time_picker_option.querySelector('.' + TIME_LABEL_CLASS);
      time_label.innerHTML = stringifyTime(current_time);

      current_time = next_time;
      next_time += time_interval;
    }
  };

  var applyDoubleDigitTimeFormat = function(numeric_time_element) {
    return (numeric_time_element < 10)
      ? '0' + numeric_time_element 
      : numeric_time_element;
  };

  var stringifyTimeForInputField = function(time) {
    var string_time = stringifyTime(time);
    return string_time.replace(/&nbsp/gi, '');
  };

  /**
   * stringifyTime()
   * - convert numeric time to string format 
   * @param: uint time: hours * 60 + minutes
   * @return 'hh:mm' 
   */
  var stringifyTime = function(time) {
    // Stringify minutes
    var minutes = time % 60;
    var minutes_string = applyDoubleDigitTimeFormat(minutes);

    // Stringify hours
    var hours = (time - minutes) / 60;

    var meridian_designation = AM_DESIGNATION;
    if (hours > 12) {
      meridian_designation = PM_DESIGNATION;   
      hours = hours % 12;
    } 

    var hours_string = (hours < 10)
      ? '&nbsp&nbsp' + hours
      : hours;

    return hours_string + HOUR_MIN_SEPARATOR + minutes_string + ' ' + meridian_designation;
  };

  /**
   * initNodes()
   * - bind all internal nodes and configure event listeners
   */
  var initNodes = function() {
    // Bind dom nodes
    inputFieldNode.node = Utils.bindNode(
      rootNode,
      inputFieldNode.className
    );
    
    inputFieldWrapperNode.node = Utils.bindNode(
      rootNode,
      inputFieldWrapperNode.className
    );
    
    dropDownNode.node = Utils.bindNode(
      rootNode,
      dropDownNode.className
    );

    // Configure event listeners
    inputFieldWrapperNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown(); 
      } else {
        openDropDown();
      }
    };

    dropDownNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown();
      } 

      // Capture selected time
      for (var i in event.path) {
        var node = event.path[i];
        if (hasClass(TIME_PICKER_OPTION_CLASS, node)) {
          var numeric_time = node.getAttribute(TIME_ATTR); 
          inputFieldNode.node.innerHTML = stringifyTimeForInputField(numeric_time);
          currentTime = numeric_time;
          return;
        }
      }
    };

    // Hide time picker if user clicks off the screen
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_id in event.path) {
        var node = event.path[node_id];
        // User clicked on the time-picker, so don't hide it!
        if (node == rootNode) {
          return;
        }
      }    

      // User clicked off the time-picker, so hide it!
      closeDropDown();
    });
  };

  // Start with closed or open drop-down (as specified by default param)
  var initDisplay = function() {
    if (INITIAL_IS_DROP_DOWN_OPEN) {
      openDropDown();
    } else {
      closeDropDown();
    }

    // Initialize start time
    var time_picker_options = rootNode.getElementsByClassName(TIME_PICKER_OPTION_CLASS);
    var starting_time_option = time_picker_options[0].getAttribute(TIME_ATTR);
    inputFieldNode.node.innerHTML = stringifyTimeForInputField(starting_time_option);
    currentTime = starting_time_option;
  };

  function setInitialStateInternal() {
    // Initialize the ui
    initDisplay();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Synthesize html template into document
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      MAIN_TEMPLATE_ID,
      parentNode,
      ROOT_WRAPPER_CLASS
    );

    // Initialize nodes: dom elements and event listeners
    initNodes(); 
  
    // Compute available times and initialize ui state
    configureAvailableTimes();
    setInitialStateInternal();
  };

  this.getSelectedTime = function() {
    var num_minutes = currentTime % 60;
    var num_hours = (currentTime - num_minutes) / 60;
    return {
      hours: num_hours,
      minutes: num_minutes,
      seconds: 0
    };
  };

  this.setInitialState = function() {
    setInitialStateInternal();
  };
};

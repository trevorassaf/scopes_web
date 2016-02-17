function TimePicker(
  template_store,
  id,
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

  /**
   * Html template id name
   */
  var MAIN_TEMPLATE_ID = '#time-picker-template';
  var OPTION_TEMPLATE_ID = '#time-picker-option-template';

  /**
   * Meridian designations 
   */
  var HOUR_MIN_SEPARATOR = ':';
  var AM_DESIGNATION = 'am';
  var PM_DESIGNATION = 'pm';

  // Private state
  var templateStore = template_store;
  var startTime = start_time;
  var endTime = end_time;
  var timeInterval = time_interval; 
  var isDropDownOpen = false;
  var currentTime = null; // hours * 60 + minutes

  // Dom Nodes
  var rootNode = {
    nodeId: id,
    node: null
  };
  
  /**
   * Internal dom nodes
   */

  var timePickerWrapperNode = {
    class: 'time-picker-wrapper',
    node: null
  };

  var inputFieldNode = {
    class: 'input-field',
    node: null
  };

  var dropDownNode = {
    class: 'time-dropdown',
    node: null
  };

  // Private functions
  /**
   * synthesizeTimePickerTemplate()
   * - copy template and insert into root node
   * @pre-condition: root node is initialized 
   */
  var synthesizeTimePickerTemplate = function() {
    var time_picker_template = templateStore.import.querySelector(MAIN_TEMPLATE_ID);
    var time_picker_clone = document.importNode(time_picker_template.content, true);
    rootNode.node.appendChild(time_picker_clone);
  };

  var openDropDown = function() {
    isDropDownOpen = true;    
    timePickerWrapperNode.node.removeAttribute(HIDDEN_ATTR);
    inputFieldNode.node.setAttribute(SHADOW_BORDER_ATTR, '');
  };

  var closeDropDown = function() {
    isDropDownOpen = false;    
    timePickerWrapperNode.node.setAttribute(HIDDEN_ATTR, '');
    inputFieldNode.node.removeAttribute(SHADOW_BORDER_ATTR);
  };

  /**
   * configureAvailableTimes()
   * - compute available times and initialize ui elements
   * @pre-condition: root initialized and dom synthesized
   */
  var configureAvailableTimes = function() {
    // Bind template node for time-picker-option
    var time_picker_option_template = templateStore.import.querySelector(OPTION_TEMPLATE_ID);

    var current_time = startTime.hours * 60 + startTime.minutes;
    var next_time = current_time + time_interval;
    var end_time = endTime.hours * 60 + endTime.minutes;

    while (next_time <= end_time) {
      // Create new time-picker-option html element
      var current_time_string = stringifyTime(current_time); 
      var time_picker_option_clone = document.importNode(time_picker_option_template.content, true);

      // Incorporate into time-option list
      dropDownNode.node.appendChild(time_picker_option_clone);

      var new_time_picker_option_list = document.getElementsByClassName(TIME_PICKER_OPTION_CLASS);
      var new_time_picker_option = new_time_picker_option_list[new_time_picker_option_list.length - 1];
      new_time_picker_option.setAttribute(TIME_ATTR, current_time);
      var time_label = new_time_picker_option.querySelector('.' + TIME_LABEL_CLASS);
      time_label.innerHTML = current_time_string;

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
    return string_time.replace(/&nbsp;/g, '');
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
   * bindInternalNode()
   * - bind the specified dom node (must be internal to this time-picker)
   * @param: Obj internal_node: internal dom node (see 'inputFieldNode' for structure)
   * @pre-condition: root node bound 
   */
  var bindInternalNode = function(internal_node) {
    // We bind internal nodes once only!
    console.assert(internal_node.node == null); 

    // Fetch internal node by class
    var node_set = rootNode.node.getElementsByClassName(internal_node.class);

    // We should only find one *internal* node with this class
    console.assert(node_set.length == 1);

    internal_node.node = node_set[0];
  };

  /**
   * initNodes()
   * - bind all internal nodes and configure event listeners
   */
  var initNodes = function() {
    // Bind top-level node in time-picker template 
    bindInternalNode(timePickerWrapperNode);

    // Bind input field and configure event listener
    bindInternalNode(inputFieldNode);

    inputFieldNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown(); 
      } else {
        openDropDown();
      }
    };

    // Bind time dropdown field and configure event listener
    bindInternalNode(dropDownNode);

    dropDownNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown();
      } 

      // Capture selected time
      for (var i in event.path) {
        var node = event.path[i];
        if (hasClass(TIME_PICKER_OPTION_CLASS, node.className)) {
          var numeric_time = node.getAttribute(TIME_ATTR); 
          inputFieldNode.node.innerHTML = stringifyTimeForInputField(numeric_time);
          return;
        }
      }
    };

    // Hide time picker if user clicks off the screen
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_id in event.path) {
        var node = event.path[node_id];
        // User clicked on the time-picker, so don't hide it!
        if (node.id == rootNode.node.id) {
          return;
        }
      }    

      // User clicked off the time-picker, so hide it!
      closeDropDown();
    });
  };

  // Start with closed or open drop-down (as specified by default param)
  var initDisplay = function() {
    if (isDropDownOpen) {
      openDropDown();
    } else {
      closeDropDown();
    }

    // Initialize start time
    var time_picker_options = rootNode.node.getElementsByClassName(TIME_PICKER_OPTION_CLASS);
    var starting_time_option = time_picker_options[0].getAttribute(TIME_ATTR);
    inputFieldNode.node.innerHTML = stringifyTimeForInputField(starting_time_option);
  };

  // Privileged functions
  this.init = function() {
    // We only init once!
    console.assert(rootNode.node == null);

    // Bind root node
    rootNode.node = document.getElementById(rootNode.nodeId);
    
    // Synthesize the template and copy into root node
    synthesizeTimePickerTemplate();

    // Initialize nodes: dom elements and event listeners
    initNodes(); 
    
    // Compute available times and initialize ui elements 
    configureAvailableTimes();

    // Initialize the ui
    initDisplay();
  };
};

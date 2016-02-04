window.onload = function() {
  var Calendar = (function(calendar_id) {

    /**
     * Attribute names
     */
    SELECTED_DATE_ATTR = 'selected';
    DISALLOWED_DATE_ATTR = 'disallowed';
    MONTH_OVERFLOW_ATTR = 'month-overflow';

    /**
     * Dom nodes
     */
    // Calendar root node
    var id = calendar_id;
    var calendarRootNode = null;
    
    // Selected day nodes
    var currentDayNode = null;

    /**
     * Dom node info
     */
    // Selected date node info
    var selectedYearLabelNodeInfo = {
      className: 'selected-year-label',
      node: null
    };

    var selectedDateLabelNodeInfo = {
      className: 'selected-date-label',
      node: null
    };

    // Month nav node info 
    var monthNavDisplayNodeInfo = {
      className: 'month-label',
      node: null
    };

    var decrementMonthNavNodeInfo = {
      className: 'decrement-month-container',
      node: null
    };
    
    var incrementMonthNavNodeInfo = {
      className: 'increment-month-container',
      node: null
    };
    
    // Selectable dates node info
    var selectableDaysContainerNodeInfo = {
      className: 'selectable-dates-container',
      node: null
    };

    /**
     * fetchClassBoundDomNode()
     * - fetch the dom node indicated by the provided class-name
     * @param Object node_info: datastructure for the node (see above for example)
     */
    var fetchClassBoundDomNode = function(node_info) {
      elements = calendarRootNode.getElementsByClassName(node_info.className);
      console.assert(elements.length == 1);
      node_info.node = elements[0];
    };

    /**
     * init()
     * - initialize calendar state and ui
     */
    var init = function() {
      /**
       * Fetch dom nodes
       */
      // Fetch root calendar nodes
      calendarRootNode = document.getElementById(id);
      console.assert(calendarRootNode != null);

      console.log(this);

      // Fetch selected date display nodes
      fetchClassBoundDomNode(selectedYearLabelNodeInfo);
      fetchClassBoundDomNode(selectedDateLabelNodeInfo);

      // Fetch month nav nodes
      fetchClassBoundDomNode(monthDisplayLabelNode);
      fetchClassBoundDomNode(decrementMonthNavNode);
      fetchClassBoundDomNode(incrementMonthNavNode);
    }; 

    return {
      init: init
    };
  });

  calendar = new Calendar('calendar-id');
  calendar.init();
};

var Utils = (function() {

  var CLASS_NAME_PROPERTY = "className";

  var HIDDEN_ATTR = 'hidden';

  // Timestamp delimiters
  var DATE_DELIMITER = "-";
  var TIME_DELIMITER = ":";
  var DATE_TIME_SEPERATOR = " ";

  // this.hasClass = function(expected_class, node) {
  //   if (!(CLASS_NAME_PROPERTY in node)) {
  //     return false;
  //   }
  //
  //   var node_class = node[CLASS_NAME_PROPERTY];
  //   var class_idx = node_class.indexOf(expected_class);
  //   
  //   if (class_idx == -1) {
  //     return false;
  //   }
  //
  //   return (class_idx == 0 || node_class.charAt(class_idx - 1) == ' ')
  //     && (expected_class.length + class_idx == node_class.length
  //       || node_class.charAt(expected_class.length + class_idx) == ' ');
  // };

  this.hasClass = function(class_name, node) {
    console.assert(node != null);
    return 'classList' in node && node.classList.contains(class_name);
  };
  
  this.makePriceString = function(price) {

    // Group thousands with commas 
    var price_str = "";
    var price_in_dollars = Math.floor(price);
    
    var i = 1;
    var j = 1000;

    while (j < price_in_dollars) {
      var codon = Math.floor((price_in_dollars % j) / i);
      price_str = "," + codon.toString().concat(price_str);
      i = j;
      j *= 1000;
    }

    var leading_digits = Math.floor(price_in_dollars / i);
    price_str = leading_digits.toString().concat(price_str);

    // Stringify decimal digits
    var cents = Math.floor(price * 100) % 100;
    var cents_str = cents.toString();
    if (cents_str.length === 1) {
      cents_str = "0".concat(cents_str);
    }
    console.assert(cents_str.length === 2);

    cents_str = ".".concat(cents_str);
    return price_str.concat(cents_str);
  };

  this.stringifyNumberWithEnforcedDigitCount = function(number, digit_count) {
    var number_string = number.toString();
    console.assert(number_string.length <= digit_count);

    if (number_string.length < digit_count) {
      var zero_prefix = "0".repeat(digit_count - number_string.length);
      number_string = zero_prefix.concat(number_string);
    }

    return number_string;
  };

  /**
   * makeTimestampString()
   * @param DateObj date: {year, month, date}
   * @param TimeObj time: {hours, minutes, seconds}
   *   - 'hours' is in military time
   */
  this.makeTimestampString = function(date, time) {
    return date.year.toString() + DATE_DELIMITER +
      stringifyNumberWithEnforcedDigitCount(date.month, 2) + DATE_DELIMITER +
      stringifyNumberWithEnforcedDigitCount(date.date, 2) + DATE_TIME_SEPERATOR +
      stringifyNumberWithEnforcedDigitCount(time.hours, 2) + TIME_DELIMITER +
      stringifyNumberWithEnforcedDigitCount(time.minutes, 2) + TIME_DELIMITER +
      stringifyNumberWithEnforcedDigitCount(time.seconds, 2);
  };

  this.makeDateString = function(timestamp) {
    var js_date = new Date(timestamp);
    var serializeable_date = new SerializeableDate(
      js_date.getUTCFullYear(),
      js_date.getUTCMonth(),
      js_date.getUTCDate()
    );
    return serializeable_date.serialize();
  };

  /**
   * removeDomChildren()
   *   - remove all children from dom node
   * @param DOMElemet dom_node: some dom node
   */
  this.removeDomChildren = function(dom_node) {
    while (dom_node.firstChild) {
      dom_node.removeChild(dom_node.firstChild);
    }
  };

  this.makeTimestampIntervalString = function(starting_timestamp, ending_timestamp) {
    // Convert to native js date objects
    var starting_js_date = new Date(starting_timestamp);
    var ending_js_date = new Date(ending_timestamp);

    var serializeable_starting_date = new SerializeableDate(
      starting_js_date.getUTCFullYear(),
      starting_js_date.getUTCMonth(),
      starting_js_date.getUTCDate()
    );

    var serializeable_starting_time = new SerializeableTime(
      starting_js_date.getHours(),
      starting_js_date.getMinutes(),
      starting_js_date.getSeconds()
    );

    var interval_string = serializeable_starting_date.serialize() + ' ' +
        serializeable_starting_time.serializeWithoutSeconds() + ' - ';

    var serializeable_ending_time = new SerializeableTime(
      ending_js_date.getHours(),
      ending_js_date.getMinutes(),
      ending_js_date.getSeconds()
    );

    if (starting_js_date.getUTCFullYear() == ending_js_date.getUTCFullYear() &&
        starting_js_date.getUTCMonth() == ending_js_date.getUTCMonth() &&
        starting_js_date.getUTCDate() == ending_js_date.getUTCDate()
    ) {
      return interval_string + serializeable_ending_time.serializeWithoutSeconds(); 
    }
    
    var serializeable_ending_date = new SerializeableDate(
      ending_js_date.getUTCFullYear(),
      ending_js_date.getUTCMonth(),
      ending_js_date.getUTCDate()
    );

    return interval_string + serializeable_ending_date.serialize() + ' ' + 
        serializeable_ending_time.serializeWithoutSeconds();
  };

  this.synthesizeTemplate = function(
    template_store,
    template_id,
    parent_node,
    class_name
  ) {
    // Clear children from parent-node
    Utils.removeDomChildren(parent_node);

    // Clone template
    var raw_template = template_store.import.querySelector('#' + template_id);  
    var template_clone = document.importNode(raw_template.content, true);

    // Insert clone
    parent_node.appendChild(template_clone);
    var activated_clones = parent_node.getElementsByClassName(class_name);
    console.assert(activated_clones.length == 1);
    
    return activated_clones[0];
  };

  this.synthesizeTemplateIntoList = function(
    template_store,
    template_id,
    parent_node,
    class_name
  ) {
    // Clone template
    var raw_template = template_store.import.querySelector('#' + template_id);
    var template_clone = document.importNode(raw_template.content, true);

    // Insert clone
    parent_node.appendChild(template_clone);
    var activated_clones = parent_node.getElementsByClassName(class_name);
    console.assert(activated_clones.length > 0);

    return activated_clones[activated_clones.length - 1];
  };

  this.bindNode = function(
    parent_node,
    class_name
  ) {
    var node_list = parent_node.getElementsByClassName(class_name);
    console.assert(node_list.length == 1);
    return node_list[0];
  };

  this.bindNodeInfo = function(parent_node, node_info) {
    node_info.node = Utils.bindNode(
      parent_node,
      node_info.className
    );
  };

  this.hideNode = function(node) {
    node.setAttribute(HIDDEN_ATTR, ''); 
  };

  this.showNode = function(node) {
    node.removeAttribute(HIDDEN_ATTR);
  };

  this.bindClickBeyondNode = function(node, callback) {
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_idx in event.path) {
        var current_node = event.path[node_idx];
        // User clicked on the time-picker, so don't hide it!
        if (current_node == node) {
          return;
        }
      }    

      callback();
    });
  };

  var compareDates = function(date1, date2) {
    // Compare years
    if (date1.getFullYear() < date2.getFullYear()) {
      return -1;
    }

    if (date1.getFullYear() > date2.getFullYear()) {
      return 1;
    }

    // Compare months
    if (date1.getMonth() < date2.getMonth()) {
      return -1;
    }

    if (date1.getMonth() > date2.getMonth()) {
      return 1;
    }

    // Compare days
    if (date1.getDate() < date2.getDate()) {
      return -1;
    }

    if (date1.getDate() > date2.getDate()) {
      return 1;
    }

    // Dates are equal
    return 0;
  };

  var contains = function(needle, haystack) {
    return haystack.indexOf(needle) != -1; 
  };

  var trimLast = function(str) {
    return str.susbtring(0, str.length - 1);
  };

  return {
    hasClass: hasClass,
    makePriceString: makePriceString,
    makeTimestampString: makeTimestampString,
    makeDateString: makeDateString,
    removeDomChildren: removeDomChildren,
    stringifyNumberWithEnforcedDigitCount: stringifyNumberWithEnforcedDigitCount,
    makeTimestampIntervalString: makeTimestampIntervalString,
    synthesizeTemplate: synthesizeTemplate,
    synthesizeTemplateIntoList: synthesizeTemplateIntoList,
    bindNode: bindNode,
    bindNodeInfo: bindNodeInfo,
    hideNode: hideNode,
    showNode: showNode,
    bindClickBeyondNode: bindClickBeyondNode,
    compareDates: compareDates,
    contains: contains,
    trimLast : trimLast,
  };

})();

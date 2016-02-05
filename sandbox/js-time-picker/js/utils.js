var Utils = (function() {
 
  this.hasClass = function(expected_class, node_class) {
    var class_idx = node_class.indexOf(expected_class);
    
    if (class_idx == -1) {
      return;
    }

    return (class_idx == 0 || node_class.charAt(class_idx - 1) == ' ')
      && (expected_class.length + class_idx == node_class.length
        || node_class.charAt(expected_class.length + class_idx) == ' ');
  };

  return {
    hasClass: hasClass
  };
})();

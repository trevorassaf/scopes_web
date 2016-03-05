var Utils = (function() {

  var CLASS_NAME_PROPERTY = "className";

  this.hasClass = function(expected_class, node) {
    if (!(CLASS_NAME_PROPERTY in node)) {
      return false;
    }

    var node_class = node[CLASS_NAME_PROPERTY];
    var class_idx = node_class.indexOf(expected_class);
    
    if (class_idx == -1) {
      return false;
    }

    return (class_idx == 0 || node_class.charAt(class_idx - 1) == ' ')
      && (expected_class.length + class_idx == node_class.length
        || node_class.charAt(expected_class.length + class_idx) == ' ');
  };
  
  this.makePriceString = function(price) {
    var price_in_cents = Math.floor(price * 100);
    price = price_in_cents / 100;
    
    if (price_in_cents % 100 === 0) {
      return price.toString() + ".00"; 
    } 
    
    if (price_in_cents % 10 === 0) {
      return price.toString() + "0";
    }

    return price;
  };

  return {
    hasClass: hasClass,
    makePriceString: makePriceString
  };

})();

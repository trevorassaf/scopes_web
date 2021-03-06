var PaymentStatus = function(_value = this.PENDING) {

  // Payment statuses
  this.PENDING = 1;
  this.APPROVED = 2;
  this.COMPLETED = 3;

  // Private state 
  var value = _value;

  this.isPending = function() {
    return value == this.PENDING;
  };

  this.isApproved = function() {
    return value == this.APPROVED;
  };

  this.isCompleted = function() {
    return value == this.COMPLETED;
  };

  this.getValue = function() {
    return value; 
  };

  this.compare = function(payment_status) {
    return value == payment_status.getValue();
  };
};

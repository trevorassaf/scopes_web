function Test() {
  
  this.a = function() {
    console.log("A");
    this.b();
  };

  this.b = function() {
    console.log("B");
  };
};

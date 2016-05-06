function ShortCode(
  id,
  code,
  alias
) {
  this.id = id;
  this.code = code;
  this.alias = alias;
};

ShortCode.prototype.getId = function() {
  return this.id;
};

ShortCode.prototype.getCode = function() {
  return this.code;
};

ShortCode.prototype.getAlias = function() {
  return this.alias;
};

ShortCode.prototype.deepCopy = function() {
  return new ShortCode(
    this.id,
    this.code,
    this.alias
  );
};

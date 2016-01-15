/**
 * ScopesApiRequestObject
 * - base class for all sub-objects used in ScopesApi requests
 * @req: all child classes store request fields in 'this.data'
 */

function ScopesApiRequestObject() {
  this.data = {};
}

ScopesApiRequestObject.prototype.getData() = function() {
  return this.data;
}

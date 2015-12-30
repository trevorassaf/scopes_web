var ScopesNetwork = (function() {
  
  var ENDPOINT_PATH = "../../hhvm/endpoints/endpoint.hh";

  var API_TYPE_KEY = "api_type";

  var PAYLOAD_KEY = "payload";

  var HTTP_REQUEST_TYPE = "POST";

  var CONTENT_TYPE_KEY = "Content-Type";

  var WWW_FORM_URLENCODED_CONTENT_TYPE = "application/x-www-form-urlencoded";

  var PARAMETER_ASSIGNMENT_TOKEN = "=";

  var PARAMETER_SEPARATOR_TOKEN = "&";

  /**
   * urlEncodeRequestObject()
   * @param Object<string, mixed> request_object: key/value pairs of request params
   */
  var urlEncodeRequestObject = function(request_object) {
    var param_str = "";
    for (var key in request_object) {
      param_str += key + PARAMETER_ASSIGNMENT_TOKEN + request_object[key] + PARAMETER_SEPARATOR_TOKEN;
    }

    return param_str.substring(0, param_str.length - 1);
  };

  return {
    /**
     * request()
     * @param int api_type: index of specified api 
     * @param array<string, mixed> payload_fields: payload parameters
     * @param bool is_async: is request synchronous
     * @param function(XMLHttpRequest xhttp) successful_callback: callback function for when request finishes successfully
     * @param function(XMLHttpRequest xhttp) failed_callback: callback function for when request finishes with failure
     */
    request: function(api_type, payload_fields, is_async, successful_callback, failed_callback) {
      var xhttp = new XMLHttpRequest(); 
      
      // Bind callbacks
      if (is_async) {
        xhttp.onreadystatechange = function() {
          if (xhttp.readyState == 4) {
            if (xhttp.status == 200) {
              successful_callback(xhttp); 
            } else {
              failed_callback(xhttp);
            }
          }
        };
      }

      // Bind http destination and request type
      xhttp.open(
        HTTP_REQUEST_TYPE,
        ENDPOINT_PATH,
        is_async
      );

      console.log(ENDPOINT_PATH);

      // Bind http content type
      xhttp.setRequestHeader(
        CONTENT_TYPE_KEY,
        WWW_FORM_URLENCODED_CONTENT_TYPE
      );

      // Assemble payload
      var serialized_payload = JSON.stringify(payload_fields);

      var request_data = {};
      request_data[API_TYPE_KEY] = api_type;
      request_data[PAYLOAD_KEY] = serialized_payload;

      console.log(request_data);

      var request_string = urlEncodeRequestObject(request_data);
      console.log(request_string);

      // Execute request 
      xhttp.send(request_string);

      if (!is_async) {
        return xhttp.responseText;
      }
    }  
  }

}());

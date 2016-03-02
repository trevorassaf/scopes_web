var ScopesNetwork = (function() {
  
  var ENDPOINT_PATH = "hhvm/endpoints/endpoint.hh";

  var API_TYPE_KEY = "api_type";

  var PAYLOAD_KEY = "payload";

  var VIDEO_UPLOAD_KEY = "video";

  var HTTP_REQUEST_TYPE = "POST";

  var CONTENT_TYPE_KEY = "Content-Type";

  var WWW_FORM_URLENCODED_CONTENT_TYPE = "application/x-www-form-urlencoded";

  var PARAMETER_ASSIGNMENT_TOKEN = "=";

  var PARAMETER_SEPARATOR_TOKEN = "&";

  return {
    /**
     * request()
     * @param int api_type: index of specified api 
     * @param array<string, mixed> payload_fields: payload parameters
     * @param bool is_async: is request synchronous
     * @param function(XMLHttpRequest xhttp) successful_callback: callback function for when request finishes successfully
     * @param function(XMLHttpRequest xhttp) failed_callback: callback function for when request finishes with failure
     * @param File upload_file: optional file upload parameter
     */
    request: function(
     api_type,
     payload_fields,
     is_async,
     successful_callback,
     failed_callback,
     upload_file
   ) {
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

      // Assemble payload
      var serialized_payload = JSON.stringify(payload_fields);

      var form_data = new FormData();
      
      if (upload_file != null) {
        form_data.append(VIDEO_UPLOAD_KEY, upload_file);
        console.log(VIDEO_UPLOAD_KEY);
        console.log(upload_file);
      }

      form_data.append(API_TYPE_KEY, api_type);
      form_data.append(PAYLOAD_KEY, serialized_payload);

console.log(API_TYPE_KEY);
console.log(api_type);
console.log(PAYLOAD_KEY);
console.log(serialized_payload);

      // Execute request 
      xhttp.send(form_data);

      if (!is_async) {
        return xhttp.responseText;
      }
    }  
  }
}());

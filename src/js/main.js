window.onload = function() {

  /**
   * Configure page settings
   */
  document.execCommand('defaultParagraphSeparator', false, 'p');

  /**
   * Capture import node for html templates
   */
  var template_store = document.querySelector('#template-import');
  console.assert(template_store != null);

  /**
   * Init application controller
   */
  var app_controller = new ApplicationController(template_store);
  app_controller.init();
};

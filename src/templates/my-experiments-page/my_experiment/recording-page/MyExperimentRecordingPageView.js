var MyExperimentRecordingPageView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiment-recording-page-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiment-recording-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  /**
   * Dom info
   */
  var videoNode = {
    className: 'experiment-recording',
    node: null
  };

  var absentVideoMessageNode = {
    className: 'absent-video-message',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    Utils.bindNodeInfo(rootNode, videoNode);
    Utils.bindNodeInfo(rootNode, absentVideoMessageNode);
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );

    // Bind all ui nodes and attach event listeners
    bindNodes(); 
  };

  this.show = function() {
    Utils.showNode(parentNode);
  };
  
  this.hide = function() {
    Utils.hideNode(parentNode);
  };

  this.showVideo = function() {
    Utils.hideNode(absentVideoMessageNode.node);
    Utils.showNode(videoNode.node);
  };

  this.showAbsentVideoMessage = function() {
    Utils.hideNode(videoNode.node);
    Utils.showNode(absentVideoMessageNode.node);
  };
};

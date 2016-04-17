var MyExperimentView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiment-skeleton-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiment-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  // Event listeners
  var frontPageNavCallbacks = [];
  var descriptionNavCallbacks = [];
  var monitorNavCallbacks = [];
  var recordingNavCallbacks = [];

  /**
   * Dom nodes
   */
  // Title
  var titleLabelNode = {
    className: 'title-label',
    node: null
  };

  var titleUnderlineNode = {
    className: 'title-underline',
    node: null
  };

  // Page wrappers
  var frontPageNode = {
    className: 'front-page',
    node: null
  };

  var descriptionPageNode = {
    className: 'description-page',
    node: null
  };

  var monitorPageNode = {
    className: 'monitor-page',
    node: null
  };

  var recordingPageNode = {
    className: 'recording-page',
    node: null
  };

  // Navigation bar
  var frontPageNavNode = {
    className: 'front-page-nav-wrapper',
    node: null
  };

  var descriptionNavNode = {
    className: 'description-nav-wrapper',
    node: null
  };

  var monitorNavNode = {
    className: 'monitor-nav-wrapper',
    node: null
  };

  var recordingNavNode = {
    className: 'recording-nav-wrapper',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    // Bind nodes    
    Utils.bindNodeInfo(rootNode, titleLabelNode);
    Utils.bindNodeInfo(rootNode, titleUnderlineNode);

    Utils.bindNodeInfo(rootNode, frontPageNode);
    Utils.bindNodeInfo(rootNode, descriptionPageNode);
    Utils.bindNodeInfo(rootNode, monitorPageNode);
    Utils.bindNodeInfo(rootNode, recordingPageNode);

    Utils.bindNodeInfo(rootNode, frontPageNavNode);
    Utils.bindNodeInfo(rootNode, descriptionNavNode);
    Utils.bindNodeInfo(rootNode, monitorNavNode);
    Utils.bindNodeInfo(rootNode, recordingNavNode);

    // TODO attach onclick listeners
    frontPageNavNode.node.onclick = function() {
      frontPageNavCallbacks.forEach(function(callback) {
        callback();
      }); 
    };
    
    descriptionNavNode.node.onclick = function() {
      descriptionNavCallbacks.forEach(function(callback) {
        callback();
      }); 
    };
    
    monitorNavNode.node.onclick = function() {
      monitorNavCallbacks.forEach(function(callback) {
        callback();
      }); 
    };
    
    recordingNavNode.node.onclick = function() {
      recordingNavCallbacks.forEach(function(callback) {
        callback();
      }); 
    };
  };

  var initPages = function() {
    // Initialize child pages
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

    // Initialize child pages
    initPages();

    return this;
  };

  this.bindFrontPageNav = function(callback) {
    frontPageNavCallbacks.push(callback);
    return this;
  };

  this.bindDescriptionNav = function(callback) {
    descriptionNavCallbacks.push(callback);
    return this;
  };

  this.bindMonitorNav = function(callback) {
    monitorNavCallbacks.push(callback);
    return this;
  };

  this.bindRecordingNav = function(callback) {
    recordingNavCallbacks.push(callback);
    return this;
  };
};

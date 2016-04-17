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
   * Ui text
   */
  var DEFAULT_TITLE = 'Add title...';

  /**
   * Ui attributes
   */
  var CHANGED_TITLE_ATTR = 'changed-title';
  var EDITING_TITLE_ATTR = 'editing-title';

  /**
   * Private state
   */
  var templateStore = template_store;

  // Ui data
  var cachedTitle = null;
  var isUserDefinedTitle = false;
  var isEditingTitle = false;
 
  // Dom nodes
  var parentNode = parent_node;
  var rootNode = null;

  // Page views
  var frontPageView = null;
  var descriptionPageView = null;
  var monitorExperimentPageView = null;
  var recordingPageView = null;

  var selectedPageView = null;
  var selectedPageButtonNode = null;

  /**
   * Event listeners
   */
  // Title change listeners
  var titleChangeCallbacks = [];

  // Page nav listeners
  var frontPageNavCallbacks = [];
  var descriptionNavCallbacks = [];
  var monitorNavCallbacks = [];
  var recordingNavCallbacks = [];

  /**
   * Dom node infos
   */
  // Title
  var titleLabelNode = {
    className: 'title-label',
    node: null
  };

  var headerNode = {
    className: 'header-wrapper',
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
    Utils.bindNodeInfo(rootNode, headerNode);

    Utils.bindNodeInfo(rootNode, frontPageNode);
    Utils.bindNodeInfo(rootNode, descriptionPageNode);
    Utils.bindNodeInfo(rootNode, monitorPageNode);
    Utils.bindNodeInfo(rootNode, recordingPageNode);

    Utils.bindNodeInfo(rootNode, frontPageNavNode);
    Utils.bindNodeInfo(rootNode, descriptionNavNode);
    Utils.bindNodeInfo(rootNode, monitorNavNode);
    Utils.bindNodeInfo(rootNode, recordingNavNode);

    /**
     * Attach event listeners
     */
    // Page nav listeners
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

    // Title event listeners
    titleLabelNode.node.onkeypress = function(event) {
      if (Utils.isEnterKeyPressed(event)) {
        setFinishedEditingTitle();
        return false;
      }
    };

    headerNode.node.onclick = function(event) {
      // Put title in 'editing' state if we're not editing it already
      if (!isEditingTitle) {
        setEditingTitle();
      }
    };

    Utils.bindClickBeyondNode(headerNode.node, function(event) {
      // Short circuit b/c we're not editing title anyhow
      if (!isEditingTitle) {
        return;
      }

      // Signal that we've finished editing the title
      setFinishedEditingTitle();
    });

  };

  var initPages = function() {
    // Initialize child pages
  };
  
  var changeVisiblePage = function(
    next_page_view,
    next_page_button
  ) {
    // Unselect current page
    selectedPageView.hide();
    Utils.unselectNode(selectedPageButtonNode);
  
    selectPage(next_page_view, next_page_button);
  };

  var selectPage = function(page_view, page_button_node) {
    // Update Ui
    page_view.show();
    Utils.selectNode(page_button_node);

    selectedPageView = page_view;
    selectedPageButtonNode = page_button_node; 
  };

  var setEditingTitle = function() {
    console.assert(!isEditingTitle);
    
    // Update ui
    Utils.markNode(headerNode.node, EDITING_TITLE_ATTR);

    if (isUserDefinedTitle) {
      // Highligh title field text
      Utils.selectTextRange(titleLabelNode.node); 
    } else {
      // Remove placeholder title 
      titleLabelNode.node.innerHTML = '';
    }

    isEditingTitle = true;
  };

  var setNotEditingTitle = function() {
    console.assert(isEditingTitle);

    // Update ui
    Utils.unmarkNode(headerNode.node, EDITING_TITLE_ATTR);

    // Unselect title
    Utils.unselectTextRange(titleLabelNode.node);
    titleLabelNode.node.blur();
    window.getSelection().removeAllRanges();

    isEditingTitle = false;
  };

  var setFinishedEditingTitle = function() {
    // Notify listeners that the title has changed! 
    var title = titleLabelNode.node.innerHTML;

    // Short circuit if title hasn't changed
    if (isUserDefinedTitle && title == cachedTitle) {
      return;
    }
    titleChangeCallbacks.forEach(function(callback) {
      callback(title); 
    }); 

    // Return title to non-editing state
    setNotEditingTitle();
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

  // Callback registers
  this.bindTitle = function(callback) {
    titleChangeCallbacks.push(callback); 
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

  // Show page functions
  this.showFrontPage = function() {
    changeVisiblePage(frontPageView);
  };

  this.showDescriptionPage = function() {
    changeVisiblePage(descriptionPageView);
  };

  this.showMonitorExperimentPage = function() {
    changeVisiblePage(monitorExperimentPageView);
  };

  this.showRecordingPage = function() {
    changeVisiblePage(recordingPageView);
  };
 
  // Ui setters
  this.setTitle = function(title) {
    // Handle title change
    titleLabelNode.node.innerHTML = title;
    cachedTitle = title;
    Utils.markNode(titleLabelNode.node, CHANGED_TITLE_ATTR);
    isUserDefinedTitle = true;
  };

  this.setTitlePlaceholder = function() {
    titleLabelNode.node.innerHTML = DEFAULT_TITLE;
    cachedTitle = null;
    Utils.unmarkNode(titleLabelNode.node, CHANGED_TITLE_ATTR);
    isUserDefinedTitle = false;
  };
};

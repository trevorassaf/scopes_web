var SidePanelView = function(
  template_store,
  parent_node
) {

  /**
   * Template node id
   */
  var TEMPLATE_ID = 'side-panel-template';

  /**
   * Root node class name
   */
  var ROOT_NODE_CLASS = 'side-panel-wrapper';
  
  /**
   * Ui attributes
   */
  var START_HIDDEN_ATTR = "start-hidden";
  
  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var currentlySelectedTabAndPageInfo = null;
  var centerPageTitleLabel = null;
  var centerPanelPageContainer = null;
  
  var currentlySelectedTab = null;
  var tabParentNode = null;

  /**
   * Tab infos
   */
  var tabContainerRootInfo = {
    className: 'nav-btns-container',
    node: null
  };

  var homeButtonNode = {
    className: 'home-nav-container',
    node: null
  };

  var userNameNode = {
    className: 'side-panel-user-label',
    node: null
  };

  var newExperimentInfo = {
    button_title: 'Add Experiment',
    icon_type: 'add-circle-outline',
    tab: null,
    callback_listeners: []
  };

  var myExperimentsInfo = {
    button_title: 'My Experiments',
    icon_type: 'group-work',
    tab: null,
    callback_listeners: []
  };

  var feedbackInfo = {
    button_title: 'Feedback',
    icon_type: 'question-answer',
    tab: null,
    callback_listeners: []
  };

  var technicianInfo = {
    button_title: 'Technician',
    icon_type: 'build',
    tab: null,
    callback_listeners: []
  };

  /**
   * Private functions
   */
  /**
   * initTabInfo()
   * - initialize SidePanelTab view
   * - bind event listeners
   * @param TabInfo (see above)
   */
  var initTabInfo = function(tab_info) {
    // Initialize tab view 
    tab_info.tab = new SidePanelTab(
      templateStore,
      tabContainerRootInfo.node,
      tab_info.button_title,
      tab_info.icon_type
    );    

    // Register 'onclick' callback
    tab_info.tab.registerOnClickListener(function() {
      // // Unselect previous tab
      // currentlySelectedTab.deselect();
      //
      // // Select new tab
      // currentlySelectedTab = tab_info.tab;
      // currentlySelectedTab.select();

      // Invoke callback listeners
      for (var i = 0; i < tab_info.callback_listeners.length; ++i) {
        tab_info.callback_listeners[i]();
      }
    });

    // Initialize tab ui
    tab_info.tab.init();
  };

  /**
   * initTabInfos()
   * - initialize all tabs (bind nodes and event listeners)
   */
  var initTabInfos = function() {
    // Initialize tab parent node
    tabContainerRootInfo.node = Utils.bindNode(
      rootNode,
      tabContainerRootInfo.className
    ); 

    // Initialize tab views
    initTabInfo(newExperimentInfo);
    initTabInfo(myExperimentsInfo);
    initTabInfo(technicianInfo);
    initTabInfo(feedbackInfo);
  };

  var selectTab = function(tab) {
    if (currentlySelectedTab != null) {
      currentlySelectedTab.deselect();
    }
    tab.select();
    currentlySelectedTab = tab;
  };

  var bindNodes = function() {
    // Initialize user-name ui node
    userNameNode.node = Utils.bindNode(
      rootNode,
      userNameNode.className
    );

    // Initialize home burron ui node
    homeButtonNode.node = Utils.bindNode(
      rootNode,
      homeButtonNode.className
    );

    // Initialize tabs
    initTabInfos();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Synthesize html template and insert into main document
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_NODE_CLASS
    );    

    bindNodes();
  
    return this;
  };

  /**
   * Onclick event listeners for tabs
   */
  this.bindNewExperimentTabClick = function(callback) {
    newExperimentInfo.callback_listeners.push(callback); 
  };

  this.bindMyExperimentsTabClick = function(callback) {
    myExperimentsInfo.callback_listeners.push(callback); 
  };

  this.bindFeedbackTabClick = function(callback) {
    feedbackInfo.callback_listeners.push(callback); 
  };

  this.bindTechnicianTabClick = function(callback) {
    technicianInfo.callback_listeners.push(callback); 
  };

  /**
   * Select tab
   */
  this.selectNewExperimentTab = function() {
    selectTab(newExperimentInfo.tab);
  };

  this.selectMyExperimentsTab = function() {
    selectTab(myExperimentsInfo.tab);
  };

  this.selectFeedbackTab = function() {
    selectTab(feedbackInfo.tab);
  };

  this.selectTechnicianTab = function() {
    selectTab(technicianInfo.tab);
  };
};

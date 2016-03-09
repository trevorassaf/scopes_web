function PendingExperimentView(
  template_store,
  parent_node
) {

  /**
   * Key code values
   */
  var ENTER_KEY_CODE = 13;

  /**
   * Default values 
   */
  var DEFAULT_TITLE = 'Add title...';
  var DEFAULT_DESCRIPTION = 'Add notes...';

  /**
   * Ui attributes
   */
  var SELECTED_BUTTON_ATTR = "selected-btn";
  var SELECTED_PAGE_ATTR = 'selected-page';
  var EDITING_TITLE_ATTR = 'editing-title';
  var EDITING_DESCRIPTION_ATTR = 'editing-description';
  var CHANGED_TITLE_ATTR = 'changed-title';
  var CHANGED_DESCRIPTION_ATTR = 'changed-description';

  /**
   * Unit tokens 
   */
  var PRICE_UNIT_TOKEN = '$ ';

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = '#pending-experiment-template';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var selectedButton = null;
  var selectedPageWrapper = null;
  var isEditingTitle = false;
  var isEditingDescription = false;
  var cachedTitle = null;
  var changedTitleListeners = [];
  var cachedDescription = null;
  var changedDescriptionListeners = [];

  /**
   * Dom nodes
   */
  var rootNode = {
    className: 'pending-experiment-wrapper',
    node: null
  };

  /**
   * Header nodes
   */
  var headerNode = {
    className: 'header-wrapper',
    node: null
  };

  var titleNode = {
    className: 'title-label',
    node: null
  };

  /**
   * Page nodes 
   */
  var timePageNode = {
    className: 'time-page',
    node: null
  };

  var staticCalendarWrapperNode = {
    className: 'static-calendar',
    node: null
  };

  var descriptionPageNode = {
    className: 'description-page',
    node: null
  };
  
  var recordingPageNode = {
    className: 'recording-page',
    node: null
  };
  
  var monitorPageNode = {
    className: 'monitor-page',
    node: null
  };
  
  /**
   * Footer button nodes
   */
  var descriptionButtonNode = {
    className: 'description-nav-wrapper',
    node: null
  };

  var recordingButtonNode = {
    className: 'recording-nav-wrapper',
    node: null
  };

  var timeButtonNode = {
    className: 'time-nav-wrapper',
    node: null
  };

  var monitorButtonNode = {
    className: 'monitor-nav-wrapper',
    node: null
  };

  /**
   * Main stage wrappers
   */
  var scopesCountNode = {
    className: 'scopes-count-value',
    node: null
  };

  var startTimeNode = {
    className: 'start-time-value',
    node: null
  };

  var durationNode = {
    className: 'experiment-duration-value',
    node: null
  };

  var durationUnitNode = {
    className: 'experiment-duration-unit',
    node: null,
    singular: 'hour',
    plural: 'hours'
  };

  var priceNode = {
    className: 'price-value',
    node: null
  };

  var shortCodeNode = {
    className: 'short-code-value',
    node: null
  };

  /**
   * Private functions
   */
  function synthesizeTemplate() {
    // Clone pending-order template
    var pending_order_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR); 
    var pending_order_clone = document.importNode(pending_order_template.content, true);

    // Activate by inserting into parent 
    parentNode.appendChild(pending_order_clone); 
    var pending_order_list = parentNode.getElementsByClassName(rootNode.className);
    rootNode.node = pending_order_list[pending_order_list.length - 1];
  };

  /**
   * setTitle()
   * @param string title: title string
   */
  function setTitle(title) {
    if (title == null || title == '') {
      titleNode.node.innerHTML = DEFAULT_TITLE; 
      cachedTitle = null;
      titleNode.node.removeAttribute(CHANGED_TITLE_ATTR);
    } else {
      titleNode.node.innerHTML = title; 
      cachedTitle = title;
      titleNode.node.setAttribute(CHANGED_TITLE_ATTR, '');
    }
  };

  function setStartTime(start_time) {
    startTimeNode.node.innerHTML = start_time; 
  };

  /**
   * setDescription()
   * @param string description
   */
  function setDescription(description) {
    if (description == null || description == '') {
      descriptionPageNode.node.innerHTML = DEFAULT_DESCRIPTION; 
      cachedDescription = null;
      descriptionPageNode.node.removeAttribute(CHANGED_DESCRIPTION_ATTR);
    } else {
      descriptionPageNode.node.innerHTML = description; 
      cachedDescription = description;
      descriptionPageNode.node.setAttribute(CHANGED_DESCRIPTION_ATTR, '');
    }
  };

  function setDuration(duration) {
    durationNode.node.innerHTML = duration;
    durationUnitNode.node.innerHTML = (duration == 1)
      ? durationUnitNode.singular
      : durationUnitNode.plural;
  };

  function setShortCode(short_code) {
    shortCodeNode.node.innerHTML = short_code.getAlias(); 
  };

  function setScopesCount(scopes_count) {
    scopesCountNode.node.innerHTML = scopes_count;
  };

  function setPrice(price) {
    priceNode.node.innerHTML = PRICE_UNIT_TOKEN + price;
  };

  function setOrderedDate(ordered_date) {
    orderedDateNode.node.innerHTML = ordered_date.serialize();
  };

  var bindClassBoundNode = function(node_info) {
    console.log(node_info.className);
    var elements = rootNode.node.getElementsByClassName(node_info.className); 
    console.assert(elements.length === 1);
    node_info.node = elements[0];
  };

  var unselectButton = function() {
    console.assert(selectedButton !== null); 
    selectedButton.node.removeAttribute(SELECTED_BUTTON_ATTR);
    selectedButton = null;
  };

  var selectButton = function(selected_button) {
    console.assert(selectedButton === null);
    selectedButton = selected_button;
    selectedButton.node.setAttribute(SELECTED_BUTTON_ATTR, '');
  };

  var hideSelectedPage = function() {
    console.assert(selectedPageWrapper !== null);
    selectedPageWrapper.node.removeAttribute(SELECTED_PAGE_ATTR);
    selectedPageWrapper = null;
  };

  var selectPage = function(page) {
    console.assert(selectedPageWrapper === null);
    selectedPageWrapper = page;
    selectedPageWrapper.node.setAttribute(SELECTED_PAGE_ATTR, '');
  };

  var changePage = function(button, page) {
    // Deselect currently selected button/page
    unselectButton();
    hideSelectedPage();

    // Select new button/page
    selectButton(button);
    selectPage(page);
  };

  var setEditingDescription = function() {
    console.assert(!isEditingDescription);
    isEditingDescription = true;
    descriptionPageNode.node.setAttribute(EDITING_DESCRIPTION_ATTR, '');

    // Highlight default description if no description provided
    if (cachedDescription == null || '') {
      var range = document.createRange();
      range.selectNodeContents(descriptionPageNode.node);
      var sel = window.getSelection();
      sel.removeAllRanges();
      sel.addRange(range);
    }
  }

  var setNotEditingDescription = function() {
    console.assert(isEditingDescription);
    descriptionPageNode.node.removeAttribute(EDITING_DESCRIPTION_ATTR);
    isEditingDescription = false;

    // Restore default description if user removed the description
    if (cachedDescription == null || cachedDescription == '') {
      descriptionPageNode.node.innerHTML = DEFAULT_DESCRIPTION;
    }
  };

  var finishedEditingDescription = function() {
    // Notify listeners that the description has changed!
    if (cachedDescription != descriptionPageNode.node.innerHTML &&
        !(cachedDescription == null && descriptionPageNode.node.innerHTML == DEFAULT_DESCRIPTION) &&
        !(cachedDescription == null && descriptionPageNode.node.innerHTML == '')
    ) {
      // Update cached description value
      cachedDescription = descriptionPageNode.node.innerHTML;

      if (cachedDescription == '') {
        cachedDescription = null;
      }

      if (cachedDescription != null) {
        descriptionPageNode.node.setAttribute(CHANGED_DESCRIPTION_ATTR, '');
      } else {
        descriptionPageNode.node.removeAttribute(CHANGED_DESCRIPTION_ATTR); 
      }

      console.log(cachedDescription);

      for (var i = 0; i < changedDescriptionListeners.length; ++i) {
        changedDescriptionListeners[i](cachedDescription);
      }
    }

    // Return description to non-editing state
    setNotEditingDescription();
  };

  var bindTimeNodes = function() {
    bindClassBoundNode(timePageNode);
    bindClassBoundNode(staticCalendarWrapperNode);
    
    bindClassBoundNode(shortCodeNode);
    bindClassBoundNode(scopesCountNode);
    bindClassBoundNode(priceNode);
    bindClassBoundNode(startTimeNode);
    bindClassBoundNode(durationNode);
    bindClassBoundNode(durationUnitNode);
  };

  var bindDescriptionNodes = function() {
    // Bind dom nodes
    bindClassBoundNode(descriptionPageNode);

    // Bind event listeners
    descriptionPageNode.node.onclick = function() {
      // Short circuit b/c we're already editing the description
      if (isEditingDescription) {
        return;
      }

      setEditingDescription();
    }; 

    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      // Short circuit b/c description isn't being edited currently anyway
      if (!isEditingDescription) {
        return;
      }

      for (var node_idx in event.path) {
        var node = event.path[node_idx];
        if (Utils.hasClass(descriptionPageNode.className, node)) {
          return;
        }
      }   

      // Signal that we've finished editing the description
      finishedEditingDescription();
    });
  };

  var bindPageNodes = function() {
    // Bind nodes
    bindTimeNodes();
    bindDescriptionNodes();
    bindClassBoundNode(recordingPageNode);
    bindClassBoundNode(monitorPageNode);
  };

  var bindFooterNodes = function() {
    // Bind nodes
    bindClassBoundNode(descriptionButtonNode);
    bindClassBoundNode(recordingButtonNode);
    bindClassBoundNode(timeButtonNode);
    bindClassBoundNode(monitorButtonNode);

    // Configure event listeners
    descriptionButtonNode.node.onclick = function() {
      changePage(descriptionButtonNode, descriptionPageNode); 
    }; 
    recordingButtonNode.node.onclick = function() {
      changePage(recordingButtonNode, recordingPageNode); 
    }; 
    timeButtonNode.node.onclick = function() {
      changePage(timeButtonNode, timePageNode); 
    }; 
    monitorButtonNode.node.onclick = function() {
      changePage(monitorButtonNode, monitorPageNode); 
    }; 
  };

  var setEditingTitle = function() {
    console.assert(!isEditingTitle);
    headerNode.node.setAttribute(EDITING_TITLE_ATTR, '');  
    
    // Select text in title field
    var range = document.createRange();
    range.selectNodeContents(titleNode.node);
    var sel = window.getSelection();
    sel.removeAllRanges();
    sel.addRange(range);

    isEditingTitle = true;
  };

  var setNotEditingTitle = function() {
    console.assert(isEditingTitle);
    isEditingTitle = false;

    headerNode.node.removeAttribute(EDITING_TITLE_ATTR);
    titleNode.node.blur();

    var selection = window.getSelection();
    if (Utils.hasClass(titleNode.node.className, selection.anchorNode.parentElement)) {
      selection.removeAllRanges(); 
    }

    // Restore default title if user removed title
    if (cachedTitle == null || cachedTitle == '') {
      titleNode.node.innerHTML = DEFAULT_TITLE; 
    }
  };

  var finishedEditingTitle = function() {
    // Notify listeners that the title has changed!
    if (cachedTitle != titleNode.node.innerHTML &&
        !(cachedTitle == null && titleNode.node.innerHTML == DEFAULT_TITLE) &&
        !(cachedTitle == null && titleNode.node.innerHTML == '')
    ) {
      // Update cached title value
      cachedTitle = titleNode.node.innerHTML;

      if (cachedTitle == '') {
        cachedTitle = null;
      }

      if (cachedTitle != null) {
        titleNode.node.setAttribute(CHANGED_TITLE_ATTR, '');  
      } else {
        titleNode.node.removeAttribute(CHANGED_TITLE_ATTR);  
      }
      
      console.log(cachedTitle);

      for (var i = 0; i < changedTitleListeners.length; ++i) {
        changedTitleListeners[i](cachedTitle);
      }
    }
    
    // Return title to non-editing state
    setNotEditingTitle();
  };

  var bindHeaderNodes = function() {
    // Bind header nodes
    bindClassBoundNode(headerNode);
    bindClassBoundNode(titleNode); 

    // Bind header event listeners
    headerNode.node.onclick = function() {
      // Short circuit b/c we're already editing the title...
      if (isEditingTitle) {
        return;
      }

      setEditingTitle();
    };

    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      // Short circuit b/c title isn't being edited currently anyway
      if (!isEditingTitle) {
        return;
      }

      for (var node_idx in event.path) {
        var node = event.path[node_idx];
        if (Utils.hasClass(headerNode.className, node)) {
          return;
        }
      }   

      // Signal that we've finished editing the title
      finishedEditingTitle();
    });

    titleNode.node.onkeypress = function(event) {
      // If 'return' pressed, then direct focus away from 'titleNode'
      if (event.charCode == ENTER_KEY_CODE) {
        finishedEditingTitle();
        return false;
      }
    };
  };

  var bindInternalNodes = function() {
    bindHeaderNodes();
    bindPageNodes();
    bindFooterNodes();
  };

  var initUiData = function(confirmed_order) {
    // Update header data
    setTitle(confirmed_order.getTitle());

    // Update time data
    staticCalendar = new StaticCalendar(
      templateStore,
      staticCalendarWrapperNode.node,
      confirmed_order.getStartTimestamp()
    );
    staticCalendar.init();
    
    setScopesCount(confirmed_order.getScopesCount());
    setPrice(confirmed_order.getPrice());
    setShortCode(confirmed_order.getShortCode());

    var experiment_start_time = new Date(confirmed_order.getStartTimestamp());
    var serializeable_experiment_start_time = new SerializeableTime(
      experiment_start_time.getHours(),
      experiment_start_time.getMinutes(),
      experiment_start_time.getSeconds()
    );

    setStartTime(serializeable_experiment_start_time.serializeWithoutSeconds());
    
    var experiment_end_time = new Date(confirmed_order.getEndTimestamp());

    setDuration(DateOperator.getDifferenceInHours(
      experiment_end_time,
      experiment_start_time
    ));

    // Init description-page data
    setDescription(confirmed_order.getDescription());
  };

  /**
   * Privileged functions
   */
  this.init = function(confirmed_order) {
    // Clone template and copy into pending-experiments list
    synthesizeTemplate();

    // Init dom pointers to internal nodes
    bindInternalNodes();

    // Place data in proper ui elements
    initUiData(confirmed_order);

    selectButton(timeButtonNode);
    selectPage(timePageNode);
  };

  /**
   * registerChangedTitleListener()
   * @param FuncPtr callback: function(title) {...}
   */
  this.registerChangedTitleListener = function(callback) {
    changedTitleListeners.push(callback);
  }
};

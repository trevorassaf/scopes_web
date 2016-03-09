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
  var DEFAULT_DESCRIPTION = 'Add description...';

  /**
   * Ui attributes
   */
  var SELECTED_BUTTON_ATTR = "selected-btn";
  var SELECTED_PAGE_ATTR = 'selected-page';
  var EDITING_TITLE_ATTR = 'editing-title';

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
  var cachedTitle = null;
  var changedTitleListeners = [];

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
  var descriptionPageNode = {
    className: 'description-page',
    node: null
  };
  
  var hardwarePageNode = {
    className: 'hardware-page',
    node: null
  };
  
  var timePageNode = {
    className: 'time-page',
    node: null
  };
  
  var paymentPageNode = {
    className: 'payment-page',
    node: null
  };
  
  /**
   * Footer button nodes
   */
  var descriptionButtonNode = {
    className: 'description-nav-wrapper',
    node: null
  };

  var hardwareButtonNode = {
    className: 'hardware-nav-wrapper',
    node: null
  };

  var timeButtonNode = {
    className: 'time-nav-wrapper',
    node: null
  };

  var paymentButtonNode = {
    className: 'payment-nav-wrapper',
    node: null
  };

  /**
   * Main stage wrappers
   */

  var scopesCountNode = {
    value: {
      className: 'scopes-count-label',
      node: null
    },
    unit: {
      className: 'scopes-count-unit-label',
      node: null,
      singular: 'scope',
      plural: 'scopes'
    }
  };

  var startDateNode = {
    className: 'start-date-label',
    node: null
  };

  var experimentTimestampIntervalNode = {
    className: 'experiment-timestamp-interval-label',
    node: null
  };

  var startTimeNode = {
    className: 'start-time-label',
    node: null
  };

  var durationNode = {
    value: {
      className: 'duration-label',
      node: null
    },
    unit: {
      className: 'duration-unit-label',
      node: null,
      singular: 'hour',
      plural: 'hours'
    }
  };

  var descriptionNode = {
    className: 'description-label',
    node: null
  };

  var orderedDateNode = {
    className: 'ordered-date-label',
    node: null
  };

  var priceNode = {
    value: { 
      className: 'price-label',
      node: null
    },
    unit: {
      className: 'price-unit-label',
      node: null,
      singular: '$',
      plural: '$'
    }
  };

  var shortCodeNode = {
    className: 'short-code-label',
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
    } else {
      titleNode.node.innerHTML = title; 
    }
  };

  /**
   * setDescription()
   * @param string description
   */
  function setDescription(description) {
    if (description == null || description == '') {
      descriptionNode.node.innerHTML = DEFAULT_DESCRIPTION; 
    } else {
      descriptionNode.node.innerHTML = description; 
    }
  };

  function setShortCode(short_code) {
    shortCodeNode.node.innerHTML = short_code.getAlias(); 
  };

  function setScopesCount(scopes_count) {
    updateNodeWithUnit(scopes_count, scopesCountNode);
  };

  function setPrice(price) {
    updateNodeWithUnit(price, priceNode);  
  };

  function setOrderedDate(ordered_date) {
    orderedDateNode.node.innerHTML = ordered_date.serialize();
  };

  function setExperimentTimestampInterval(experiment_timestamp_interval) {
    experimentTimestampIntervalNode.node.innerHTML = experiment_timestamp_interval;
  }

  function updateNodeWithUnit(value, node) {
    // Place value in ui node
    node.value.node.innerHTML = value;
    
    // Adjust unit
    node.unit.node.innerHTML = (value === 1)
      ? node.unit.singular
      : node.unit.plural;
  };

  var bindClassBoundNode = function(node_info) {
    var elements = rootNode.node.getElementsByClassName(node_info.className); 
    console.assert(elements.length === 1);
    node_info.node = elements[0];
  };

  var bindClassBoundNodeWithUnit = function(node_info) {
    bindClassBoundNode(node_info.value);
    bindClassBoundNode(node_info.unit);
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

  var bindPageNodes = function() {
    // Bind nodes
    bindClassBoundNode(descriptionPageNode);
    bindClassBoundNode(hardwarePageNode);
    bindClassBoundNode(timePageNode);
    bindClassBoundNode(paymentPageNode);
  };

  var bindFooterNodes = function() {
    // Bind nodes
    bindClassBoundNode(descriptionButtonNode);
    bindClassBoundNode(hardwareButtonNode);
    bindClassBoundNode(timeButtonNode);
    bindClassBoundNode(paymentButtonNode);

    // Configure event listeners
    descriptionButtonNode.node.onclick = function() {
      changePage(descriptionButtonNode, descriptionPageNode); 
    }; 
    hardwareButtonNode.node.onclick = function() {
      changePage(hardwareButtonNode, hardwarePageNode); 
    }; 
    timeButtonNode.node.onclick = function() {
      changePage(timeButtonNode, timePageNode); 
    }; 
    paymentButtonNode.node.onclick = function() {
      changePage(paymentButtonNode, paymentPageNode); 
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
    headerNode.node.removeAttribute(EDITING_TITLE_ATTR);
    titleNode.node.blur();
    window.getSelection().removeAllRanges();
    isEditingTitle = false;
  };

  var finishedEditingTitle = function() {
    // Notify listeners that the title has changed!
    if (cachedTitle != titleNode.node.innerHTML) {
      // Update cached title value
      cachedTitle = titleNode.node.innerHTML;

      console.log(cachedTitle);

      for (var i = 0; i < changedTitleListeners.length; ++i) {
        changedTitleListeners[i](cachedTitle);
      }
    }
    
    // Return title to unselected state
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

    // Bind unitless nodes
    bindClassBoundNode(experimentTimestampIntervalNode);
    bindClassBoundNode(descriptionNode); 
    bindClassBoundNode(orderedDateNode); 
    bindClassBoundNode(shortCodeNode); 
  
    // Bind nodes with unit
    bindClassBoundNodeWithUnit(scopesCountNode); 
    bindClassBoundNodeWithUnit(priceNode); 
  };

  var initUiData = function(confirmed_order) {
    setTitle(confirmed_order.getTitle());
    setDescription(confirmed_order.getDescription());
    setScopesCount(confirmed_order.getScopesCount());
    setPrice(confirmed_order.getPrice());
    setShortCode(confirmed_order.getShortCode());

    // Set date ordered
    var ordered_date = new Date(confirmed_order.getTimeOrdered());
    var serializeable_ordered_date = new SerializeableDate(
      ordered_date.getUTCFullYear(),
      ordered_date.getUTCMonth(),
      ordered_date.getUTCDate()
    );
    setOrderedDate(serializeable_ordered_date);

    var experiment_timestamp_interval = Utils.makeTimestampIntervalString(
      confirmed_order.getStartTimestamp(),
      confirmed_order.getEndTimestamp()
    );

    console.log(experiment_timestamp_interval);

    setExperimentTimestampInterval(experiment_timestamp_interval);
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

    selectButton(descriptionButtonNode);
    selectPage(descriptionPageNode);
  };

  /**
   * registerChangedTitleListener()
   * @param FuncPtr callback: function(title) {...}
   */
  this.registerChangedTitleListener = function(callback) {
    changedTitleListeners.push(callback);
  }
};

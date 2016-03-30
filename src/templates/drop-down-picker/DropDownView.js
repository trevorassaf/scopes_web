var DropDownView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'dropdown-picker-template';

  /**
   * Revealed dropdown attribute
   */
  var REVEALED_DROPDOWN_ATTR = 'revealed-dropdown';

  /**
   * Root wrapper class
   */
  var ROOT_WRAPPER_CLASS = 'dropdown-picker-wrapper';

  /**
   * Icon type attribute
   */
  var ICON_TYPE_ATTR = 'icon';

  /**
   * Private vars
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var dropDownRootNode = null;

  var isDropDownOpen = false;
  var dropDownItemViews = [];
  var onClickCallbacks = [];

  var _this = this;

  /**
   * Dom nodes
   */
  var inputFieldWrapperNode = {
    className: 'input-field-wrapper',
    node: null
  };

  var inputFieldLabelNode = {
    className: 'input-field-label',
    node: null
  };

  var dropDownIconNode = {
    className: 'dropdown-icon',
    node: null
  }; 

  var dropDownListNode = {
    className: 'dropdown-list',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    // Input field wrapper
    inputFieldWrapperNode.node = Utils.bindNode(
      dropDownRootNode,
      inputFieldWrapperNode.className
    );

    // Input field label
    inputFieldLabelNode.node = Utils.bindNode(
      dropDownRootNode,
      inputFieldLabelNode.className
    );

    // Dropdown icon
    dropDownIconNode.node = Utils.bindNode(
      dropDownRootNode,
      dropDownIconNode.className
    );

    // Dropdown list
    dropDownListNode.node = Utils.bindNode(
      dropDownRootNode,
      dropDownListNode.className
    );

    // Attach click event listener
    dropDownRootNode.onclick = function() {
      if (isDropDownOpen) {
        closeDropDown();
      } else {
        openDropDown(); 
      }
    }; 

    // Close dropdown when user clicks away from ui element 
    Utils.bindClickBeyondNode(dropDownRootNode, closeDropDown);
  };

  var closeDropDown = function() {
    isDropDownOpen = false;
    Utils.hideNode(dropDownListNode.node);
    dropDownRootNode.removeAttribute(REVEALED_DROPDOWN_ATTR);
  };

  var openDropDown = function() {
    isDropDownOpen = true;
    Utils.showNode(dropDownListNode.node);
    dropDownRootNode.setAttribute(REVEALED_DROPDOWN_ATTR, '');
  };

  var bindModel = function(drop_down_model) {
    // Bind to model state
    drop_down_model
      .bindSelectedItem(setSelectedItem)
      .bindDropDownItemModels(setDropDownItemModels);
  };

  var configureDropDownItems = function(drop_down_data) {
    for (var i = 0; i < drop_down_data.length; ++i) {
      var label = drop_down_data[i]; 
      var drop_down_item_view = new DropDownItemView(
        templateStore,
        dropDownListNode.node
      );

      drop_down_item_view.init(label, i);
      drop_down_item_view.bindClick(invokeOnclickCallbacks);
      dropDownItemViews.push(drop_down_item_view);
    }
  };

  var invokeOnclickCallbacks = function(index) {
    onClickCallbacks.forEach(function(callback) {
      callback(this, index);
    }, _this); 
  };

  var setIcon = function(icon_type) {
    dropDownIconNode.node.setAttribute(ICON_TYPE_ATTR, icon_type); 
  };

  var setSelectedItem = function(drop_down_item) {
    inputFieldLabelNode.node.innerHTML = drop_down_item.getLabel();
  };

  var setDropDownItemModels = function(drop_down_item_models) {
    for (var i = 0; i < drop_down_item_models.length; ++i) {
      // Initialize drop down view
      var drop_down_item_view = new DropDownItemView(
        templateStore,
        dropDownListNode.node
      );

      drop_down_item_view.init(i, drop_down_item_models[i]);

      // Bind click event listeners
      drop_down_item_view.bindClick(invokeOnclickCallbacks);

      dropDownItemViews.push(drop_down_item_view);
    }
  };

  /**
   * Privileged functions 
   */
  this.init = function(
      drop_down_model,
      icon_type
  ) {
    // Synthesize template into document
    dropDownRootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_WRAPPER_CLASS
    );  

    // Bind nodes
    bindNodes();

    // Configure icon
    setIcon(icon_type);

    // Bind model
    bindModel(drop_down_model);
  };

  this.bindClick = function(callback) {
    onClickCallbacks.push(callback);
  };
};

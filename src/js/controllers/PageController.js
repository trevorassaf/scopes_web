var PageController = function(
  side_panel_view,
  new_experiment_view
) {

  /**
   * Ui Views
   */
  var sidePanelView = side_panel_view;
  var newExperimentView = new_experiment_view;

  var currentPageView = null;

  /**
   * Private functions
   */
  var hideCurrentPage = function() {
    console.assert(currentPageView != null);
    currentPageView.hide();
    currentPageView = null;
  };

  var changePage = function(next_page_view) {
    hideCurrentPage();
    showPage(next_page_view);
  };

  var showPage = function(next_page_view) {
    console.assert(currentPageView == null);
    next_page_view.show();
    currentPageView = next_page_view;
  };

  var bindSidePanelButtons = function() {
    sidePanelView.bindNewExperimentTabClick(function() {
      changePage(newExperimentView); 
    });
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Select initial page
    sidePanelView.selectNewExperimentTab();
    showPage(newExperimentView);

    // Bind event listeners to side-panel button clicks
    bindSidePanelButtons();
  };
};

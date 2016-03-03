var CenterPanelController = (function() {

  /**
   * Dom ui id's
   */
  var TITLE_LABEL_ID = 'center-page-title-label';

  /**
   * Attribute names
   */
  var HIDDEN_PAGE_ATTRIBUTE = 'hidden-page';

  /**
   * Dom nodes
   */
  var currentPage = null;
  var titleLabel = null;

  /**
   * Center panel data structures
   */
  var addExperimentPageInfo = {
    title: 'Add Experiment',
    container_id : 'add-exp-center-page',
    container : null
  };
  
  var myExperimentsPageInfo = {
    title: 'My Experiments',
    container_id : 'my-exp-center-page',
    container : null
  };
  
  var recordedExperimentsPageInfo = {
    title: 'Recorded Experiments',
    container_id : 'recorded-exp-center-page',
    container : null
  };

  var monitorExperimentPageInfo = {
    title: 'Monitor Experiment',
    container_id : 'monitor-exp-center-page',
    container : null
  };

  /**
   * changePage()
   * - change page to page indicated in 'next_page_info'
   */
  this.changePage = function(next_page_info) {
    // Check to see if 'currentPage' is set. If not, then this ui module is
    // just being initialized.
    if (currentPage != null) {
      // Skip change b/c we're switching to the same page
      if (next_page_info.container_id == currentPage.id) {
        return;
      }

      // Hide 'currentPage'
      console.assert(
        !currentPage.hasAttribute(HIDDEN_PAGE_ATTRIBUTE),
        'Illegal state: current page (id=' + currentPage.id + ') should not have the HIDDEN_LABEL_ATTRIBUTE'
      );

      currentPage.setAttribute(HIDDEN_PAGE_ATTRIBUTE, '');
    }

    // Display page indicated by 'next_page_info'
    if (next_page_info.container == null) {
      next_page_info.container = document.getElementById(next_page_info.container_id);
      console.assert(
        next_page_info.container != null,
        'Illegal state: next page (id=' + next_page_info.container_id + ') has invalid id'
      );
    }

    titleLabel.innerHTML = next_page_info.title;
    currentPage = next_page_info.container;
    currentPage.removeAttribute(HIDDEN_PAGE_ATTRIBUTE);
  };

  /**
   * init()
   * - bind dom ui nodes and event listeners, configure ui for startup
   */
  this.init = function() {
    // Load dom ui nodes
    titleLabel = document.getElementById(TITLE_LABEL_ID);

    // Configure Ui
    displayAddExperimentPage(); 
  };
  
  /**
   * dispalyAddExperimentPage()
   * - hide previous page and display add experiment page 
   */
  this.displayAddExperimentPage = function() {
    changePage(addExperimentPageInfo);
  };

  /**
   * dispalyMyExperimentsPage()
   * - hide previous page and display my experiments page 
   */
  this.displayMyExperimentsPage = function() {
    changePage(myExperimentsPageInfo);
  };

  /**
   * dispalyRecordedExperimentsPage()
   * - hide previous page and display recorded experiments page 
   */
  this.displayRecordedExperimentsPage = function() {
    changePage(recordedExperimentsPageInfo);
  };
  
  /**
   * dispalyMonitorExperimentPage()
   * - hide previous page and display monitor experiment page 
   */
  this.displayMonitorExperimentPage = function() {
    changePage(monitorExperimentPageInfo);
  };

  return {
    init: init,
    displayAddExperimentPage: displayAddExperimentPage,
    displayMyExperimentsPage: displayMyExperimentsPage,
    displayRecordedExperimentsPage: displayRecordedExperimentsPage,
    displayMonitorExperimentPage: displayMonitorExperimentPage
  };

})();

<!DOCTYPE html>
<html lang='en'>
  <head>
    <link rel='import' href='../lib/libraries.html?fd=p'>
    <link rel='import' href='../styles/styles.html?fd=p' />
    <link rel='import' href='../js/js.html?d=<?php echo date('his');?>' />
  </head>

  <body unresolved>
    <div id='side-panel'>
      <!-- User name -->
      <div id='side-panel-user-container'>
        <img id='side-panel-user-profile-pic' src='../../../../assets/default_profile_images/blue-ring.png' />
        <span id='side-panel-user-label'>Kalyna Petrusha</span>
      </div>

      <!-- Mvs home button -->
      <div id='home-nav-container'>
        <div id='home-nav-label'>
          <span><iron-icon id='home-nav-label-back-icon' icon='chevron-left'></iron-icon></span>  
          <div id='home-nav-label-home-icon-container'><iron-icon id='home-nav-label-home-icon' icon='home'></iron-icon></div>
          <span id='home-nav-label-name'>MVS Home</span>
        </div>
      </div>
      
      <!-- Mvs dashboard title -->
      <div id='dash-title-container'>
        <div id='dash-title-label'>
          <span><iron-icon icon='dashboard' id='dash-title-label-icon'></iron-icon></span>
          <span id='dash-title-label-name'>MVS Dashboard</span>
          <span id='dash-title-label-version'>1.0.0</span>
        </div>
      </div>

      <!-- Page navigation buttons -->
      <div id='nav-btns-container'>
        <div id='add-exp-btn' class='dash-nav-panel-btn'>
          <iron-icon icon='add-circle-outline'></iron-icon>
          <span class='nav-btn-label'>Add Experiment</span>
        </div>
        <div id='my-exp-btn' class='dash-nav-panel-btn'>
          <iron-icon icon='group-work'></iron-icon>
          <span class='nav-btn-label'>My Experiments</span>
        </div>
        <div id='recorded-exp-btn' class='dash-nav-panel-btn'>
          <iron-icon icon='cloud-queue'></iron-icon>
          <span class='nav-btn-label'>Recorded Experiments</span>
        </div>
        <div id='monitor-exp-btn' class='dash-nav-panel-btn'>
          <iron-icon icon='settings-input-svideo'></iron-icon>
          <span class='nav-btn-label'>Monitor Experiment</span>
        </div>
      </div>
    </div>

    <!-- Center panel -->
    <div id='center-panel'></div>
  </body>
</html>

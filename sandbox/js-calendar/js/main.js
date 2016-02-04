window.onload = function() {
  var disallowed_week_days = new Set([0, 6]);
  var calendar = new Calendar(
      'calendar-id',
      disallowed_week_days,
      {},
      3,
      0 
  );
  calendar.init();
};

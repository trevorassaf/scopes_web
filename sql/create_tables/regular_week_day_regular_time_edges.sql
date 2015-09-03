/**
 * Regular week day/regular time join table
 */
CREATE TABLE RegularWeekDayRegularTimeEdges (
  id INT UNSIGNED NOT NULL,
  regularWeekDayId INT UNSIGNED NOT NULL,
  FOREIGN KEY(regularWeekDayId) REFERENCES RegularWeekDays(id),
  regularTimeId INT UNSIGNED NOT NULL,
  FOREIGN KEY(regularTimeId) REFERENCES RegularTimes(id)
);


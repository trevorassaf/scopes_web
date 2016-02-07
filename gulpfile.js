var gulp = require('gulp');
var gutil = require('gulp-util');
var concat = require('gulp-concat');
var cssmin = require('gulp-minify-css');
var rename = require("gulp-rename");
var sass = require('gulp-sass');
var uglify = require('gulp-uglify');

gulp.task('default', function() {
    // place code for your default task here
});

/**
 * Scripts task
 * - concatenates and minifies js
 */
gulp.task('scripts', function() {
  return gulp.src('./src/js/**/*.js')
    .pipe(concat('app.js'))
    .pipe(gulp.dest('./dist/js/'))
    .pipe(uglify())
    .pipe(rename({
      suffix: '.min'
    }))
    .pipe(gulp.dest('./dist/js/'));
});

/**
 * Styles task
 * - concatenates and minifies css
 */
gulp.task('styles', function() {
  return gulp.src('./src/css/**/*.css')
    .pipe(gulp.dest('./dist/css/'))
    .pipe(cssmin())
    .pipe(rename({
      suffix: '.min'
    }))
    .pipe(gulp.dest('./dist/css/'));
});

/**
 * Watch task
 * - tracks changes to src files and automatically runs deployment tasks
 */
gulp.task('watch', function() {
  gulp.watch('./src/js/**/*.js', ['scripts']);
  gulp.watch('./src/css/**/*.css', ['styles']);
});

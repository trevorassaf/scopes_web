var gulp = require('gulp');
var gutil = require('gulp-util');
var concat = require('gulp-concat');
var cssmin = require('gulp-minify-css');
var rename = require("gulp-rename");
var sass = require('gulp-sass');
var uglify = require('gulp-uglify');
var ignore = require('gulp-ignore');

gulp.task('default', function() {
    // place code for your default task here
});

/**
 * Scripts task
 * - concatenates and minifies js
 */
gulp.task('scripts', function() {
  return gulp.src([
      './src/js/**/*.js',
      './src/templates/**/*.js',
    ])
    .pipe(concat('app.js'))
    .pipe(gulp.dest('./dist/js/'))
    // .pipe(ignore.exclude([ "*|)}>#*.map" ]))
    // .pipe(uglify())
    // .pipe(rename({
    //   suffix: '.min'
    // }))
    .pipe(gulp.dest('./dist/js/'));
});

gulp.task('templates', function() {
  return gulp.src([
    './src/templates/**/*.html'
  ])
  .pipe(concat('templates.html'))
  .pipe(gulp.dest('./dist/templates/'));
});

/**
 * Styles task
 * - concatenates and minifies css
 */
gulp.task('styles', function() {
  return gulp.src('./src/**/*.css')
    .pipe(concat('app.css'))
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
  gulp.watch('./src/**/*.js', ['scripts']);
  gulp.watch('./src/**/*.css', ['styles']);
});

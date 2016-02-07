function goodbyeWorld() {
  console.log('Goodbye world!');
}

function helloWorld() {
  console.log('Hell world!');
}

window.onload = function() {
  console.log('HELLO BEBE KPEEZ <3 <3');
  var template = document.querySelector('#test-template');
  var new_template = document.importNode(template.content, true);
  document.body.appendChild(new_template);
};

function testFunc() {
  console.log('TEST SHIT');
}

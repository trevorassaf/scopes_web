window.onload = function() {
  console.log('HELLO BEBE KPEEZ <3 <3');
  var template = document.querySelector('#test-template');
  var new_template = document.importNode(template.content, true);
  document.body.appendChild(new_template);
};

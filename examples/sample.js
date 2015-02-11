var obj = require('../index');

obj.notification("Notification sample", "opened from", "NODEJS");
obj.dialog();

var types = obj.getDialogTypes();
var responses = obj.getResponseTypes();

for(var i in types){
	var result = obj.dialog("Title: ["+i+"]", "os value: "+types[i], types[i]);
	console.log("clicked button id: ["+ result + "]"+obj.answerToString(result) + " for dialog type: " + obj.typeToString(types[i]));
}
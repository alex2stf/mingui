var obj = require('../index');

obj.notification("Notification sample", "opened from", "NODEJS");
obj.dialog();

var types = obj.getDialogTypes();
var responses = obj.getResponseTypes();

for(var i in types){
	var result = obj.dialog("Title: ["+i+"]", "os value: "+types[i], types[i]);
	console.log(obj.answerToString(result));
		switch(result){
		case DGANSW_OK:
			console.log("dialog closed OK");
			break;
		case DGANSW_CANCEL:
			console.log("dialog closed CANCEL");
			break;
	}
}
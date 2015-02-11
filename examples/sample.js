var obj = require('../index');

console.log(DGANSW_OK);

//obj.print_color("44", 2, 4, true, "data");
//obj.notification("Notification sample", "opened from", "NODEJS");

obj.dialog();
var types = obj.getDialogTypes();
var responses = obj.getResponseTypes();



//for(var i in types){
	for(var i in types){
//	console.log(i + " = " + types[i]);
	var result = obj.dialog("Title: ["+i+"]", "os value: "+types[i], types[i]);
		switch(result){
		case DGANSW_OK:
			console.log("dialog closed OK");
			break;
		case DGANSW_CANCEL:
			console.log("dialog closed CANCEL");
			break;
	}
}
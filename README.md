mingui
=========
### MINimal Graphic User Interface tools

Requirements:
----------
### MacOSX
before installing on macosx, run ```sudo xcodebuild -license``` in terminal to agree xcode license and agreement

Sample:
----------
```javascript
var obj = require('mingui');

//notification sample:
obj.notification("Notification sample", "opened from", "NODEJS");

//dialog sample with no arguments
obj.dialog(); 

var types = obj.getDialogTypes();
var responses = obj.getResponseTypes();


//iterate all supported dialog types:
for(var i in types){
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
```
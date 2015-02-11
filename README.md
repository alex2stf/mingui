mingui
=========
### MINimal Graphic User Interface tools

MACOSX install:
----------
before installing on macosx, run sudo xcodebuild -license in terminal to agree xcode license

Sample:
----------
```javascript
var obj = require('../index');

obj.notification("Notification sample", "opened from", "NODEJS");
obj.dialog();

var types = obj.getDialogTypes();
var responses = obj.getResponseTypes();

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
mingui
=========
### MINimal Graphic User Interface tools

Install:
----------
```npm install mingui```

Requirements:
----------
### MacOSX
before installing on macosx, run ```sudo xcodebuild -license``` in terminal to agree xcode license and agreement

### Linux
before installing you can check if pgk-config requirements exist:
```shell
pkg-config gtk+-2.0 --cflags
pkg-config libnotify --cflags
```
to install dependecies:
```shell
apt-get install libnotify-dev
apt-get install libgtk2.0-dev
```

### Windows
no requirements needed

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

addon will modify your global context, by adding the following numeric constants:
```javascript
DGANSW_OK, DGANSW_CANCEL, DGANSW_YES, DGANSW_NO, DGANSW_CLOSED, DG_DEFAULT, DG_OK_WARNING, 
DG_OK_ERROR, DG_OK_INFO, DG_OKCANCEL, DG_OKCANCEL_WARNING, DG_OKCANCEL_ERROR, DG_OKCANCEL_INFO, 
DG_YESNO, DG_YESNO_WARNING, DG_YESNO_ERROR, DG_YESNO_INFO
```


therefore you will be able to use them like:
```javascript
int result = obj.dialog("Title", "message", DG_OKCANCEL_WARNING);
// result may have value DGANSW_OK or DGANSW_CANCEL
```
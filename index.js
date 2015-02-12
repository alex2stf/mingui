var mingui = null;
mingui = require("./build/Release/mingui");
module.exports = mingui;

var answtype = mingui.getResponseTypes();
var dlgtypes = mingui.getDialogTypes();

for(var i in answtype){
	GLOBAL[i] = answtype[i];
}

for(var i in dlgtypes){
	GLOBAL[i] = dlgtypes[i];
}

console.log(GLOBAL);
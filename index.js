var mingui = null;
mingui = require("./build/Release/mingui");
module.exports = mingui;

var answtype = mingui.getResponseTypes();

GLOBAL.DGANSW_OK = answtype.DGANSW_OK;
GLOBAL.DGANSW_CANCEL = answtype.DGANSW_CANCEL;
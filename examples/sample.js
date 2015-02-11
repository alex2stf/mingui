var obj = require('../build/Release/mingui');

console.log(obj);

//obj.print_color("44", 2, 4, true, "data");
obj.notification("Notification sample", "opened from", "NODEJS");

{
  "targets": [
    
 	
    	
    {
      "target_name": "mingui"
      
      ,"include_dirs": [
	      "src/astox-deps"
	  ]
	  
	  ,'defines': [
              'ASTX_ENABLE_NODEJS'
		]
	  

	  ,"sources": [
		"src/mingui.cc",
		"src/astox-deps/StringAlg.cpp"
	  ]
	  
	  ,"conditions": [
		['OS=="win"', {
			"defines": [ "ASTOX_OS_WINDOWS" ]
          	}],
		['OS=="linux"', {
			"sources": [
				"src/mingui.cc",
				"src/astox-deps/StringAlg.cpp",
				"src/astox-deps/MinGUI.cpp"
			],
			"defines": [ "ASTOX_ENABLE_GTK" ],
			"include_dirs": ['<!@(pkg-config gtk+-2.0 --cflags-only-I | sed s/-I//g)', '<!@(pkg-config libnotify --cflags-only-I | sed s/-I//g)'],
			 "libraries": ['<!@(pkg-config gtk+-2.0 --libs)', '<!@(pkg-config libnotify --libs)']
          	}],

          	['OS=="mac"', {
          		"defines": [ "__MACOSX_CORE__" ],
          		"cflags":["-framework", "Cocoa", "-x", "objective-c"],
          		"sources": [ "src/astox-deps/MinGUI.mm" ]
          	}]  
	  ]
    }
  ]
}

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
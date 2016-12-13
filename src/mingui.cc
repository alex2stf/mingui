/*
 * shllex.cc
 *
 *  Created on: Jan 8, 2015
 *      Author: alexandru
 */





#include <iostream>

#include "StringAlg.h"
#include "Macros.h"
#include <node.h>




#include "astox-deps/MinGUI.h"




using namespace v8;
using namespace astox::stringAlg;

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;



Handle<Function> dialogHandler;

void notification(const FunctionCallbackInfo<Value>& args) {
  
  Isolate* isolate = args.GetIsolate();
  std::string title;
  std::string subtitle;
  std::string footer;

  if(args[0]->IsString()){
	  title = v8Value2StdString(args[0]);
  }
  if(args[1]->IsString()){
	  subtitle = v8Value2StdString(args[1]);
  }
  if(args[2]->IsString()){
	  footer = v8Value2StdString(args[2]);
  }

  MINGUI_Notification(title.c_str(), subtitle.c_str(), footer.c_str(), 1);

  args.GetReturnValue().Set(Number::New(isolate, 9));
}


void getResponseTypes(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Object> cobj = Object::New(isolate);
  cobj->Set( String::NewFromUtf8(isolate, "DGANSW_OK"), Number::New(isolate, DGANSW_OK));
  cobj->Set( String::NewFromUtf8(isolate, "DGANSW_CANCEL"), Number::New(isolate, DGANSW_CANCEL));
  cobj->Set( String::NewFromUtf8(isolate, "DGANSW_YES"), Number::New(isolate, DGANSW_YES));
  cobj->Set( String::NewFromUtf8(isolate, "DGANSW_NO"), Number::New(isolate, DGANSW_NO));
  cobj->Set( String::NewFromUtf8(isolate, "DGANSW_CLOSED"), Number::New(isolate, DGANSW_CLOSED));
  args.GetReturnValue().Set(cobj);
}

void getDialogTypes(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Object> cobj = Object::New(isolate);
  cobj->Set( String::NewFromUtf8(isolate, "DG_DEFAULT"), Number::New(isolate, DG_DEFAULT));
  cobj->Set( String::NewFromUtf8(isolate,"DG_OK_WARNING"), Number::New(isolate, DG_OK_WARNING));
  cobj->Set( String::NewFromUtf8(isolate, "DG_OK_ERROR"), Number::New(isolate, DG_OK_ERROR));
  cobj->Set( String::NewFromUtf8(isolate, "DG_OK_INFO"), Number::New(isolate, DG_OK_INFO));
  cobj->Set( String::NewFromUtf8(isolate, "DG_OKCANCEL"), Number::New(isolate, DG_OKCANCEL));
  cobj->Set( String::NewFromUtf8(isolate, "DG_OKCANCEL_WARNING"), Number::New(isolate, DG_OKCANCEL_WARNING));
  cobj->Set( String::NewFromUtf8(isolate, "DG_OKCANCEL_ERROR"), Number::New(isolate, DG_OKCANCEL_ERROR));
  cobj->Set( String::NewFromUtf8(isolate, "DG_OKCANCEL_INFO"), Number::New(isolate, DG_OKCANCEL_INFO));
  cobj->Set( String::NewFromUtf8(isolate, "DG_YESNO"), Number::New(isolate, DG_YESNO));
  cobj->Set( String::NewFromUtf8(isolate, "DG_YESNO_WARNING"), Number::New(isolate, DG_YESNO_WARNING));
  cobj->Set( String::NewFromUtf8(isolate, "DG_YESNO_ERROR"), Number::New(isolate, DG_YESNO_ERROR));
  cobj->Set( String::NewFromUtf8(isolate, "DG_YESNO_INFO"), Number::New(isolate, DG_YESNO_INFO));
  args.GetReturnValue().Set(cobj);
}

void typeToString(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  const char * response;

	int type = Handle<Number>::Cast(args[0])->Uint32Value();
	switch(type) {
	case DG_DEFAULT:
		response = "DG_DEFAULT";
		break;
	case DG_OKCANCEL:
		response = "DG_OKCANCEL";
		break;
	case DG_OKCANCEL_ERROR:
		response = "DG_OKCANCEL_ERROR";
		break;
	case DG_OKCANCEL_INFO:
		response = "DG_OKCANCEL_INFO";
		break;
	case DG_OKCANCEL_WARNING:
		response = "DG_OKCANCEL_WARNING";
		break;
	case DG_OK_ERROR:
		response = "DG_OK_ERROR";
		break;
	case DG_OK_INFO:
		response = "DG_OK_INFO";
		break;
	case DG_OK_WARNING:
		response = "DG_OK_WARNING";
		break;
	case DG_YESNO:
		response = "DG_YESNO";
		break;
	case DG_YESNO_ERROR:
		response = "DG_YESNO_ERROR";
		break;
	case DG_YESNO_INFO:
		response = "DG_YESNO_INFO";
		break;
	case DG_YESNO_WARNING:
		response = "DG_YESNO_WARNING";
		break;

	default:
		response = "undefined";
		break;
	}


	args.GetReturnValue().Set(String::NewFromUtf8(isolate, response));
}


void answerToString(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
  const char * response;

	int type = Handle<Number>::Cast(args[0])->Uint32Value();
	switch(type) {
	case DGANSW_OK:
		response = "DGANSW_OK";
		break;
	case DGANSW_CANCEL:
		response = "DGANSW_CANCEL";
		break;
	case DGANSW_YES:
		response = "DGANSW_YES";
		break;
	case DGANSW_NO:
		response = "DGANSW_NO";
		break;
	case DGANSW_CLOSED:
		response = "DGANSW_CLOSED";
		break;
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, response));
}


void dialog(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	v8::String::Utf8Value uftValue(args[0]->ToString());
	v8::String::Utf8Value uftValue2(args[1]->ToString());
	char * _tlt = *uftValue;
	char * _stlt = *uftValue2;
	int type = Handle<Number>::Cast(args[2])->Uint32Value();
	int result = MINGUI_Dialog(_tlt, _stlt, NULL, type, 0);
	args.GetReturnValue().Set(Number::New(isolate, result));

}

void init(Handle<Object> exports) {

#ifdef ASTOX_ENABLE_GTK
	int argc = 1;
	char xx1[] = "1"; // Now these are null-terminated strings
	char xx2[] = "2";
	char* argv[] = {xx1, xx2};
	char** argvp = argv;
	gtk_init (&argc, &argvp);
#endif

	NODE_SET_METHOD(exports, "notification", notification);
	NODE_SET_METHOD(exports, "dialog", dialog);
	NODE_SET_METHOD(exports, "getDialogTypes", getDialogTypes);
	NODE_SET_METHOD(exports, "getResponseTypes", getResponseTypes);
	NODE_SET_METHOD(exports, "answerToString", answerToString);
	NODE_SET_METHOD(exports, "typeToString", typeToString);
 

}

NODE_MODULE(mingui, init)

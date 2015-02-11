/*
 * shllex.cc
 *
 *  Created on: Jan 8, 2015
 *      Author: alexandru
 */





#include <iostream>
#ifdef __MACOSX_CORE__
#include "astox-deps/MinGUI.h"
#endif
#include "StringAlg.h"
#include "Macros.h"
#include <node.h>
#include <v8.h>
using namespace v8;
using namespace astox::stringAlg;


Handle<Function> dialogHandler;

Handle<Value> notification(const Arguments& args) {
  HandleScope scope;

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

  MINGUI_Notification(title.c_str(), subtitle.c_str(), footer.c_str());

  return scope.Close(Number::New(9));
}


Handle<Value> getResponseTypes(const Arguments& args) {
  HandleScope scope;
  Local<Object> cobj = Object::New();
  cobj->Set( String::New("DGANSW_OK"), Number::New(DGANSW_OK));
  cobj->Set( String::New("DGANSW_CANCEL"), Number::New(DGANSW_CANCEL));
  cobj->Set( String::New("DGANSW_YES"), Number::New(DGANSW_YES));
  cobj->Set( String::New("DGANSW_NO"), Number::New(DGANSW_NO));
  cobj->Set( String::New("DGANSW_CLOSED"), Number::New(DGANSW_CLOSED));


  return scope.Close(cobj);
}

Handle<Value> getDialogTypes(const Arguments& args) {
  HandleScope scope;
  Local<Object> cobj = Object::New();
  cobj->Set( String::New("DG_DEFAULT"), Number::New(DG_DEFAULT));
  cobj->Set( String::New("DG_OK_WARNING"), Number::New(DG_OK_WARNING));
  cobj->Set( String::New("DG_OK_ERROR"), Number::New(DG_OK_ERROR));
  cobj->Set( String::New("DG_OK_INFO"), Number::New(DG_OK_INFO));
  cobj->Set( String::New("DG_OKCANCEL"), Number::New(DG_OKCANCEL));
  cobj->Set( String::New("DG_OKCANCEL_WARNING"), Number::New(DG_OKCANCEL_WARNING));
  cobj->Set( String::New("DG_OKCANCEL_ERROR"), Number::New(DG_OKCANCEL_ERROR));
  cobj->Set( String::New("DG_OKCANCEL_INFO"), Number::New(DG_OKCANCEL_INFO));
  cobj->Set( String::New("DG_YESNO"), Number::New(DG_YESNO));
  cobj->Set( String::New("DG_YESNO_WARNING"), Number::New(DG_YESNO_WARNING));
  cobj->Set( String::New("DG_YESNO_ERROR"), Number::New(DG_YESNO_ERROR));
  cobj->Set( String::New("DG_YESNO_INFO"), Number::New(DG_YESNO_INFO));

  return scope.Close(cobj);
}


void c_dialogHandler(int stat, int pid) {
	printf("         dialog clicked result: %i    \n", stat);
	if(!dialogHandler->IsUndefined()) {
		Handle<Value> filArgs[1];
		Local<Object> filObj = Object::New();
		filObj->Set( String::New("stat"), Number::New(stat));
		filObj->Set( String::New("pid"), Number::New(pid));
		dialogHandler->Call(Context::GetCurrent()->Global(), 1, filArgs);
	}
}

Handle<Value> dialog(const Arguments& args) {
  HandleScope scope;


	v8::String::Utf8Value uftValue(args[0]->ToString());
	v8::String::Utf8Value uftValue2(args[1]->ToString());
	char * _tlt = *uftValue;
	char * _stlt = *uftValue2;
	int type = Handle<Number>::Cast(args[2])->Uint32Value();
	int result = MINGUI_Dialog(_tlt, _stlt, NULL, type, 0);




   return scope.Close(Number::New(result));
}

void init(Handle<Object> exports) {

  exports->Set(String::NewSymbol("notification"), FunctionTemplate::New(notification)->GetFunction());
  exports->Set(String::NewSymbol("dialog"), FunctionTemplate::New(dialog)->GetFunction());
  exports->Set(String::NewSymbol("getDialogTypes"), FunctionTemplate::New(getDialogTypes)->GetFunction());
  exports->Set(String::NewSymbol("getResponseTypes"), FunctionTemplate::New(getResponseTypes)->GetFunction());

}

NODE_MODULE(mingui, init)

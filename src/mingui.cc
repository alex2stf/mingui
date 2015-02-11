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

Handle<Value> notification(const Arguments& args) {
  HandleScope scope;

  printf("hello world");
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

  Notification(title.c_str(), subtitle.c_str(), footer.c_str());

  return scope.Close(Number::New(9));
}

void init(Handle<Object> exports) {

  exports->Set(String::NewSymbol("notification"), FunctionTemplate::New(notification)->GetFunction());

}

NODE_MODULE(mingui, init)

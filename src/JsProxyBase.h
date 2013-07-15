/*
 * JsProxyBase.h
 *
 *  Created on: Apr 22, 2013
 *      Author: dcampbell
 */

#ifndef JSPROXYBASE_H_
#define JSPROXYBASE_H_

#include <v8.h>
#include <string>

namespace jessip
{

class JsObjectFactory;

class JsProxyBase
{
public:
   JsProxyBase();
   virtual ~JsProxyBase();
   virtual void addRef();
   virtual void release();
   static std::string toString(v8::Handle<v8::Value> value,
         const char* defaultStr = 0);
protected:
   friend class JsObjectFactory;
   virtual void onInitializeProxy(v8::Handle<v8::Object> obj,
         JsObjectFactory& factory);
private:
   int mRefCount;
};

#define _QUOTE(arg)       #arg
#define _STR(arg)         _QUOTE(arg)

#define ADD_JS_METHOD(TEMP,NAME,TYPE)  (TEMP)->Set(v8::String::New(_STR(NAME)),\
      v8::FunctionTemplate::New(TYPE::_intern_##NAME))

#define ADD_JS_RW_PROPERTY(TEMP,NAME,TYPE)   (TEMP)->SetAccessor(\
      v8::String::New(_STR(NAME)),TYPE::_intern_get##NAME,TYPE::_intern_set##NAME)

#define DEFINE_JS_METHOD(TYPE,NAME)    static void _intern_##NAME(\
      const v8::FunctionCallbackInfo<v8::Value>& info) { TYPE* self=(TYPE*)v8::Handle<v8::External>::Cast(\
      info.Holder()->GetInternalField(0))->Value();self->NAME(info);}\
      void NAME(const v8::FunctionCallbackInfo<v8::Value>& info)

#define DEFINE_JS_RW_PROPERTY(TYPE,NAME)  static void _intern_get##NAME(\
      v8::Local<v8::String> property,const v8::PropertyCallbackInfo<v8::Value>& info)\
      { TYPE* self=(TYPE*)v8::Handle\
      <v8::External>::Cast(info.Holder()->GetInternalField(0))->Value();\
      self->get##NAME(property,info);}\
      void get##NAME(v8::Local<v8::String> property,const v8::PropertyCallbackInfo<v8::Value>& info);\
      static void _intern_set##NAME(v8::Local<v8::String> property,v8::Local<v8::Value> value,\
      const v8::PropertyCallbackInfo<void>& info)\
      {TYPE* self=(TYPE*)v8::Handle<v8::External>::Cast(info.Holder()->\
      GetInternalField(0))->Value();self->set##NAME(property,value,info);}\
      void set##NAME(v8::Local<v8::String> property,v8::Local<v8::Value> value,\
      const v8::PropertyCallbackInfo<void>& info);


} /* namespace sipmod */
#endif /* JSPROXYBASE_H_ */

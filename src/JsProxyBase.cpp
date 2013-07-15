/*
 * JsProxyBase.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: dcampbell
 */

#include "JsProxyBase.h"

namespace jessip
{

JsProxyBase::JsProxyBase() :
      mRefCount(1)
{
}

JsProxyBase::~JsProxyBase()
{
}

void JsProxyBase::addRef()
{
   mRefCount++;
}

void JsProxyBase::release()
{
   mRefCount--;
   if (mRefCount < 1)
   {
      delete this;
   }
}

void JsProxyBase::onInitializeProxy(v8::Handle<v8::Object> obj,
      JsObjectFactory& factory)
{
}

std::string JsProxyBase::toString(v8::Handle<v8::Value> value,
      const char* defaultStr)
{
   if (value->IsUndefined())
   {
      std::string def(defaultStr ? defaultStr : "");
      return def;
   }
   v8::String::Utf8Value str(value->ToString());
   std::string ret(*str);
   return ret;
}

} /* namespace sipmod */

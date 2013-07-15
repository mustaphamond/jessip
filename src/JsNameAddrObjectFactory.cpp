/*
 * JsNameAddrObjectFactory.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: dcampbell
 */

#include "JsNameAddrObjectFactory.h"

namespace jessip
{

JsNameAddrObjectFactory::JsNameAddrObjectFactory()
{
}

JsNameAddrObjectFactory::~JsNameAddrObjectFactory()
{
}

v8::Handle<v8::Value> JsNameAddrObjectFactory::createObjectInstance(
         const char* address)
{
   return v8::Undefined(v8::Isolate::GetCurrent());
}

JsProxyBase* JsNameAddrObjectFactory::onCreateProxyObject()
{
   return 0;
}

void JsNameAddrObjectFactory::onAddTemplateMethods(v8::Handle<v8::ObjectTemplate> temp)
{
}


} /* namespace jessip */

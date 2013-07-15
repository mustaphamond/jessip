/*
 * JsObjectFactory.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: dcampbell
 */

#include "JsObjectFactory.h"
#include "JsProxyBase.h"

namespace jessip
{

JsObjectFactory::JsObjectFactory()
{
}

JsObjectFactory::~JsObjectFactory()
{
   if (!m_template.IsEmpty())
   {
      m_template.Dispose(v8::Isolate::GetCurrent());
   }
}

void JsObjectFactory::onSetupTemplate()
{
   if (!m_template.IsEmpty())
   {
      return;
   }
   v8::HandleScope handleScope;
   v8::Handle<v8::ObjectTemplate> temp = onCreateObjectTemplate();
   temp->SetInternalFieldCount(1);
   m_template.Reset(v8::Isolate::GetCurrent(), temp);
   onAddTemplateMethods(temp);
}

v8::Handle<v8::ObjectTemplate> JsObjectFactory::onCreateObjectTemplate()
{
   v8::HandleScope handleScope;
   v8::Handle<v8::ObjectTemplate> temp = v8::ObjectTemplate::New();
   return handleScope.Close(temp);
}

void JsObjectFactory::onAddTemplateMethods(v8::Handle<v8::ObjectTemplate> temp)
{
}

v8::Handle<v8::Value> JsObjectFactory::createObjectInstance()
{
   v8::HandleScope handleScope;
   onSetupTemplate();
   v8::Handle<v8::ObjectTemplate> temp = v8::Handle<v8::ObjectTemplate>::New(
         v8::Isolate::GetCurrent(), m_template);
   v8::Handle<v8::Object> o = temp->NewInstance();
   v8::Persistent<v8::Object> obj;
   obj.Reset(v8::Isolate::GetCurrent(), o);
   JsProxyBase* proxy = onCreateProxyObject();
   o->SetInternalField(0, v8::External::New(proxy));
   obj.MakeWeak(proxy, weakCallback);
   proxy->onInitializeProxy(o, *this);
   return handleScope.Close(o);
}

void JsObjectFactory::createObjectInstance(v8::Handle<v8::Object> parentObj,
      const char* memberName)
{
   v8::Handle<v8::Value> obj = createObjectInstance();
   parentObj->Set(v8::String::New(memberName), obj);
}

JsProxyBase* JsObjectFactory::getProxyFromJsObject(v8::Handle<v8::Object> obj)
{
   v8::Handle<v8::External> ext = v8::Handle<v8::External>::Cast(
         obj->GetInternalField(0));
   JsProxyBase* ret = (JsProxyBase*) ext->Value();
   return ret;
}

JsProxyBase* JsObjectFactory::onCreateProxyObject()
{
   return new JsProxyBase;
}

void JsObjectFactory::weakCallback(v8::Isolate* isolate,
      v8::Persistent<v8::Object>* obj, JsProxyBase* proxy)
{
   proxy->release();
   (*obj).Dispose(v8::Isolate::GetCurrent());
   (*obj).Clear();
}

}

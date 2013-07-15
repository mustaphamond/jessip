/*
 * CallDialogSet.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: dcampbell
 */

#include "CallDialogSet.h"

namespace jessip
{

CallDialogSet::CallDialogSet(resip::DialogUsageManager& dum,
      JsSIPFactory& factory) :
      resip::AppDialogSet(dum), m_factory(factory)
{
   m_dialogObject.Reset(v8::Isolate::GetCurrent(), v8::Object::New());
}

CallDialogSet::CallDialogSet(resip::DialogUsageManager& dum,
      JsSIPFactory& factory, v8::Handle<v8::Object> dialogObject) :
      resip::AppDialogSet(dum), m_factory(factory)
{
   m_dialogObject.Reset(v8::Isolate::GetCurrent(), dialogObject);
}

CallDialogSet::~CallDialogSet()
{
   v8::HandleScope scope(v8::Isolate::GetCurrent());
   v8::Handle<v8::Object> obj = getDialogObject();
   v8::Handle<v8::Value> arg=v8::Handle<v8::Value>::Cast(obj);
   v8::Handle<v8::Value> destroyValue = obj->Get(v8::String::New("destroy"));
   if ((!destroyValue.IsEmpty()) && (destroyValue->IsFunction()))
   {
      v8::Handle<v8::Function> f = v8::Handle<v8::Function>::Cast(destroyValue);
      f->Call(obj, 1, &arg);
   }
   if (!m_dialogObject.IsEmpty())
   {
      m_dialogObject.Dispose(v8::Isolate::GetCurrent());
   }
}

v8::Handle<v8::Object> CallDialogSet::getDialogObject()
{
   v8::HandleScope scope(v8::Isolate::GetCurrent());
   v8::Handle<v8::Object> dialogObj = v8::Handle<v8::Object>::New(
         v8::Isolate::GetCurrent(), m_dialogObject);
   return scope.Close(dialogObj);
}

} /* namespace jessip */

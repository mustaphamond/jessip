/*
 * JsSIPMessageObjectFactory.cpp
 *
 *  Created on: Apr 23, 2013
 *      Author: dcampbell
 */

#include "JsSIPMessageObjectFactory.h"
#include <sstream>
#include <string>

namespace jessip
{

JsSIPMessageObjectFactory::JsSIPMessageObjectFactory()
{
}

JsSIPMessageObjectFactory::~JsSIPMessageObjectFactory()
{
}

v8::Handle<v8::Value> JsSIPMessageObjectFactory::createObjectInstance(
      JsSIPFactory& factory, const resip::SipMessage& msg)
{
   v8::HandleScope scope(v8::Isolate::GetCurrent());
   v8::Handle<v8::Value> ret = JsObjectFactory::createObjectInstance();
   InternalSipMessage* sip = (InternalSipMessage*) getProxyFromJsObject(
         ret->ToObject());
   sip->m_msg = msg;
   sip->m_factory = &factory;
   ret->ToObject()->SetHiddenValue(v8::String::New("SipMessage"),
         v8::External::New(&sip->m_msg));
   return scope.Close(ret);
}

JsProxyBase* JsSIPMessageObjectFactory::onCreateProxyObject()
{
   return new InternalSipMessage;
}

void JsSIPMessageObjectFactory::onAddTemplateMethods(
      v8::Handle<v8::ObjectTemplate> temp)
{
   // Methods
   ADD_JS_METHOD(temp, toString, InternalSipMessage);
   // Properties
   ADD_JS_RW_PROPERTY(temp, from, InternalSipMessage);
}

JsSIPMessageObjectFactory::InternalSipMessage::InternalSipMessage() :
      m_factory(0)
{
}

JsSIPMessageObjectFactory::InternalSipMessage::~InternalSipMessage()
{
}

void JsSIPMessageObjectFactory::InternalSipMessage::toString(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
   std::ostringstream stream;
   stream << m_msg;
   info.GetReturnValue().Set(v8::String::New(stream.str().c_str()));
}

void JsSIPMessageObjectFactory::InternalSipMessage::getfrom(
      v8::Local<v8::String> property,
      const v8::PropertyCallbackInfo<v8::Value>& info)
{
}

void JsSIPMessageObjectFactory::InternalSipMessage::setfrom(
      v8::Local<v8::String> property, v8::Local<v8::Value> value,
      const v8::PropertyCallbackInfo<void>& info)
{
   // Preserve the tag parameter
   resip::Data tag(m_msg.header(resip::h_From).param(resip::p_tag));
   resip::NameAddr addr(resip::Data(JsProxyBase::toString(value)));
   m_msg.header(resip::h_From) = addr;
   m_msg.header(resip::h_From).param(resip::p_tag) = tag;
}

} /* namespace jessip */

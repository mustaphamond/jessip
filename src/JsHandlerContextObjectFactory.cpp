/*
 * JsHandlerContextObjectFactory.cpp
 *
 *  Created on: Apr 23, 2013
 *      Author: dcampbell
 */

#include "JsHandlerContextObjectFactory.h"
#include <resip/dum/ServerInviteSession.hxx>
#include <resip/dum/ClientInviteSession.hxx>
#include <resip/dum/InviteSession.hxx>

namespace jessip
{

JsHandlerContextObjectFactory::JsHandlerContextObjectFactory()
{
}

JsHandlerContextObjectFactory::~JsHandlerContextObjectFactory()
{
}

v8::Handle<v8::Value> JsHandlerContextObjectFactory::createObjectInstance(
      JsSIPFactory& factory,
      resip::InviteSessionHandle* inviteHandle,
      resip::ServerInviteSessionHandle* serverInviteHandle,
      resip::ClientInviteSessionHandle* clientInviteHandle,
      const resip::SipMessage* msg, const resip::SdpContents* sdp)
{
   v8::HandleScope scope(v8::Isolate::GetCurrent());
   v8::Handle<v8::Value> ret = JsObjectFactory::createObjectInstance();
   Context* context = (Context*) getProxyFromJsObject(ret->ToObject());
   if (inviteHandle)
   {
      context->m_inviteSessionHandle = *inviteHandle;
      context->m_inviteSession = context->m_inviteSessionHandle.get();
   }
   if (serverInviteHandle)
   {
      context->m_serverInviteSessionHandle = *serverInviteHandle;
      context->m_inviteSession = context->m_serverInviteSessionHandle.get();
   }
   if (clientInviteHandle)
   {
      context->m_clientInviteSessionHandle = *clientInviteHandle;
      context->m_inviteSession = context->m_clientInviteSessionHandle.get();
   }
   if (msg)
   {
      v8::Handle<v8::Value> msgObj = m_msgFactory.createObjectInstance(factory, *msg);
      ret->ToObject()->Set(v8::String::New("msg"), msgObj);
   }
   return scope.Close(ret);
}

JsProxyBase* JsHandlerContextObjectFactory::onCreateProxyObject()
{
   return new Context;
}

void JsHandlerContextObjectFactory::onAddTemplateMethods(
      v8::Handle<v8::ObjectTemplate> temp)
{
   // Methods
   ADD_JS_METHOD(temp, accept, Context);
   ADD_JS_METHOD(temp, reject, Context);
   ADD_JS_METHOD(temp, end, Context);
}

JsHandlerContextObjectFactory::Context::Context() :
      m_inviteSession(0)
{
}

JsHandlerContextObjectFactory::Context::~Context()
{
}

void JsHandlerContextObjectFactory::Context::accept(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
}

void JsHandlerContextObjectFactory::Context::reject(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
   int code = 603;
   if ((info.Length() > 0) && (info[0]->IsInt32()))
   {
      code = info[0]->ToInt32()->Value();
   }
   m_inviteSession->reject(code);
}

void JsHandlerContextObjectFactory::Context::end(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
   m_inviteSession->end();
}


} /* namespace jessip */

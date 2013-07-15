/*
 * JsSIPObject.cpp
 *
 *  Created on: Mar 14, 2013
 *      Author: dcampbell
 */

#include "JsSIPObject.h"
#include <stdio.h>
#include "InviteSessionHandler.h"
#include "DialogSetFactory.h"
#include "Exception.h"
#include <rutil/Log.hxx>
#include "JsSIPFactory.h"
#include "ClientSubscriptionHandler.h"
#include "CallDialogSet.h"

namespace jessip
{

JsSIPObject::JsSIPObject(JsSIPFactory& factory) :
      m_factory(factory)
{
   m_transportTypeMap["tls"] = resip::TLS;
   m_transportTypeMap["tcp"] = resip::TCP;
   m_transportTypeMap["udp"] = resip::UDP;

   m_ipVersion["v4"] = resip::V4;
   m_ipVersion["v6"] = resip::V6;
}

JsSIPObject::~JsSIPObject()
{
}

void JsSIPObject::onAddTemplateMethods(v8::Handle<v8::ObjectTemplate> temp)
{
   // Methods
   ADD_JS_METHOD(temp, initialize, JsSIPProxy);
   ADD_JS_METHOD(temp, end, JsSIPProxy);
   ADD_JS_METHOD(temp, log, JsSIPProxy);
   ADD_JS_METHOD(temp, addTransport, JsSIPProxy);
   ADD_JS_METHOD(temp, run, JsSIPProxy);
   ADD_JS_METHOD(temp, sendMessage, JsSIPProxy);
   ADD_JS_METHOD(temp, createInviteMessage, JsSIPProxy);
   ADD_JS_METHOD(temp, scheduleEvent, JsSIPProxy);
   ADD_JS_METHOD(temp, subscribeToEvent, JsSIPProxy);

   // Constants
   temp->Set(v8::String::New("version"), v8::String::New("jessip 0.1"),
         v8::ReadOnly);

   v8::Handle<v8::Object> transportType = v8::Object::New();
   for (std::map<std::string, resip::TransportType>::const_iterator it =
         m_transportTypeMap.begin(); it != m_transportTypeMap.end(); it++)
   {
      transportType->Set(v8::String::New(it->first.c_str()),
            v8::Integer::New((int) it->second), v8::ReadOnly);
   }
   temp->Set(v8::String::New("transportType"), transportType, v8::ReadOnly);

   v8::Handle<v8::Object> ipVersion = v8::Object::New();
   for (std::map<std::string, resip::IpVersion>::const_iterator it =
         m_ipVersion.begin(); it != m_ipVersion.end(); it++)
   {
      ipVersion->Set(v8::String::New(it->first.c_str()),
            v8::Integer::New((int) it->second), v8::ReadOnly);
   }
   temp->Set(v8::String::New("ipVersion"), ipVersion, v8::ReadOnly);
}

JsProxyBase* JsSIPObject::onCreateProxyObject()
{
   return new JsSIPProxy(m_factory);
}

JsSIPObject::JsSIPProxy::JsSIPProxy(JsSIPFactory& factory) :
      m_factory(factory), m_sipStack(0), m_dum(0), m_inviteHandler(0), m_masterProfile(
            new resip::MasterProfile), m_appDialogSetFactory(0), m_shutdown(
            false)
{
}

JsSIPObject::JsSIPProxy::~JsSIPProxy()
{
   if (m_dum)
   {
      delete m_dum;
      m_dum = 0;
   }
   if (m_sipStack)
   {
      m_sipStack->shutdown();
      delete m_sipStack;
      m_sipStack = 0;
   }
   if (m_inviteHandler)
   {
      delete m_inviteHandler;
      m_inviteHandler = 0;
   }
   if (!m_resipHandler.IsEmpty())
   {
      m_resipHandler.Dispose(v8::Isolate::GetCurrent());
   }
}

void JsSIPObject::JsSIPProxy::initialize(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
   v8::HandleScope scope(info.GetIsolate());
   if (m_sipStack)
   {
      return;
   }
   resip::Log::initialize(resip::Log::Cout, resip::Log::Crit,
         resip::Data("jessip"));
   m_sipStack = new resip::SipStack();
   m_dum = new resip::DialogUsageManager(*m_sipStack);
   v8::Handle<v8::Object> handler = v8::Handle<v8::Object>::New(
         info.GetIsolate(), m_resipHandler);
   m_inviteHandler = new InviteSessionHandler(m_factory, handler);
   setupSIPProfile();
}

void JsSIPObject::JsSIPProxy::end(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
   m_shutdown = true;
   m_dum->shutdown(0);
}

void JsSIPObject::JsSIPProxy::log(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
   for (int i = 0; i < info.Length(); i++)
   {
      printf("%s\n", JsProxyBase::toString(info[i]).c_str());
   }
}

void JsSIPObject::JsSIPProxy::addTransport(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
   resip::Data interface(resip::Data::Empty);
   for (int i = 0; i < info.Length(); i++)
   {
      if (!info[i]->IsObject())
      {
         std::string err("Invalid argument for 'addTransport'");
         info.GetReturnValue().Set(
               v8::ThrowException(v8::String::New(err.c_str())));
         return;
      }
      int transportType = (int) resip::UDP;
      if (!info[i]->ToObject()->Get(v8::String::New("type"))->IsUndefined())
      {
         transportType =
               info[i]->ToObject()->Get(v8::String::New("type"))->ToInt32()->Value();
         if ((transportType <= (int) resip::UNKNOWN_TRANSPORT)
               || (transportType >= (int) resip::MAX_TRANSPORT))
         {
            info.GetReturnValue().Set(
                  v8::ThrowException(
                        v8::Exception::TypeError(
                              v8::String::New("Invalid transport type"))));
            return;
         }
      }
      resip::TransportType resipTransportType =
            (resip::TransportType) transportType;

      int port = 5060;
      if (!info[i]->ToObject()->Get(v8::String::New("port"))->IsUndefined())
      {
         port =
               info[i]->ToObject()->Get(v8::String::New("port"))->ToInt32()->Value();
         if ((port < 1) || (port >= 0x00010000))
         {
            info.GetReturnValue().Set(
                  v8::ThrowException(
                        v8::Exception::RangeError(
                              v8::String::New("Invalid port number"))));
            return;
         }
      }

      int ipVersion = (int) resip::V4;
      if (!info[i]->ToObject()->Get(v8::String::New("ipVersion"))->IsUndefined())
      {
         transportType =
               info[i]->ToObject()->Get(v8::String::New("ipVersion"))->ToInt32()->Value();
         if ((transportType < (int) resip::V4)
               || (transportType > (int) resip::V6))
         {
            info.GetReturnValue().Set(
                  v8::ThrowException(
                        v8::Exception::TypeError(
                              v8::String::New("Invalid IP version"))));
            return;
         }
      }

      resip::IpVersion resipIPVersion = (resip::IpVersion) ipVersion;
      if (!m_sipStack->addTransport(resipTransportType, port, resipIPVersion,
            resip::StunDisabled, interface))
      {

      }
   }
}

void JsSIPObject::JsSIPProxy::run(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
   v8::HandleScope handleScope;
   for (;;)
   {
      try
      {
         m_sipStack->process(50);
         while (m_dum->process())
            ;
      }
      catch (Exception& e)
      {
         info.GetReturnValue().Set(
               v8::ThrowException(
                     v8::Exception::Error(v8::String::New(e.getMessage()))));
         break;
      }
      if (m_shutdown)
      {
         m_shutdown = false;
         break;
      }
   }
   m_sipStack->shutdownAndJoinThreads();
   delete m_dum;
   m_dum = 0;
   delete m_sipStack;
   m_sipStack = 0;
}

// sendMessage( <msg>)
void JsSIPObject::JsSIPProxy::sendMessage(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
   v8::HandleScope scope(info.GetIsolate());
   std::string sipMsgString;

   if ((info.Length() < 1) || (!info[0]->IsObject()))
   {
      info.GetReturnValue().Set(
            v8::ThrowException(
                  v8::Exception::TypeError(
                        v8::String::New(
                              "sendMessage expected a SIP message object as first argument"))));
      return;
   }

   v8::Handle<v8::Object> sipMsgObj = info[0]->ToObject();
   if (sipMsgObj->GetHiddenValue(v8::String::New("SipMessage")).IsEmpty())
   {
      sipMsgString = JsProxyBase::toString(info[0]->ToString());
      resip::SharedPtr<resip::SipMessage> newMsg = resip::SharedPtr<
            resip::SipMessage>(
            resip::SipMessage::make(resip::Data(sipMsgString.c_str()), false));
      if (newMsg.get())
      {
         m_dum->send(newMsg);
      }
   }
   else
   {
      v8::Handle<v8::Value> sipMsgPtr = sipMsgObj->GetHiddenValue(
            v8::String::New("SipMessage"));
      v8::Handle<v8::External> ext = v8::Handle<v8::External>::Cast(sipMsgPtr);
      resip::SipMessage* msgValue = new resip::SipMessage(
            *((resip::SipMessage*) ext->Value()));
      resip::SharedPtr<resip::SipMessage> sipMsg(msgValue);
      m_dum->send(sipMsg);
   }
}

// Usage: createInviteMessage( <target URL>[, <invite object>]);
//
//        invite object:
//        content:<data>
//        handler: { clientNewSession: <function>, ...}
//        contents: { mime: <mime type>, body: <body> }

void JsSIPObject::JsSIPProxy::createInviteMessage(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
   v8::HandleScope scope(info.GetIsolate());
   if (info.Length() < 1)
   {
      info.GetReturnValue().Set(
            v8::ThrowException(
                  v8::Exception::TypeError(
                        v8::String::New("missing target URL"))));
      return;
   }
   v8::Handle<v8::Object> obj;
   if (info.Length() > 1)
   {
      if (!info[1]->IsObject())
      {
         info.GetReturnValue().Set(
               v8::ThrowException(
                     v8::Exception::TypeError(
                           v8::String::New(
                                 "expected object as second argument"))));
         return;
      }
      obj = v8::Handle<v8::Object>::New(info.GetIsolate(), info[1]->ToObject());
      // TODO: contents
   }
   else
   {
      obj = v8::Object::New();
   }
   resip::NameAddr target(resip::Data(JsProxyBase::toString(info[0]).c_str()));
   CallDialogSet* callDialogSet = new CallDialogSet(*m_dum, m_factory, obj);
   resip::SharedPtr<resip::SipMessage> msg = m_dum->makeInviteSession(target, 0,
         callDialogSet);
   v8::Handle<v8::Value> jsMsg = m_factory.createSipMessageObject(*msg.get());
   info.GetReturnValue().Set(jsMsg);
}

void JsSIPObject::JsSIPProxy::scheduleEvent(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
   v8::HandleScope scope(info.GetIsolate());
   v8::Handle<v8::Function> func;
   v8::Handle<v8::Object> jthis;
   v8::Handle<v8::Value> context;
   int timeout = 0;
   if (info.Length() > 0)
   {
      if (!info[0]->IsFunction())
      {
         info.GetReturnValue().Set(
               v8::ThrowException(
                     v8::Exception::TypeError(
                           v8::String::New(
                                 "Expected a function as a first argument"))));
         return;
      }
      func = v8::Handle<v8::Function>::Cast(info[0]);
   }
   if (info.Length() > 1)
   {
      context = info[1];
   }
   else
   {
      context = v8::Object::New();
   }
   if (info.Length() > 2)
   {
      timeout = info[2]->ToInt32()->Value();
   }
   jthis = info.Holder();
   if (!func.IsEmpty())
   {
      m_dum->getSipStack().postMS(ScheduledEvent(func, jthis, context), timeout,
            m_dum);
   }
}

void JsSIPObject::JsSIPProxy::subscribeToEvent(
      const v8::FunctionCallbackInfo<v8::Value>& info)
{
   v8::HandleScope scope(v8::Isolate::GetCurrent());
   if (info.Length() < 2)
   {
      info.GetReturnValue().Set(
            v8::ThrowException(
                  v8::Exception::TypeError(
                        v8::String::New(
                              "Expects an address and event type arguments"))));
      return;
   }
   resip::NameAddr nameAddr(
         resip::Data(JsProxyBase::toString(info[0]->ToString()).c_str()));
   resip::Data eventType(JsProxyBase::toString(info[1]->ToString()).c_str());
   v8::Handle<v8::Object> dialogObject;
   if ((info.Length() > 2) && (info[2]->IsObject()))
   {
      dialogObject = v8::Local<v8::Object>::New(info.GetIsolate(),
            info[2]->ToObject());
   }
   else
   {
      dialogObject = v8::Object::New();
   }
   CallDialogSet* callDialogSet = new CallDialogSet(*m_dum, m_factory,
         dialogObject);
   v8::Handle<v8::Object> dialogObj = callDialogSet->getDialogObject();
   resip::SharedPtr<resip::SipMessage> msg = m_dum->makeSubscription(nameAddr,
         eventType, callDialogSet);
   ClientSubscriptionHandler* handler = new ClientSubscriptionHandler(m_factory,
         JsProxyBase::toString(info[0]->ToString()).c_str());
   m_dum->addClientSubscriptionHandler(eventType, handler);
   m_dum->send(msg);
}

void JsSIPObject::JsSIPProxy::onInitializeProxy(v8::Handle<v8::Object> obj,
      JsObjectFactory& factory)
{
   v8::HandleScope handleScope;
   v8::Handle<v8::Object> newObj = v8::Object::New();
   m_resipHandler.Reset(v8::Isolate::GetCurrent(), newObj);
   obj->Set(v8::String::New("handlers"), newObj);
}

void JsSIPObject::JsSIPProxy::setupSIPProfile()
{
   m_masterProfile->setUserAgent("jessip");
   m_masterProfile->addSupportedMimeType(resip::INVITE,
         resip::Mime("multipart", "mixed"));
   m_masterProfile->addSupportedMimeType(resip::INVITE,
         resip::Mime("application", "sdp"));
   m_masterProfile->addSupportedMimeType(resip::INVITE,
         resip::Mime("application", "pidf+xml"));
   if (!m_masterProfile->isMethodSupported(resip::INVITE))
   {
      m_masterProfile->addSupportedMethod(resip::INVITE);
   }
   if (!m_masterProfile->isMethodSupported(resip::ACK))
   {
      m_masterProfile->addSupportedMethod(resip::ACK);
   }
   if (!m_masterProfile->isMethodSupported(resip::CANCEL))
   {
      m_masterProfile->addSupportedMethod(resip::CANCEL);
   }
   if (!m_masterProfile->isMethodSupported(resip::OPTIONS))
   {
      m_masterProfile->addSupportedMethod(resip::OPTIONS);
   }
   if (!m_masterProfile->isMethodSupported(resip::BYE))
   {
      m_masterProfile->addSupportedMethod(resip::BYE);
   }
   if (!m_masterProfile->isMethodSupported(resip::UPDATE))
   {
      m_masterProfile->addSupportedMethod(resip::UPDATE);
   }
   if (!m_masterProfile->isMethodSupported(resip::SUBSCRIBE))
   {
      m_masterProfile->addSupportedMethod(resip::SUBSCRIBE);
   }
   if (!m_masterProfile->isMethodSupported(resip::NOTIFY))
   {
      m_masterProfile->addSupportedMethod(resip::NOTIFY);
   }
   m_dum->setMasterProfile(m_masterProfile);

   resip::MessageFilterRule::SchemeList schemeList;
   schemeList.push_back(resip::Symbols::Sip);
   schemeList.push_back(resip::Symbols::Sips);
   schemeList.push_back(resip::Symbols::Tel);

   resip::MessageFilterRuleList ruleList;
   ruleList.push_back(resip::MessageFilterRule(schemeList));

   m_dum->setMessageFilterRuleList(ruleList);

   m_dum->setInviteSessionHandler(m_inviteHandler);
   m_appDialogSetFactory = new DialogSetFactory(m_factory);
   m_dum->setAppDialogSetFactory(
         std::auto_ptr<resip::AppDialogSetFactory>(m_appDialogSetFactory));
}

} /* namespace jessip */

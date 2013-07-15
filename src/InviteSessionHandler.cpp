/*
 * InviteSessionHandler.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: dcampbell
 */

#include "InviteSessionHandler.h"
#include <resip/dum/InviteSession.hxx>
#include <resip/dum/ServerInviteSession.hxx>
#include <resip/dum/ClientInviteSession.hxx>
#include "CallDialogSet.h"

namespace jessip
{

InviteSessionHandler::InviteSessionHandler(JsSIPFactory& factory,
      v8::Handle<v8::Object> obj) :
      m_factory(factory)
{
   m_handler.Reset(v8::Isolate::GetCurrent(), obj);
}

InviteSessionHandler::~InviteSessionHandler()
{
   if (!m_handler.IsEmpty())
   {
      m_handler.Dispose(v8::Isolate::GetCurrent());
   }
}

void InviteSessionHandler::onNewSession(resip::ClientInviteSessionHandle handle,
      resip::InviteSession::OfferAnswerType oat, const resip::SipMessage& msg)
{
   callHandler(handle->getAppDialogSet(), "clientNewSession", 0, 0, &handle,
         &msg, 0);
}

void InviteSessionHandler::onNewSession(resip::ServerInviteSessionHandle handle,
      resip::InviteSession::OfferAnswerType oat, const resip::SipMessage& msg)
{
   callHandler(handle->getAppDialogSet(), "serverNewSession", 0, &handle, 0,
         &msg, 0);
}

void InviteSessionHandler::onSessionExpired(resip::InviteSessionHandle handle)
{
   callHandler(handle->getAppDialogSet(), "sessionExpired", &handle, 0, 0, 0,
         0);
}

void InviteSessionHandler::onFailure(resip::ClientInviteSessionHandle handle,
      const resip::SipMessage& msg)
{
   callHandler(handle->getAppDialogSet(), "sessionExpired", 0, 0, &handle, &msg,
         0);
}

void InviteSessionHandler::onEarlyMedia(resip::ClientInviteSessionHandle handle,
      const resip::SipMessage& msg, const resip::SdpContents& sdp)
{
   callHandler(handle->getAppDialogSet(), "earlyMedia", 0, 0, &handle, &msg,
         &sdp);
}

void InviteSessionHandler::onProvisional(
      resip::ClientInviteSessionHandle handle, const resip::SipMessage& msg)
{
   callHandler(handle->getAppDialogSet(), "provisional", 0, 0, &handle, &msg,
         0);
}

void InviteSessionHandler::onConnected(resip::ClientInviteSessionHandle handle,
      const resip::SipMessage& msg)
{
   callHandler(handle->getAppDialogSet(), "clientConnected", 0, 0, &handle,
         &msg, 0);
}

void InviteSessionHandler::onConnected(resip::InviteSessionHandle handle,
      const resip::SipMessage& msg)
{
   callHandler(handle->getAppDialogSet(), "connected", &handle, 0, 0, &msg, 0);
}

void InviteSessionHandler::onConnectedConfirmed(
      resip::InviteSessionHandle handle, const resip::SipMessage &msg)
{
   callHandler(handle->getAppDialogSet(), "connectedConfirmed", &handle, 0, 0,
         &msg, 0);
}

void InviteSessionHandler::onTerminated(resip::InviteSessionHandle handle,
      resip::InviteSessionHandler::TerminatedReason reason,
      const resip::SipMessage* related)
{
   // TODO: add TerminatedReason
   callHandler(handle->getAppDialogSet(), "terminated", &handle, 0, 0,
         related, 0);
}

void InviteSessionHandler::onForkDestroyed(
      resip::ClientInviteSessionHandle handle)
{
   callHandler(handle->getAppDialogSet(), "forkDestroyed", 0, 0, &handle, 0, 0);
}

void InviteSessionHandler::onRedirected(resip::ClientInviteSessionHandle handle,
      const resip::SipMessage& msg)
{
   callHandler(handle->getAppDialogSet(), "redirected", 0, 0, &handle, &msg, 0);
}

void InviteSessionHandler::onAnswer(resip::InviteSessionHandle handle,
      const resip::SipMessage& msg, const resip::SdpContents& sdp)
{
   callHandler(handle->getAppDialogSet(), "answer", &handle, 0, 0, &msg, &sdp);
}

void InviteSessionHandler::onOffer(resip::InviteSessionHandle handle,
      const resip::SipMessage& msg, const resip::SdpContents& sdp)
{
   callHandler(handle->getAppDialogSet(), "offer", &handle, 0, 0, &msg, &sdp);
}

void InviteSessionHandler::onOfferRequired(resip::InviteSessionHandle handle,
      const resip::SipMessage& msg)
{
   callHandler(handle->getAppDialogSet(), "offerRequired", &handle, 0, 0, &msg,
         0);
}

void InviteSessionHandler::onOfferRejected(resip::InviteSessionHandle handle,
      const resip::SipMessage* msg)
{
   callHandler(handle->getAppDialogSet(), "offerRejected", &handle, 0, 0, msg,
         0);
}

void InviteSessionHandler::onInfo(resip::InviteSessionHandle handle,
      const resip::SipMessage& msg)
{
   callHandler(handle->getAppDialogSet(), "info", &handle, 0, 0, &msg, 0);
}

void InviteSessionHandler::onInfoSuccess(resip::InviteSessionHandle handle,
      const resip::SipMessage& msg)
{
}

void InviteSessionHandler::onInfoFailure(resip::InviteSessionHandle handle,
      const resip::SipMessage& msg)
{
}

void InviteSessionHandler::onMessage(resip::InviteSessionHandle handle,
      const resip::SipMessage& msg)
{
}

void InviteSessionHandler::onMessageSuccess(resip::InviteSessionHandle handle,
      const resip::SipMessage& msg)
{
}

void InviteSessionHandler::onMessageFailure(resip::InviteSessionHandle handle,
      const resip::SipMessage& msg)
{
}

void InviteSessionHandler::onReadyToSend(resip::InviteSessionHandle handle,
      resip::SipMessage& msg)
{
}

void InviteSessionHandler::onRefer(resip::InviteSessionHandle handle,
      resip::ServerSubscriptionHandle, const resip::SipMessage& msg)
{
}

void InviteSessionHandler::onReferNoSub(resip::InviteSessionHandle handle,
      const resip::SipMessage& msg)
{
}

void InviteSessionHandler::onReferRejected(resip::InviteSessionHandle handle,
      const resip::SipMessage& msg)
{
}

void InviteSessionHandler::onReferAccepted(resip::InviteSessionHandle handle,
      resip::ClientSubscriptionHandle, const resip::SipMessage& msg)
{
}

void InviteSessionHandler::onTargetRefreshed(resip::InviteSessionHandle handle)
{
}

void InviteSessionHandler::callHandler(resip::AppDialogSetHandle handle,
      const char* functionName, resip::InviteSessionHandle* inviteHandle,
      resip::ServerInviteSessionHandle* serverInviteHandle,
      resip::ClientInviteSessionHandle* clientInviteHandle,
      const resip::SipMessage* msg, const resip::SdpContents* sdp)
{
   v8::HandleScope scope(v8::Isolate::GetCurrent());
   CallDialogSet* dialog = dynamic_cast<CallDialogSet*>(handle.get());
   v8::Handle<v8::Object> context = dialog->getDialogObject();
   v8::Handle<v8::Function> function;
   if (context.IsEmpty())
   {
      return;
   }
   v8::Handle<v8::Value> tmp = context->Get(v8::String::New(functionName));
   v8::Handle<v8::Object> v8This;
   v8::Handle<v8::Object> handler = v8::Handle<v8::Object>::New(
         v8::Isolate::GetCurrent(), m_handler);
   if ((tmp.IsEmpty()) || (tmp->IsUndefined()))
   {
      v8This = v8::Handle<v8::Object>::New(v8::Isolate::GetCurrent(),
            m_handler);
      tmp = handler->Get(v8::String::New(functionName));
      if ((tmp.IsEmpty()) || (!tmp->IsFunction()))
      {
         return;
      }
      v8::Handle<v8::Function> f = v8::Handle<v8::Function>::Cast(tmp);
      function = v8::Handle<v8::Function>::New(v8::Isolate::GetCurrent(), f);
   }
   else
   {
      if (tmp->IsFunction())
      {
         v8This = v8::Handle<v8::Object>::New(v8::Isolate::GetCurrent(), tmp->ToObject());
         v8::Handle<v8::Function> f = v8::Handle<v8::Function>::Cast(tmp);
         function = v8::Handle<v8::Function>::New(v8::Isolate::GetCurrent(), f);
      }
      else
      {
         return;
      }
   }
   v8::Handle<v8::Value> arg = m_factory.createHandlerContext(context,
         inviteHandle, serverInviteHandle, clientInviteHandle, msg, sdp);
   function->Call(v8This, 1, &arg);
}

} /* namespace jessip */

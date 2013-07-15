/*
 * ClientSubscriptionHandler.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: dcampbell
 */

#include "ClientSubscriptionHandler.h"
#include "CallDialogSet.h"
#include <v8.h>

namespace jessip
{

ClientSubscriptionHandler::ClientSubscriptionHandler(JsSIPFactory& factory,
      const char* eventType) :
      m_factory(factory), m_eventType(eventType)
{
}

ClientSubscriptionHandler::~ClientSubscriptionHandler()
{
}

void ClientSubscriptionHandler::onUpdatePending(
      resip::ClientSubscriptionHandle handle, const resip::SipMessage& notify,
      bool outOfOrder)
{
   handle->acceptUpdate(200);
}

void ClientSubscriptionHandler::onUpdateActive(
      resip::ClientSubscriptionHandle handle, const resip::SipMessage& notify,
      bool outOfOrder)
{

   v8::HandleScope scope(v8::Isolate::GetCurrent());
   CallDialogSet* dialogSet =
         dynamic_cast<CallDialogSet*>(handle->getAppDialogSet().get());
   v8::Handle<v8::Object> obj = dialogSet->getDialogObject();
   if (obj.IsEmpty())
   {
      handle->rejectUpdate();
      return;
   }
   v8::Handle<v8::Value> cbValue = obj->Get(v8::String::New("notify"));
   if ((!cbValue.IsEmpty()) && (cbValue->IsFunction()))
   {
      v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(cbValue);
      func->Call(obj, 0, 0);
   }
   handle->acceptUpdate(200);
}

void ClientSubscriptionHandler::onUpdateExtension(
      resip::ClientSubscriptionHandle handle, const resip::SipMessage& notify,
      bool outOfOrder)
{
}

int ClientSubscriptionHandler::onRequestRetry(
      resip::ClientSubscriptionHandle handle, int retrySeconds,
      const resip::SipMessage& notify)
{
   return 0;
}

void ClientSubscriptionHandler::onTerminated(
      resip::ClientSubscriptionHandle handle, const resip::SipMessage* msg)
{
}

void ClientSubscriptionHandler::onNewSubscription(
      resip::ClientSubscriptionHandle handle, const resip::SipMessage& notify)
{
}

} /* namespace jessip */

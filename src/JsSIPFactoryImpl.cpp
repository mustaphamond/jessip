/*
 * JsSIPFactoryImpl.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: dcampbell
 */

#include "JsSIPFactoryImpl.h"

namespace jessip
{

JsSIPFactoryImpl::JsSIPFactoryImpl()
{
}

JsSIPFactoryImpl::~JsSIPFactoryImpl()
{
}

v8::Handle<v8::Value> JsSIPFactoryImpl::createSipMessageObject(
      const resip::SipMessage& msg)
{
   return m_sipMsgObjectFactory.createObjectInstance(*this, msg);
}

v8::Handle<v8::Value> JsSIPFactoryImpl::createNameAddrObject(const char* addr)
{
   return m_nameAddrObjectFactory.createObjectInstance(addr);
}

v8::Handle<v8::Value> JsSIPFactoryImpl::createHandlerContext(
      v8::Handle<v8::Object> baseObject,
      resip::InviteSessionHandle* inviteHandle,
      resip::ServerInviteSessionHandle* serverInviteHandle,
      resip::ClientInviteSessionHandle* clientInviteHandle,
      const resip::SipMessage* msg, const resip::SdpContents* sdp)
{
   v8::HandleScope scope(v8::Isolate::GetCurrent());
   if (msg)
   {
      baseObject->Set(v8::String::New("message"), createSipMessageObject(*msg));
   }
   if (sdp)
   {
      //baseObject->Set(v8::String::New("sdp"),sdp->getContents()->);
   }
   baseObject->Set(v8::String::New("dialog"),
         m_contextHandlerFactory.createObjectInstance(*this, inviteHandle,
               serverInviteHandle, clientInviteHandle, msg, sdp));
   return baseObject;
}

} /* namespace jessip */

/*
 * JsSIPFactoryImpl.h
 *
 *  Created on: Jul 9, 2013
 *      Author: dcampbell
 */

#ifndef JSSIPFACTORYIMPL_H_
#define JSSIPFACTORYIMPL_H_

#include "JsSIPFactory.h"
#include "JsSIPMessageObjectFactory.h"
#include "JsNameAddrObjectFactory.h"
#include "JsHandlerContextObjectFactory.h"

namespace jessip
{

class JsSIPFactoryImpl : public jessip::JsSIPFactory
{
public:
   JsSIPFactoryImpl();
   virtual ~JsSIPFactoryImpl();

   virtual v8::Handle<v8::Value> createSipMessageObject(const resip::SipMessage& msg);
   virtual v8::Handle<v8::Value> createNameAddrObject(const char* addr);
   virtual v8::Handle<v8::Value> createHandlerContext(
         v8::Handle<v8::Object> baseObject,
         resip::InviteSessionHandle* inviteHandle,
         resip::ServerInviteSessionHandle* serverInviteHandle,
         resip::ClientInviteSessionHandle* clientInviteHandle,
         const resip::SipMessage* msg, const resip::SdpContents* sdp);
private:
   JsSIPMessageObjectFactory m_sipMsgObjectFactory;
   JsNameAddrObjectFactory m_nameAddrObjectFactory;
   JsHandlerContextObjectFactory m_contextHandlerFactory;
};

} /* namespace jessip */
#endif /* JSSIPFACTORYIMPL_H_ */

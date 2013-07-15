/*
 * JsSIPFactory.h
 *
 *  Created on: Jul 9, 2013
 *      Author: dcampbell
 */

#ifndef JSSIPFACTORY_H_
#define JSSIPFACTORY_H_

#include <v8.h>
#include <resip/stack/SipMessage.hxx>
#include <resip/stack/SdpContents.hxx>
#include <resip/dum/InviteSessionHandler.hxx>

namespace jessip
{

class JsSIPFactory
{
public:
   virtual v8::Handle<v8::Value> createSipMessageObject(
         const resip::SipMessage& msg)=0;
   virtual v8::Handle<v8::Value> createNameAddrObject(const char* addr)=0;
   virtual v8::Handle<v8::Value> createHandlerContext(
         v8::Handle<v8::Object> baseObject,
         resip::InviteSessionHandle* inviteHandle,
         resip::ServerInviteSessionHandle* serverInviteHandle,
         resip::ClientInviteSessionHandle* clientInviteHandle,
         const resip::SipMessage* msg, const resip::SdpContents* sdp)=0;
protected:
   JsSIPFactory();
   virtual ~JsSIPFactory();
};

} /* namespace jessip */
#endif /* JSSIPFACTORY_H_ */

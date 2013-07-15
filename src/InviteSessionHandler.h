/*
 * InviteSessionHandler.h
 *
 *  Created on: Apr 22, 2013
 *      Author: dcampbell
 */

#ifndef INVITESESSIONHANDLER_H_
#define INVITESESSIONHANDLER_H_

#include <resip/dum/InviteSessionHandler.hxx>
#include <v8.h>

namespace jessip
{

class JsSIPFactory;

class InviteSessionHandler : public resip::InviteSessionHandler
{
public:
   InviteSessionHandler(JsSIPFactory& factory, v8::Handle<v8::Object> obj);
   virtual ~InviteSessionHandler();

   virtual void onNewSession(resip::ClientInviteSessionHandle,
         resip::InviteSession::OfferAnswerType oat,
         const resip::SipMessage& msg);

   virtual void onNewSession(resip::ServerInviteSessionHandle,
         resip::InviteSession::OfferAnswerType oat,
         const resip::SipMessage& msg);

   virtual void onSessionExpired(resip::InviteSessionHandle handle);

   virtual void onFailure(resip::ClientInviteSessionHandle,
         const resip::SipMessage& msg);

   virtual void onEarlyMedia(resip::ClientInviteSessionHandle,
         const resip::SipMessage&, const resip::SdpContents&);

   virtual void onProvisional(resip::ClientInviteSessionHandle,
         const resip::SipMessage&);

   virtual void onConnected(resip::ClientInviteSessionHandle,
         const resip::SipMessage& msg);

   virtual void onConnected(resip::InviteSessionHandle,
         const resip::SipMessage& msg);

   virtual void onConnectedConfirmed(resip::InviteSessionHandle,
         const resip::SipMessage &msg);

   virtual void onTerminated(resip::InviteSessionHandle,
         resip::InviteSessionHandler::TerminatedReason reason,
         const resip::SipMessage* related);

   virtual void onForkDestroyed(resip::ClientInviteSessionHandle);

   virtual void onRedirected(resip::ClientInviteSessionHandle,
         const resip::SipMessage& msg);

   virtual void onAnswer(resip::InviteSessionHandle,
         const resip::SipMessage& msg, const resip::SdpContents&);

   virtual void onOffer(resip::InviteSessionHandle,
         const resip::SipMessage& msg, const resip::SdpContents&);

   virtual void onOfferRequired(resip::InviteSessionHandle,
         const resip::SipMessage& msg);

   virtual void onOfferRejected(resip::InviteSessionHandle,
         const resip::SipMessage* msg);

   virtual void onInfo(resip::InviteSessionHandle,
         const resip::SipMessage& msg);

   virtual void onInfoSuccess(resip::InviteSessionHandle,
         const resip::SipMessage& msg);

   virtual void onInfoFailure(resip::InviteSessionHandle,
         const resip::SipMessage& msg);

   virtual void onMessage(resip::InviteSessionHandle,
         const resip::SipMessage& msg);

   virtual void onMessageSuccess(resip::InviteSessionHandle,
         const resip::SipMessage& msg);

   virtual void onMessageFailure(resip::InviteSessionHandle,
         const resip::SipMessage& msg);

   virtual void onReadyToSend(resip::InviteSessionHandle,
         resip::SipMessage& msg);

   virtual void onRefer(resip::InviteSessionHandle handle,
         resip::ServerSubscriptionHandle, const resip::SipMessage& msg);

   virtual void onReferNoSub(resip::InviteSessionHandle handle,
         const resip::SipMessage& msg);

   virtual void onReferRejected(resip::InviteSessionHandle handle,
         const resip::SipMessage& msg);

   virtual void onReferAccepted(resip::InviteSessionHandle handle,
         resip::ClientSubscriptionHandle, const resip::SipMessage& msg);

   virtual void onTargetRefreshed(resip::InviteSessionHandle);

private:
   void callHandler(resip::AppDialogSetHandle handle,
         const char* functionName, resip::InviteSessionHandle* inviteHandle,
         resip::ServerInviteSessionHandle* serverInviteHandle,
         resip::ClientInviteSessionHandle* clientInviteHandle,
         const resip::SipMessage* msg, const resip::SdpContents* sdp);

   JsSIPFactory& m_factory;
   v8::Persistent<v8::Object> m_handler;
};

} /* namespace jessip */
#endif /* INVITESESSIONHANDLER_H_ */

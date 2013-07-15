/*
 * ClientSubscriptionHandler.h
 *
 *  Created on: Jul 9, 2013
 *      Author: dcampbell
 */

#ifndef CLIENTSUBSCRIPTIONHANDLER_H_
#define CLIENTSUBSCRIPTIONHANDLER_H_

#include <resip/dum/SubscriptionHandler.hxx>
#include <resip/stack/SipMessage.hxx>
#include <resip/dum/ClientSubscription.hxx>
#include <resip/dum/Handles.hxx>
#include "JsSIPFactory.h"
#include <string>

namespace jessip
{

class ClientSubscriptionHandler : public resip::ClientSubscriptionHandler
{
public:
   ClientSubscriptionHandler(JsSIPFactory& factory, const char* eventType);
   virtual ~ClientSubscriptionHandler();

   virtual void onUpdatePending(resip::ClientSubscriptionHandle handle,
         const resip::SipMessage& notify, bool outOfOrder);
   virtual void onUpdateActive(resip::ClientSubscriptionHandle handle,
         const resip::SipMessage& notify, bool outOfOrder);
   virtual void onUpdateExtension(resip::ClientSubscriptionHandle handle,
         const resip::SipMessage& notify, bool outOfOrder);
   virtual int onRequestRetry(resip::ClientSubscriptionHandle handle,
         int retrySeconds, const resip::SipMessage& notify);
   virtual void onTerminated(resip::ClientSubscriptionHandle handle,
         const resip::SipMessage* msg);
   virtual void onNewSubscription(resip::ClientSubscriptionHandle handle,
         const resip::SipMessage& notify);
private:
   JsSIPFactory& m_factory;
   std::string m_eventType;
};

} /* namespace jessip */
#endif /* CLIENTSUBSCRIPTIONHANDLER_H_ */

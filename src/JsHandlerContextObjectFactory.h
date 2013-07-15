/*
 * JsHandlerContextObjectFactory.h
 *
 *  Created on: Apr 23, 2013
 *      Author: dcampbell
 */

#ifndef JSHANDLERCONTEXTOBJECTFACTORY_H_
#define JSHANDLERCONTEXTOBJECTFACTORY_H_

#include "JsObjectFactory.h"
#include <resip/dum/InviteSessionHandler.hxx>
#include "JsProxyBase.h"
#include "JsSIPMessageObjectFactory.h"

namespace jessip
{

class JsSIPFactory;

class JsHandlerContextObjectFactory : public jessip::JsObjectFactory
{
public:
   JsHandlerContextObjectFactory();
   virtual ~JsHandlerContextObjectFactory();
   virtual v8::Handle<v8::Value> createObjectInstance(JsSIPFactory& factory,
         resip::InviteSessionHandle* inviteHandle,
         resip::ServerInviteSessionHandle* serverInviteHandle,
         resip::ClientInviteSessionHandle* clientInviteHandle,
         const resip::SipMessage* msg, const resip::SdpContents* sdp);

protected:
   virtual JsProxyBase* onCreateProxyObject();
   virtual void onAddTemplateMethods(v8::Handle<v8::ObjectTemplate> temp);
private:
   class Context : public JsProxyBase
   {
   public:
      Context();
      virtual ~Context();

      DEFINE_JS_METHOD(JsHandlerContextObjectFactory::Context,accept);
      DEFINE_JS_METHOD(JsHandlerContextObjectFactory::Context,reject);
      DEFINE_JS_METHOD(JsHandlerContextObjectFactory::Context,end);

      resip::InviteSessionHandle m_inviteSessionHandle;
      resip::ServerInviteSessionHandle m_serverInviteSessionHandle;
      resip::ClientInviteSessionHandle m_clientInviteSessionHandle;
      resip::InviteSession* m_inviteSession;
   };

   JsSIPMessageObjectFactory m_msgFactory;
};

} /* namespace jessip */
#endif /* JSHANDLERCONTEXTOBJECTFACTORY_H_ */

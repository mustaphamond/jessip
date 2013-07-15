/*
 * JsSIPMessageObjectFactory.h
 *
 *  Created on: Apr 23, 2013
 *      Author: dcampbell
 */

#ifndef JSSIPMESSAGEOBJECTFACTORY_H_
#define JSSIPMESSAGEOBJECTFACTORY_H_

#include "JsObjectFactory.h"
#include <resip/stack/SipMessage.hxx>
#include "JsProxyBase.h"
#include "JsSIPFactory.h"

namespace jessip
{

class JsSIPMessageObjectFactory : public jessip::JsObjectFactory
{
public:
   JsSIPMessageObjectFactory();
   virtual ~JsSIPMessageObjectFactory();
   virtual v8::Handle<v8::Value> createObjectInstance(
         JsSIPFactory& factory, const resip::SipMessage& msg);
protected:
   virtual JsProxyBase* onCreateProxyObject();
   virtual void onAddTemplateMethods(v8::Handle<v8::ObjectTemplate> temp);
private:
   class InternalSipMessage : public JsProxyBase
   {
   public:
      InternalSipMessage();
      virtual ~InternalSipMessage();

      DEFINE_JS_METHOD(JsSIPMessageObjectFactory::InternalSipMessage,toString);

      DEFINE_JS_RW_PROPERTY(JsSIPMessageObjectFactory::InternalSipMessage,from);

      JsSIPFactory* m_factory;
      resip::SipMessage m_msg;
   };
};

} /* namespace jessip */
#endif /* JSSIPMESSAGEOBJECTFACTORY_H_ */

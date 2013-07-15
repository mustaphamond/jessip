/*
 * JsNameAddrObjectFactory.h
 *
 *  Created on: Jul 9, 2013
 *      Author: dcampbell
 */

#ifndef JSNAMEADDROBJECTFACTORY_H_
#define JSNAMEADDROBJECTFACTORY_H_

#include "JsObjectFactory.h"
#include <resip/stack/SipMessage.hxx>
#include "JsProxyBase.h"

namespace jessip
{

class JsNameAddrObjectFactory : public jessip::JsObjectFactory
{
public:
   JsNameAddrObjectFactory();
   virtual ~JsNameAddrObjectFactory();
   virtual v8::Handle<v8::Value> createObjectInstance(
         const char* address);
protected:
   virtual JsProxyBase* onCreateProxyObject();
   virtual void onAddTemplateMethods(v8::Handle<v8::ObjectTemplate> temp);
};

} /* namespace jessip */
#endif /* JSNAMEADDROBJECTFACTORY_H_ */

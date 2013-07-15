/*
 * JsObjectFactory.h
 *
 *  Created on: Jan 10, 2013
 *      Author: dcampbell
 */

#ifndef JSOBJECTFACTORY_H_
#define JSOBJECTFACTORY_H_

#include "v8.h"

namespace jessip
{

class JsProxyBase;

class JsObjectFactory
{
public:
   JsObjectFactory();
   virtual ~JsObjectFactory();
   virtual v8::Handle<v8::Value> createObjectInstance();
   virtual void createObjectInstance(v8::Handle<v8::Object> parentObj,
         const char* memberName);
   static JsProxyBase* getProxyFromJsObject(v8::Handle<v8::Object> obj);
protected:
   virtual void onSetupTemplate();
   virtual v8::Handle<v8::ObjectTemplate> onCreateObjectTemplate();
   virtual void onAddTemplateMethods(v8::Handle<v8::ObjectTemplate> temp);
   virtual JsProxyBase* onCreateProxyObject();
private:
   JsObjectFactory(const JsObjectFactory&);
   const JsObjectFactory& operator =(const JsObjectFactory&);
   static void weakCallback(v8::Isolate* isolate, v8::Persistent<v8::Object>* obj,
         JsProxyBase* proxy);

   v8::Persistent<v8::ObjectTemplate> m_template;
};

}
#endif /* JSOBJECTFACTORY_H_ */

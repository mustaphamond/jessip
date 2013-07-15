/*
 * JsSIPObject.h
 *
 *  Created on: Mar 14, 2013
 *      Author: dcampbell
 */

#ifndef JSSIPOBJECT_H_
#define JSSIPOBJECT_H_

#include "JsObjectFactory.h"
#include "JsProxyBase.h"
#include "ScheduledEvent.h"
#include <rutil/Data.hxx>
#include <resip/stack/SipStack.hxx>
#include <resip/dum/DialogUsageManager.hxx>
#include <resip/dum/MasterProfile.hxx>
#include <resip/dum/AppDialogSetFactory.hxx>
#include <resip/stack/Transport.hxx>
#include <map>
#include <string>

namespace jessip
{

class JsSIPFactory;
class InviteSessionHandler;

class JsSIPObject : public JsObjectFactory
{
public:
   JsSIPObject(JsSIPFactory& factory);
   virtual ~JsSIPObject();
protected:
   virtual void onAddTemplateMethods(v8::Handle<v8::ObjectTemplate> temp);
   virtual JsProxyBase* onCreateProxyObject();
private:

   class JsSIPProxy : public JsProxyBase
   {
   public:
      JsSIPProxy(JsSIPFactory& factory);
      virtual ~JsSIPProxy();

      DEFINE_JS_METHOD(JsSIPObject::JsSIPProxy, initialize);
      DEFINE_JS_METHOD(JsSIPObject::JsSIPProxy, end);
      DEFINE_JS_METHOD(JsSIPObject::JsSIPProxy, log);
      DEFINE_JS_METHOD(JsSIPObject::JsSIPProxy, addTransport);
      DEFINE_JS_METHOD(JsSIPObject::JsSIPProxy, run);
      DEFINE_JS_METHOD(JsSIPObject::JsSIPProxy, sendMessage);
      DEFINE_JS_METHOD(JsSIPObject::JsSIPProxy, createInviteMessage);
      DEFINE_JS_METHOD(JsSIPObject::JsSIPProxy, scheduleEvent);
      DEFINE_JS_METHOD(JsSIPObject::JsSIPProxy, subscribeToEvent);

   protected:
      virtual void onInitializeProxy(v8::Handle<v8::Object> obj, JsObjectFactory& factory);

   private:
      friend class JsSIPObject;
      void setupSIPProfile();

      JsSIPFactory& m_factory;
      resip::SipStack* m_sipStack;
      resip::DialogUsageManager* m_dum;
      InviteSessionHandler* m_inviteHandler;
      resip::SharedPtr<resip::MasterProfile> m_masterProfile;
      resip::AppDialogSetFactory* m_appDialogSetFactory;
      v8::Persistent<v8::Object> m_resipHandler;
      bool m_shutdown;
   };
   JsSIPFactory& m_factory;
   std::map<std::string, resip::TransportType> m_transportTypeMap;
   std::map<std::string, resip::IpVersion> m_ipVersion;
};

} /* namespace jessip */
#endif /* JSSIPOBJECT_H_ */

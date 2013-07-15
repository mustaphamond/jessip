/*
 * CallDialogSet.h
 *
 *  Created on: Apr 22, 2013
 *      Author: dcampbell
 */

#ifndef CALLDIALOGSET_H_
#define CALLDIALOGSET_H_

#include <resip/dum/DialogUsageManager.hxx>
#include <resip/dum/AppDialogSet.hxx>
#include <resip/stack/SipMessage.hxx>
#include "JsSIPFactory.h"
#include <v8.h>

namespace jessip
{

class CallDialogSet : public resip::AppDialogSet
{
public:
   CallDialogSet(resip::DialogUsageManager& dum, JsSIPFactory& factory);
   CallDialogSet(resip::DialogUsageManager& dum, JsSIPFactory& factory,
         v8::Handle<v8::Object> dialogObject);
   virtual ~CallDialogSet();
   v8::Handle<v8::Object> getDialogObject();
private:
   JsSIPFactory& m_factory;
   //v8::Handle<v8::Object> m_dialogObject;
   v8::Persistent<v8::Object> m_dialogObject;
};

} /* namespace jessip */
#endif /* CALLDIALOGSET_H_ */

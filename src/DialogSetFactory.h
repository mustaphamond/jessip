/*
 * DialogSetFactory.h
 *
 *  Created on: Apr 22, 2013
 *      Author: dcampbell
 */

#ifndef DIALOGSETFACTORY_H_
#define DIALOGSETFACTORY_H_

#include <resip/dum/AppDialogSetFactory.hxx>

namespace jessip
{

class JsSIPFactory;

class DialogSetFactory : public resip::AppDialogSetFactory
{
public:
   DialogSetFactory(JsSIPFactory& factory);
   virtual ~DialogSetFactory();
   virtual resip::AppDialogSet* createAppDialogSet(
         resip::DialogUsageManager& dum, const resip::SipMessage& msg);
private:
   JsSIPFactory& m_factory;
};

} /* namespace jessip */
#endif /* DIALOGSETFACTORY_H_ */

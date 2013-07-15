/*
 * DialogSetFactory.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: dcampbell
 */

#include "DialogSetFactory.h"
#include <resip/dum/AppDialogSet.hxx>
#include "CallDialogSet.h"

namespace jessip
{

class JsSIPFactory;

DialogSetFactory::DialogSetFactory(JsSIPFactory& factory) :
      m_factory(factory)
{
}

DialogSetFactory::~DialogSetFactory()
{
}

resip::AppDialogSet* DialogSetFactory::createAppDialogSet(
      resip::DialogUsageManager& dum, const resip::SipMessage& msg)
{
   return new CallDialogSet(dum, m_factory);
}

} /* namespace jessip */

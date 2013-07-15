/*
 * JsSIPUtilities.h
 *
 *  Created on: Jul 10, 2013
 *      Author: dcampbell
 */

#ifndef JSSIPUTILITIES_H_
#define JSSIPUTILITIES_H_

#include <v8.h>
#include <resip/stack/NameAddr.hxx>

namespace jessip
{

class JsSIPUtilities
{
public:
   JsSIPUtilities();
   virtual ~JsSIPUtilities();
   static std::string toString(v8::Handle<v8::Value> value,
         const char* defaultStr = 0);
   static resip::NameAddr getNameAddrFromJSValue(v8::Handle<v8::Value> value);
};

} /* namespace jessip */
#endif /* JSSIPUTILITIES_H_ */

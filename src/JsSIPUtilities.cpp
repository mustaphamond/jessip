/*
 * JsSIPUtilities.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: dcampbell
 */

#include "JsSIPUtilities.h"

namespace jessip
{

JsSIPUtilities::JsSIPUtilities()
{
}

JsSIPUtilities::~JsSIPUtilities()
{
}

std::string JsSIPUtilities::toString(v8::Handle<v8::Value> value,
      const char* defaultStr)
{
   if (value->IsUndefined())
   {
      std::string def(defaultStr ? defaultStr : "");
      return def;
   }
   v8::String::Utf8Value str(value->ToString());
   std::string ret(*str);
   return ret;
}

resip::NameAddr JsSIPUtilities::getNameAddrFromJSValue(v8::Handle<v8::Value> value)
{
   if(value.IsEmpty())
   {
      resip::NameAddr dummyAddr;
      return dummyAddr;
   }
   if(value->IsString())
   {
      resip::NameAddr stringAddr(resip::Data(toString(value).c_str()));
      return stringAddr;
   }
   if(value->IsObject())
   {

   }
   resip::NameAddr addr;
   return addr;
}

} /* namespace jessip */

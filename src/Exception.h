/*
 * Exception.h
 *
 *  Created on: Jan 9, 2013
 *      Author: dcampbell
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>

namespace jessip
{

class Exception
{
public:
   Exception();
   Exception(const Exception& e);
   explicit Exception(const char* msg);
   virtual ~Exception();
   const Exception& operator =(const Exception& e);
   const char* getMessage() const;
private:
   std::string m_msg;
};

} /* namespace jessip */
#endif /* EXCEPTION_H_ */

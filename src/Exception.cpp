/*
 * Exception.cpp
 *
 *  Created on: Jan 9, 2013
 *      Author: dcampbell
 */

#include "Exception.h"

namespace jessip
{

Exception::Exception()
{
}

Exception::Exception(const Exception& e) :
      m_msg(e.m_msg)
{
}

Exception::Exception(const char* msg) :
      m_msg(msg)
{
}

Exception::~Exception()
{
}

const Exception& Exception::operator =(const Exception& e)
{
   m_msg = e.m_msg;
   return (*this);
}

const char* Exception::getMessage() const
{
   return m_msg.c_str();
}

} /* namespace jessip */

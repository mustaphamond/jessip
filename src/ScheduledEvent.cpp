/*
 * ScheduledEvent.cpp
 *
 *  Created on: Apr 24, 2013
 *      Author: dcampbell
 */

#include "ScheduledEvent.h"

namespace jessip
{

ScheduledEvent::ScheduledEvent()
{
}

ScheduledEvent::ScheduledEvent(const ScheduledEvent& evt) :
      m_callback(evt.m_callback)
{
   v8::HandleScope scope(v8::Isolate::GetCurrent());
   m_callback = v8::Handle<v8::Function>::New(v8::Isolate::GetCurrent(),
         evt.m_callback);
   m_this = v8::Handle<v8::Object>::New(v8::Isolate::GetCurrent(), evt.m_this);
   m_context = v8::Handle<v8::Value>::New(v8::Isolate::GetCurrent(),
         evt.m_context);
}

ScheduledEvent::ScheduledEvent(v8::Handle<v8::Function> callback,
      v8::Handle<v8::Object> jthis, v8::Handle<v8::Value> context)
{
   v8::HandleScope scope(v8::Isolate::GetCurrent());
   m_callback = v8::Handle<v8::Function>::New(v8::Isolate::GetCurrent(),
         callback);
   m_this = v8::Handle<v8::Object>::New(v8::Isolate::GetCurrent(), jthis);
   m_context = v8::Handle<v8::Value>::New(v8::Isolate::GetCurrent(), context);
}

ScheduledEvent::~ScheduledEvent()
{
}

const ScheduledEvent& ScheduledEvent::operator =(const ScheduledEvent& evt)
{
   m_callback = v8::Handle<v8::Function>::New(v8::Isolate::GetCurrent(),
         evt.m_callback);
   m_this = v8::Handle<v8::Object>::New(v8::Isolate::GetCurrent(), evt.m_this);
   m_context = v8::Handle<v8::Value>::New(v8::Isolate::GetCurrent(),
         evt.m_context);
   return (*this);
}

void ScheduledEvent::executeCommand()
{
   v8::HandleScope scope(v8::Isolate::GetCurrent());
   v8::Handle<v8::Value> arg[1] =
   { m_context };
   m_callback->Call(m_this, 1, arg);
}

resip::Message* ScheduledEvent::clone() const
{
   return new ScheduledEvent(*this);
}

EncodeStream& ScheduledEvent::encode(EncodeStream& strm) const
{
   return strm;
}

EncodeStream& ScheduledEvent::encodeBrief(EncodeStream& strm) const
{
   return encode(strm);
}

} /* namespace jessip */

/*
 * ScheduledEvent.h
 *
 *  Created on: Apr 24, 2013
 *      Author: dcampbell
 */

#ifndef SCHEDULEDEVENT_H_
#define SCHEDULEDEVENT_H_

#include <resip/dum/DumCommand.hxx>
#include <v8.h>

namespace jessip
{

class ScheduledEvent : public resip::DumCommand
{
public:
   ScheduledEvent();
   ScheduledEvent(const ScheduledEvent& evt);
   ScheduledEvent(v8::Handle<v8::Function> callback,
         v8::Handle<v8::Object> jthis, v8::Handle<v8::Value> context);
   virtual ~ScheduledEvent();
   const ScheduledEvent& operator = (const ScheduledEvent& evt);
   virtual void executeCommand();
   virtual resip::Message* clone() const;
   virtual EncodeStream& encode(EncodeStream& strm) const;
   virtual EncodeStream& encodeBrief(EncodeStream& strm) const;
private:
   v8::Handle<v8::Function> m_callback;
   v8::Handle<v8::Object> m_this;
   v8::Handle<v8::Value> m_context;
};

} /* namespace jessip */
#endif /* SCHEDULEDEVENT_H_ */

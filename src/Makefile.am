CFLAGS = -Wall -std=c99 -O2 -g

AM_CPPFLAGS = -I$(top_srcdir)/include

bin_PROGRAMS = jessip
jessip_SOURCES = main.cpp \
	Runtime.cpp Runtime.h \
	Exception.cpp Exception.h \
	JsObjectFactory.cpp JsObjectFactory.h \
	JsProxyBase.cpp JsProxyBase.h \
	JsSIPObject.cpp JsSIPObject.h \
	InviteSessionHandler.cpp InviteSessionHandler.h \
	DialogSetFactory.cpp DialogSetFactory.h \
	CallDialogSet.cpp CallDialogSet.h \
	JsSIPMessageObjectFactory.cpp JsSIPMessageObjectFactory.h \
	JsHandlerContextObjectFactory.cpp JsHandlerContextObjectFactory.h \
	ScheduledEvent.cpp ScheduledEvent.h \
	JsNameAddrObjectFactory.cpp JsNameAddrObjectFactory.h \
	JsSIPFactory.cpp JsSIPFactory.h \
	JsSIPFactoryImpl.cpp JsSIPFactoryImpl.h \
	ClientSubscriptionHandler.cpp ClientSubscriptionHandler.h \
	JsSIPUtilities.cpp JsSIPUtilities.h

jessip_LDADD = -L$(top_srcdir)/lib \
	-lv8_base.x64 \
	-lv8_snapshot \
	-lrt \
	-ldum \
	-lresip \
	-lrutil \
	-lssl \
	-lcrypto

/*
 * RunTime.h
 *
 *  Created on: Jan 8, 2013
 *      Author: dcampbell
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#include <string>
#include "v8.h"
#include "JsSIPObject.h"
#include "JsSIPFactoryImpl.h"

namespace jessip
{

class Runtime
{
public:
   static int run(int argc, char* argv[]);
private:
   Runtime();
   virtual ~Runtime();
   void processCommandLine(int argc, char* argv[]);
   void runMainScript();
   static void printUsage();
   void setupJsEnvironment();
   void loadMainScript(std::string& script);

   std::string m_scriptFileName;
   //v8::Persistent<v8::Context> m_context;
   v8::Handle<v8::Object> m_rootObj;
   JsSIPObject* m_sip;
   JsSIPFactoryImpl m_sipFactory;
};

} /* namespace jessip */
#endif /* RUNTIME_H_ */

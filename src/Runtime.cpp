/*
 * RunTime.cpp
 *
 *  Created on: Jan 8, 2013
 *      Author: dcampbell
 */

#include "Runtime.h"
#include "Exception.h"
#include <fstream>
#include <streambuf>
#include <stdio.h>

namespace jessip
{

Runtime::Runtime() :
      m_sip(0)
{
}

Runtime::~Runtime()
{
   if (m_sip)
   {
      delete m_sip;
      m_sip = 0;
   }
}

int Runtime::run(int argc, char* argv[])
{
   v8::HandleScope scope;
   Runtime runtime;
   try
   {
      runtime.processCommandLine(argc, argv);
      if (runtime.m_scriptFileName.length() == 0)
      {
         printUsage();
         return 1;
      }
      //runtime.setupJsEnvironment();
      runtime.runMainScript();
   }
   catch (Exception& e)
   {
      printf("%s\n", e.getMessage());
      return -1;
   }
   return 0;
}

void Runtime::processCommandLine(int argc, char* argv[])
{
   for (int i = 1; i < argc; i++)
   {
      std::string arg(argv[i]);
      if (arg[0] == '-')
      {
         // TODO: set argument
      }
      else
      {
         m_scriptFileName = arg;
      }
   }
}

void Runtime::runMainScript()
{
   v8::HandleScope scope(v8::Isolate::GetCurrent());
   v8::Handle<v8::Context> context = v8::Context::New(
         v8::Isolate::GetCurrent());
   v8::Context::Scope contextScope(context);
   m_sip = new JsSIPObject(m_sipFactory);
   m_sip->createObjectInstance(context->Global(), "sip");
   v8::TryCatch tryCatch;
   std::string mainScript;

   loadMainScript(mainScript);
   v8::Handle<v8::Script> script = v8::Script::Compile(
         v8::String::New(mainScript.c_str()),
         v8::String::New(m_scriptFileName.c_str()));
   if (script.IsEmpty())
   {
      throw Exception(JsProxyBase::toString(tryCatch.Exception()).c_str());
   }
   v8::Handle<v8::Value> result = script->Run();
   if (result.IsEmpty())
   {
      // TODO: add log
      v8::String::Utf8Value stackTrace(tryCatch.StackTrace());
      if (stackTrace.length() > 0)
      {
         throw Exception(*stackTrace);
      }
      throw Exception(JsProxyBase::toString(tryCatch.Exception()).c_str());
   }
}

void Runtime::printUsage()
{
   printf("Usage: jessip <script file name>\n");
}

void Runtime::loadMainScript(std::string& script)
{
   try
   {
      std::ifstream t(m_scriptFileName.c_str());
      t.seekg(0, std::ios::end);
      size_t size = t.tellg();
      script.reserve(size);
      t.seekg(0, std::ios::beg);
      script.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
   }
   catch (std::exception&)
   {
      throw Exception("Failed to load script");
   }
}

void Runtime::setupJsEnvironment()
{
   //v8::HandleScope scope;
   //m_context = v8::Context::New();
}

} /* namespace jessip */

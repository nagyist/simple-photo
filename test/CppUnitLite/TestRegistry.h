/*****************************************************************
Copyright 2009 Rui Barbosa Martins 

Licensed under the Apache License, Version 2.0 (the "License"); 
you may not use this file except in compliance with the License. 
You may obtain a copy of the License at 

http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an 
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, 
either express or implied. See the License for the specific
language governing permissions and limitations under the License.
*****************************************************************/

///////////////////////////////////////////////////////////////////////////////
//
// TESTREGISTRY.H
// 
// TestRegistry is a singleton collection of all the tests to run in a system.  
// 
///////////////////////////////////////////////////////////////////////////////

#ifndef TESTREGISTRY_H
#define TESTREGISTRY_H


class Test;
class TestResult;



class TestRegistry
{
public:
	TestRegistry();
	static void addTest (Test *test);
	static void runAllTests (TestResult& result, SimpleString* filter);
	static void ListAllTests();

private:
	static TestRegistry&	instance ();
	void					add (Test *test);
	void					run (TestResult& result, SimpleString* filter);
	
	Test* m_head;
	Test*	m_tail;
};

#endif

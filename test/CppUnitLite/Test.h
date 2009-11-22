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
// TEST.H
//
// This file contains the Test class along with the macros which make effective
// in the harness.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TEST_H
#define TEST_H


#include <cmath>
#include "SimpleString.h"

class TestResult;



class Test
{
public:
	Test (const SimpleString& testName);
  virtual ~Test() {}

	virtual void	run (TestResult& result) = 0;


	void			setNext(Test *test);
	Test			*getNext () const;
	SimpleString& name() { return name_; }

protected:

	bool check (long expected, long actual, TestResult& result, const SimpleString& fileName, long lineNumber);
	bool check (const SimpleString& expected, const SimpleString& actual, TestResult& result, const SimpleString& fileName, long lineNumber);

	SimpleString	name_;
	Test			*next_;

};


#define TEST(testClass, testName)\
  class testClass##_##testName : public Test {\
    public: \
    testClass##_##testName () : Test(#testClass"::"#testName) {} \
      void run (TestResult& result_); \
  }; \
  testClass##_##testName s_instance##testClass##testName; \
	void testClass##_##testName::run(TestResult& result_)



#define CHECK(condition)\
{ if (!(condition)) \
{ result_.addFailure (Failure (name_, __FILE__,__LINE__, #condition)); return; } }

#define CHECK_EQUAL(expected, actual)\
  { if ((expected) != (actual)) { result_.addFailure(Failure(name_, __FILE__, __LINE__, StringFrom(expected), StringFrom(actual))); return; } }

//#define LONGS_EQUAL(expected,actual)\
//{ long actualTemp = actual; \
//  long expectedTemp = expected; \
//  if ((expectedTemp) != (actualTemp)) \
//{ result_.addFailure (Failure (name_, __FILE__, __LINE__, StringFrom(expectedTemp), \
//StringFrom(actualTemp))); return; } }
//
//#define DOUBLES_EQUAL(expected,actual,threshold)\
//{ double actualTemp = actual; \
//  double expectedTemp = expected; \
//  if (fabs ((expectedTemp)-(actualTemp)) > threshold) \
//{ result_.addFailure (Failure (name_, __FILE__, __LINE__, \
//StringFrom((double)expectedTemp), StringFrom((double)actualTemp))); return; } }

#define FAIL(text) \
{ result_.addFailure (Failure (name_, __FILE__, __LINE__,(text))); return; }

#endif

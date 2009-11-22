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



#include "Test.h"
#include "TestRegistry.h"
#include "TestResult.h"
#include "Failure.h"


Test::Test (const SimpleString& testName) 
	: name_ (testName) 
{
	TestRegistry::addTest (this);
}


Test *Test::getNext() const
{
	return next_;
}


void Test::setNext(Test *test)
{	
	next_ = test;
}

bool Test::check(long expected, long actual, TestResult& result, const SimpleString& fileName, long lineNumber) {
	if (expected == actual)
		return true;
	result.addFailure (
		Failure (
			name_, 
			StringFrom (__FILE__), 
			__LINE__, 
			StringFrom (expected), 
			StringFrom (actual)));

	return false;

}


bool Test::check(const SimpleString& expected, const SimpleString& actual, TestResult& result, const SimpleString& fileName, long lineNumber)
{
	if (expected == actual)
		return true;
	result.addFailure (
		Failure (
			name_, 
			StringFrom (__FILE__), 
			__LINE__, 
			expected, 
			actual));

	return false;

}

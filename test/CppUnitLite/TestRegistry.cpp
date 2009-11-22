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
#include "TestResult.h"
#include "TestRegistry.h"

#include <stdio.h>


TestRegistry::TestRegistry()
		: m_head(NULL), m_tail(NULL) {}

void TestRegistry::addTest (Test *test)
{
	instance ().add (test);
}


void TestRegistry::runAllTests (TestResult& result, SimpleString* filter) {
	instance ().run (result, filter);
}


TestRegistry& TestRegistry::instance ()
{
	static TestRegistry registry;
	return registry;
}


void TestRegistry::add (Test *test)
{
	if (m_head == NULL) {
		m_head = m_tail = test;
		return;
	}

	m_tail->setNext(test);
	m_tail = test;
}


void TestRegistry::run (TestResult& result, SimpleString* filter) {
	result.testsStarted ();
	if (filter != NULL) {
		printf("Running tests with filter [%s].\n\n", filter->asCharString());
	}
	int total_tests = 0;
	for (Test *test = m_head; test != 0; test = test->getNext ()) {
		if (filter != NULL && !test->name().Contains(*filter)) {
			continue;
		}
		int failures = result.failures();
		test->run (result);
		++total_tests;
		if (failures != result.failures()) {
			printf("Failed: %s\n", test->name().asCharString());
		} else {
			printf("Ok:     %s\n", test->name().asCharString());
		}
	}
	result.testsEnded (total_tests);
}

void TestRegistry::ListAllTests() {
	int total_tests = 0;
	TestRegistry& reg = TestRegistry::instance();
	printf("-----------------------------------\n");
	printf("Available tests:\n");
	printf("-----------------------------------\n");
	for (Test *test = reg.m_head; test != 0; test = test->getNext ()) {
		printf("%s\n", test->name().asCharString());
		++total_tests;
	}
	printf("-----------------------------------\n");
	printf("Listed a total of %d tests.\n", total_tests);
	printf("-----------------------------------\n");
}

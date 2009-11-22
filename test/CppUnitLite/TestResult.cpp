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


#include "TestResult.h"
#include "Failure.h"
#include "SimpleString.h"

#include <stdio.h>


TestResult::TestResult ()
	: failureCount (0)
{
}

void TestResult::testsStarted () {
	printf("----------------------------------------------\n");
}

void TestResult::addFailure (const Failure& failure)
{
	char buffer[1024];
  sprintf (buffer, "Failure: [%s] line [%ld] in [%s].\n",
		failure.message.asCharString (),
		failure.lineNumber,
		failure.fileName.asCharString ());
  failure_msgs.push_back(new SimpleString(buffer));
	failureCount++;
}

void TestResult::testsEnded (int total_tests)
{
	printf("----------------------------------------------\n");
	for (unsigned int i = 0; i < failure_msgs.size(); ++i) {
		fprintf(stdout, "%s", failure_msgs[i]->asCharString());
		delete failure_msgs[i];
	}
	printf("==============================================\n");
	if (failureCount > 0)
		fprintf (stdout, "There were %d failures out of %d tests\n", failureCount, total_tests);
	else
		fprintf (stdout, "A total of %d tests succeeded\n", total_tests);
}

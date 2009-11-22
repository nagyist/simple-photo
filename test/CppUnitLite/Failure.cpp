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



#include "Failure.h"

#include <stdio.h>
#include <string.h> 


Failure::Failure (const SimpleString&	theTestName, 
				  const SimpleString&	theFileName, 
		          long	 				theLineNumber,
		          const SimpleString&	theCondition) 
  : message (theCondition), 
    testName (theTestName), 
    fileName (theFileName), 
    lineNumber (theLineNumber) {
  char buffer[2048];
  memset(buffer, 0, sizeof(char));
  sprintf(buffer, "%s",
          testName.asCharString());
	message = SimpleString(buffer);
}

Failure::Failure (const SimpleString&	theTestName, 
			 	  const SimpleString&	theFileName, 
				  long					theLineNumber,
				  const SimpleString&	expected,
				  const SimpleString&	actual) 
  : testName (theTestName), 
    fileName (theFileName), 
    lineNumber (theLineNumber) {
  char buffer[2048];
  memset(buffer, 0, sizeof(char));
  sprintf(buffer, "%s expected [%s] but was: [%s].",
          testName.asCharString(), expected.asCharString(),
		      actual.asCharString());
	message = SimpleString(buffer);
}



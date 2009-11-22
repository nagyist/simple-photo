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
// FAILURE.H
//
// Failure is a class which holds information pertaining to a specific
// test failure.  The stream insertion operator is overloaded to allow easy
// display.
//
///////////////////////////////////////////////////////////////////////////////


#ifndef FAILURE_H
#define FAILURE_H

#include "SimpleString.h"


class Failure
{

public:
	Failure (const SimpleString&		theTestName, 
			 const SimpleString&		theFileName, 
			 long	  					theLineNumber,
			 const SimpleString&		theCondition);

	Failure (const SimpleString&		theTestName, 
			 const SimpleString&		theFileName, 
			 long						theLineNumber,
			 const SimpleString&		expected,
			 const SimpleString&		actual);

	SimpleString		message;
	SimpleString		testName;
	SimpleString		fileName;
	long				lineNumber;
};


#endif

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
// SIMPLESTRING.H
//
// One of the design goals of CppUnitLite is to compilation with very old C++
// compilers.  For that reason, I've added a simple string class that provides
// only the operations needed in CppUnitLite.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef SIMPLE_STRING
#define SIMPLE_STRING

#include <wx/wx.h>
#include <wx/colour.h>

class SimpleString {
friend bool	operator== (const SimpleString& left, const SimpleString& right);

public:
	SimpleString ();
	SimpleString (const char *value);
	SimpleString (const SimpleString& other);
	~SimpleString ();

	SimpleString operator= (const SimpleString& other);

	char *asCharString () const;
	int size() const;
	bool Contains(const SimpleString& substring);

private:
	char* buffer;
};

SimpleString StringFrom (bool value);
SimpleString StringFrom (const char *value);
SimpleString StringFrom (const wchar_t *value);
SimpleString StringFrom (long value);
SimpleString StringFrom (double value);
SimpleString StringFrom (const SimpleString& other);
SimpleString StringFrom (int value);
SimpleString StringFrom (unsigned int value);
SimpleString StringFrom (size_t value);
SimpleString StringFrom (const wxString& value);
SimpleString StringFrom (const wxRect& value);
SimpleString StringFrom (const wxSize& value);
SimpleString StringFrom (const wxColour& value);

#endif

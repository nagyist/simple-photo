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



#include "SimpleString.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "simplephoto/core/Macros.h"

static const int DEFAULT_SIZE = 128;

SimpleString::SimpleString ()
: buffer(new char [1])
{
	buffer [0] = '\0';
}


SimpleString::SimpleString (const char *otherBuffer)
: buffer (new char [strlen (otherBuffer) + 1])
{
	strcpy (buffer, otherBuffer);
}

SimpleString::SimpleString (const SimpleString& other)
{
	buffer = new char [other.size() + 1];
	strcpy(buffer, other.buffer);
}


SimpleString SimpleString::operator= (const SimpleString& other)
{
	delete buffer;
	buffer = new char [other.size() + 1];
	strcpy(buffer, other.buffer);
	return *this;
}


char *SimpleString::asCharString () const
{
	return buffer;
}

int SimpleString::size() const {
	return strlen (buffer);
}

SimpleString::~SimpleString ()
{
	delete [] buffer;
}

bool SimpleString::Contains(const SimpleString& substring) {
	for (int i = 0; buffer[i] != 0; ++i) {
		for (int j = 0; substring.buffer[j] != 0; ++j) {
			if (buffer[i + j] != substring.buffer[j]) {
				break;
			} else if (substring.buffer[j + 1] == 0) {
				return true;
			}
		}
	}
	return false;
}


bool operator== (const SimpleString& left, const SimpleString& right)
{
	return !strcmp (left.asCharString (), right.asCharString ());
}


SimpleString StringFrom (bool value)
{
	char buffer [sizeof ("false") + 1];
	sprintf (buffer, "%s", value ? "true" : "false");
	return SimpleString(buffer);
}

SimpleString StringFrom (const char *value) {
	return SimpleString(value);
}

SimpleString StringFrom (const wchar_t *value) {
	return StringFrom(wxString(value));
}

SimpleString StringFrom (long value)
{
	char buffer [DEFAULT_SIZE];
	sprintf (buffer, "%ld", value);

	return SimpleString(buffer);
}

SimpleString StringFrom (double value)
{
	char buffer [DEFAULT_SIZE];
	sprintf (buffer, "%lf", value);
	return SimpleString(buffer);
}

SimpleString StringFrom (const SimpleString& value)
{
	return SimpleString(value);
}

SimpleString StringFrom (int value) {
  char buffer [DEFAULT_SIZE];
  sprintf (buffer, "%d", value);
  return SimpleString(buffer);
}

SimpleString StringFrom (unsigned int value) {
  char buffer [DEFAULT_SIZE];
  sprintf (buffer, "%u", value);
  return SimpleString(buffer);
}

#ifndef _WINDOWS
SimpleString StringFrom (size_t value) {
	char buffer [DEFAULT_SIZE];
	sprintf (buffer, "%d", static_cast<int>(value));
	return SimpleString(buffer);
}
#endif

SimpleString StringFrom (const wxString& value) {
  return SimpleString(C_STR(value));
}

SimpleString StringFrom (const wxRect& value) {
  char buffer [DEFAULT_SIZE];
  sprintf (buffer, "[%d, %d, %d, %d]", value.x, value.y,
      value.width, value.height);
  return SimpleString(buffer);
}

SimpleString StringFrom (const wxColour& value) {
  char buffer [DEFAULT_SIZE];
  sprintf (buffer, "[red=%d, green=%d, blue=%d, alpha=%d]", value.Red(), value.Green(),
      value.Blue(), value.Alpha());
  return SimpleString(buffer);
}

SimpleString StringFrom (const wxSize& value) {
	char buffer [DEFAULT_SIZE];
	sprintf (buffer, "[%d, %d]", value.x, value.y);
	return SimpleString(buffer);
}

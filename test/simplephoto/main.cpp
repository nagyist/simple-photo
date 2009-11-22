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

#include <stdlib.h>

#include <Magick++.h>

#include "CppUnitLite/SimpleString.h"
#include "CppUnitLite/TestHarness.h"

#include "simplephoto/core/Macros.h"

int main(int argc, char** argv) {
  wxApp app;
  wxString text(argv[0], wxConvUTF8);
  Magick::InitializeMagick(C_STR(text));
  scoped_ptr<SimpleString> regex;
  if (argc >= 2) {
	  regex.reset(new SimpleString(argv[1]));
  }
  TestResult tr;
  if (regex.get() != NULL &&
  		*(regex) == SimpleString("-l")) {
  	TestRegistry::ListAllTests();
  } else {
    TestRegistry::runAllTests(tr, regex.get());
    const int tests_succeeded = (tr.failures() == 0);
  //  if (!tests_succeeded) {
  //    system("pause");
  //  }
    return tests_succeeded ? 0 : 42;
  }
  return 0;
}

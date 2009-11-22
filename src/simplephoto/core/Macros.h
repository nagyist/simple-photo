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

#ifndef SIMPLE_PHOTO_CORE_MACROS_H
#define SIMPLE_PHOTO_CORE_MACROS_H

#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <assert.h>
#include <memory.h>

// Macros.
#define DISABLE_MAGIC_METHODS(class_name) \
    explicit class_name(class_name&); \
    class_name& operator=(const class_name&);

#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

// Using declarations.
using boost::scoped_array;
using boost::scoped_ptr;
using boost::shared_ptr;
using boost::weak_ptr;
using std::auto_ptr;

#ifdef _WINDOWS
#define C_STR(wxstring_arg) (wxstring_arg.data())
#else
#define C_STR(wxstring_arg) ((const char*) wxstring_arg.mb_str(wxConvUTF8))
#endif

#endif // SIMPLE_PHOTO_CORE_MACROS_H

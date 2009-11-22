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

/*
 * PhotoTests.cpp
 *
 *  Created on: Apr 27, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"

#include "simplephoto/core/Photo.h"

using namespace simplephoto;

TEST(PhotoTests, IsValidPhoto) {
	CHECK(Photo::IsValidPhoto(wxString(wxT("test/data/1.jpg"))));
	CHECK(Photo::IsValidPhoto(wxString(wxT("test/data/2.jpg"))));
	CHECK(Photo::IsValidPhoto(wxString(wxT("test/data/8.png"))));
	CHECK(!Photo::IsValidPhoto(wxString(wxT("does/not/exit.jpeg"))));
	CHECK(!Photo::IsValidPhoto(wxString(wxT(""))));
}

TEST(PhotoTests, DataIsInitialized) {
  wxDateTime date = wxDateTime::Now();
	Photo photo(wxT("test/data/1.jpg"));
	CHECK(photo.m_size_bytes > 0);
	CHECK(photo.m_created != date);
	CHECK(photo.m_modified != date);
	CHECK(photo.m_accessed != date);
}

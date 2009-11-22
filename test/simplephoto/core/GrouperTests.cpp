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
 * GrouperTests.cpp
 *
 *  Created on: Jun 9, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"
#include <wx/wx.h>

#include "simplephoto/core/SimpleGrouper.h"
#include "simplephoto/core/Grouper.h"
#include "simplephoto/core/Macros.h"
#include "simplephoto/core/Photo.h"
#include "simplephoto/core/PhotoGroup.h"

using namespace simplephoto;

TEST(GrouperTests, EmptyInputPhotoVector) {
	Grouper* groupers[] = {
			new SimpleGrouper(SimpleGrouper::DIR),
			new SimpleGrouper(SimpleGrouper::DAY)
	};
	int count = ARRAY_SIZE(groupers);
	for (int i = 0; i < count; ++i) {
		std::vector<Photo*> input;
		std::vector<PhotoGroup*> output;
		groupers[i]->Group(input, output);
		CHECK(output.size() == 0);
		CHECK(input.size() == 0);
		delete groupers[i];
	}
}

TEST(GrouperTests, OneInputPhotoVector) {
	Grouper* groupers[] = {
			new SimpleGrouper(SimpleGrouper::DIR),
			new SimpleGrouper(SimpleGrouper::DAY)
	};
	int count = ARRAY_SIZE(groupers);
	Photo photo;
	wxFileName path(wxT("test path"));
	photo.m_path = wxFileName(path);
	for (int i = 0; i < count; ++i) {
		std::vector<Photo*> input;
		std::vector<PhotoGroup*> output;
		input.push_back(&photo);
		groupers[i]->Group(input, output);
		CHECK(input.size() == 1);
		CHECK(output.size() == 1);
		CHECK(output[0]->m_name.Length() > 0);
		CHECK(output[0]->m_photos.size() == 1);
		CHECK(output[0]->m_photos[0]->m_path == path);
		delete output[0];
		delete groupers[i];
	}
}


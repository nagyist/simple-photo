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
 * PhotoGroupTests.cpp
 *
 *  Created on: May 12, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"

#include "simplephoto/core/Macros.h"
#include "simplephoto/core/Photo.h"
#include "simplephoto/core/PhotoGroup.h"

#include <wx/datetime.h>

using namespace simplephoto;

Photo SAMPLE[5];

class SampleData {
public:
	static const int COUNT = 5;
	Photo m_photos[COUNT];
	PhotoGroup m_group;

	SampleData() : m_group(wxT("test")) {
		for (int i = 0; i < COUNT; ++i) {
			time_t time = i;
			m_photos[i].m_created = wxDateTime(time);
			m_photos[i].m_path = wxFileName(wxString::Format(wxT("myfile%d.png"), i));
		}
		m_group.AddPhoto(&m_photos[2]);
		m_group.AddPhoto(&m_photos[1]);
		m_group.AddPhoto(&m_photos[0]);
		m_group.AddPhoto(&m_photos[4]);
		m_group.AddPhoto(&m_photos[3]);
	}

	bool IsSorted(bool asc) const {
		for (int i = 0; i < COUNT; ++i) {
			if (asc) {
				if (&m_photos[i] != m_group.m_photos[i]) {
					printf("%s != %s\n",
              C_STR(m_photos[i].m_path.GetFullName()),
              C_STR(m_group.m_photos[i]->m_path.GetFullName()));
					return false;
				}
			} else {
				if (&m_photos[COUNT - 1 - i] != m_group.m_photos[i]) {
					return false;
				}
			}
		}
		return true;
	}
};

TEST(PhotoGroupTests, IsNameSet) {
	PhotoGroup group(wxT("Rui"));
	CHECK(group.m_name == wxString(wxT("Rui")));
}

TEST(PhotoGroupTests, AddPhoto) {
	PhotoGroup group(wxT("Rui"));
	group.AddPhoto(NULL);
	CHECK(group.m_photos.size() == 1);
	CHECK(group.m_photos[0] == NULL);
}

TEST(PhotoGroupTests, TestSortByCreationDate) {
	SampleData data;
	data.m_group.SortByCreationDate(true);
	CHECK(data.IsSorted(true));
}

TEST(PhotoGroupTests, TestSortByName) {
	SampleData data;
	data.m_group.SortByName(true);
	CHECK(data.IsSorted(true));
}

TEST(PhotoGroupTests, TestSortByCreationDateDescending) {
	SampleData data;
	data.m_group.SortByCreationDate(false);
	CHECK(data.IsSorted(false));
}

TEST(PhotoGroupTests, TestSortByNameDescending) {
	SampleData data;
	data.m_group.SortByName(false);
	CHECK(data.IsSorted(false));
}

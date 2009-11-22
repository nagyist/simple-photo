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
 * SimpleGrouperTests.cpp
 *
 *  Created on: Jun 18, 2009
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

class TestData {
public:
	TestData(wxString paths[], int count);
	TestData(wxDateTime times[], int count);
	~TestData();

	std::vector<Photo*> m_in;
	std::vector<PhotoGroup*> m_out;
};

TestData::TestData(wxString paths[], int count) {
	for (int i = 0; i < count; ++i) {
		Photo* photo = new Photo;
		photo->m_path = paths[i];
		m_in.push_back(photo);
	}
	SimpleGrouper grouper(SimpleGrouper::DIR);
	grouper.Group(m_in, m_out);
}

TestData::TestData(wxDateTime times[], int count) {
	for (int i = 0; i < count; ++i) {
		Photo* photo = new Photo;
		photo->m_created = times[i];
		photo->m_modified = times[i];
		m_in.push_back(photo);
	}
	SimpleGrouper grouper(SimpleGrouper::DAY);
	grouper.Group(m_in, m_out);
}

TestData::~TestData() {
	for (unsigned int i = 0; i < m_in.size(); ++i) {
		delete m_in[i];
	}
	for (unsigned int i = 0; i < m_out.size(); ++i) {
		delete m_out[i];
	}
}

TEST(SimpleGrouperTests, TwoPhotosInSameDirectory) {
	wxString paths[] = {
			wxT("/rui/photo1.png"),
			wxT("/rui/photo2.png")
	};
	TestData d(paths, ARRAY_SIZE(paths));
	CHECK(d.m_out.size() == 1);
	CHECK(d.m_out[0]->m_photos.size() == 2);
}

TEST(SimpleGrouperTests, TwoPhotosInDifferentDirectory) {
	wxString paths[] = {
			wxT("/rui1/photo1.png"),
			wxT("/rui2/photo2.png")
	};
	TestData d(paths, ARRAY_SIZE(paths));
	CHECK(d.m_out.size() == 2);
	CHECK(d.m_out[0]->m_photos.size() == 1);
	CHECK(d.m_out[1]->m_photos.size() == 1);
}

TEST(SimpleGrouperTests, ThreePhotosTwoPlusOne) {
	wxString paths[] = {
			wxT("/rui1/photo1.png"),
			wxT("/rui1/photo2.png"),
			wxT("/rui3/photo3.png")
	};
	TestData d(paths, ARRAY_SIZE(paths));
	CHECK(d.m_out.size() == 2);
	CHECK(d.m_out[0]->m_photos.size() == 2);
	CHECK(d.m_out[1]->m_photos.size() == 1);
}

TEST(SimpleGrouperTests, PhotosInSubDirectories) {
	wxString paths[] = {
			wxT("/rui/photo1.png"),
			wxT("/rui/rui/photo2.png")
	};
	TestData d(paths, ARRAY_SIZE(paths));
	CHECK(d.m_out.size() == 2);
	CHECK(d.m_out[0]->m_photos.size() == 1);
	CHECK(d.m_out[1]->m_photos.size() == 1);
}

TEST(SimpleGrouperTests, DifferentPathsWithSameDirName) {
	wxString paths[] = {
			wxT("/rui1/rui/photo.png"),
			wxT("/rui2/rui/photo.png")
	};
	TestData d(paths, ARRAY_SIZE(paths));
	CHECK(d.m_out.size() == 2);
	CHECK(d.m_out[0]->m_photos.size() == 1);
	CHECK(d.m_out[1]->m_photos.size() == 1);
}

TEST(SimpleGrouperTests, SameDay) {
	wxDateTime times[] = {
			wxDateTime(4, wxDateTime::Jun, 1982, 12, 0),
			wxDateTime(4, wxDateTime::Jun, 1982, 13, 0),
	};
	TestData d(times, ARRAY_SIZE(times));
	CHECK(d.m_out.size() == 1);
	CHECK(d.m_out[0]->m_photos.size() == 2);
}

TEST(SimpleGrouperTests, DifferentDay) {
	wxDateTime times[] = {
			wxDateTime(3, wxDateTime::Jun, 1982, 12, 0),
			wxDateTime(4, wxDateTime::Jun, 1982, 13, 0)
	};
	TestData d(times, ARRAY_SIZE(times));
	CHECK(d.m_out.size() == 2);
	CHECK(d.m_out[0]->m_photos.size() == 1);
	CHECK(d.m_out[1]->m_photos.size() == 1);
}

TEST(SimpleGrouperTests, TwoPhotosAgainstOne) {
	wxDateTime times[] = {
			wxDateTime(3, wxDateTime::Jun, 1982, 12, 0),
			wxDateTime(4, wxDateTime::Jun, 1982, 13, 1),
			wxDateTime(4, wxDateTime::Jun, 1982, 13, 0)
	};
	TestData d(times, ARRAY_SIZE(times));
	CHECK(d.m_out.size() == 2);
	CHECK(d.m_out[0]->m_photos.size() == 1);
	CHECK(d.m_out[1]->m_photos.size() == 2);
}

TEST(SimpleGrouperTests, TestGrouperNone) {
	Photo p1;
	p1.m_path.SetFullName(wxT("rui"));
	Photo p2;
	p2.m_path.SetFullName(wxT("rui2"));
	std::vector<Photo*> in;
	in.push_back(&p1);
	in.push_back(&p2);
	SimpleGrouper grouper(SimpleGrouper::NONE);
	std::vector<PhotoGroup*> out;
	grouper.Group(in, out);
	CHECK_EQUAL(1, out.size());
	scoped_ptr<PhotoGroup> cleaner(out[0]);
	CHECK_EQUAL(2, out[0]->m_photos.size());
}


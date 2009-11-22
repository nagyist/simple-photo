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
 * ProjectTests.cpp
 *
 *  Created on: Jun 28, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"

#include "simplephoto/core/Project.h"

using namespace simplephoto;

TEST(ProjectTests, AddPhotosTest) {
	Project project;
	for (int i = 0; i < 42; ++i) {
		Photo* photo = new Photo;
		photo->m_path.SetFullName(wxString::Format(wxT("rui%d.png"), i));
		project.AddPhoto(photo);
		CHECK_EQUAL(i + 1, project.GetPhotoCount());
	}
}

TEST(ProjectTests, ContainsPhotoTest) {
	Photo* p1 = new Photo;
	Photo p2;
	p1->m_path.SetName(wxT("rui"));
	p2.m_path.SetName(wxT("rui2"));
	Project project;
	project.AddPhoto(p1);
	CHECK(project.ContainsPhoto(*p1));
	CHECK(!project.ContainsPhoto(p2));
}

TEST(ProjectTests, DefaultOutputDirNotEmpty) {
	Project project;
	CHECK(!project.GetOutputDir().IsEmpty());
}

TEST(ProjectTests, AddPhotosWithoutUpdatingGroups) {
	Project project;
	const int total_photos = 42;
	for (int i = 0; i < total_photos; ++i) {
		Photo* photo = new Photo;
		photo->m_path.SetFullName(wxString::Format(wxT("rui%d.png"), i));
		project.AddPhoto(photo);
	}
	CHECK_EQUAL(0, project.GetGroupCount());
}

TEST(ProjectTests, AddPhotosAndUpdateGroups) {
	Project project;
	const int total_photos = 42;
	for (int i = 0; i < total_photos; ++i) {
		Photo* photo = new Photo;
		photo->m_path.SetFullName(wxString::Format(wxT("rui%d.png"), i));
		project.AddPhoto(photo);
	}
	project.UpdateGroups();
	CHECK_EQUAL(1, project.GetGroupCount());
	CHECK_EQUAL(total_photos, project.GetGroup(0).m_photos.size());
}

TEST(ProjectTests, UpdatePhotoCrops) {
	Resizer resizer(Resizer::RATIO, wxSize(4, 2));
	Project project;
	project.SetResizer(resizer);
	Photo* p1 = new Photo;
	p1->m_size = wxSize(42, 42);
	project.AddPhoto(p1);
	project.UpdatePhotoCrop();
	wxRect crop = project.GetPhotoCrop(*p1);
	CHECK_EQUAL(wxRect(0, 0, 42, 21), crop);
}

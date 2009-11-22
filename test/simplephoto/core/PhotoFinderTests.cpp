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
 * PhotoFinderTests.cpp
 *
 *  Created on: May 21, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"

#include "simplephoto/core/Macros.h"
#include "simplephoto/core/Photo.h"
#include "simplephoto/core/PhotoFinder.h"
#include "simplephoto/core/PhotoGroup.h"

using namespace simplephoto;

TEST(PhotoFinderTests, FindAllPhotosInLeafDirectory) {
	PhotoFinder finder(wxFileName(wxT("test/data/PhotoFinderTests/dir2")));
	PhotoGroup group(wxT(""));
	finder.Find(group);
	CHECK(group.m_photos.size() == 2);
	group.ClearAndDeletePhotos();
}

TEST(PhotoFinderTests, FindAllPhotosInRootDirectory) {
	PhotoFinder finder(wxFileName(wxT("test/data/PhotoFinderTests/")));
	PhotoGroup group(wxT(""));
	finder.Find(group);
	CHECK(group.m_photos.size() == 8);
	group.ClearAndDeletePhotos();
}

TEST(PhotoFinderTests, FindInNonExistentDirectory) {
	PhotoFinder finder(wxFileName(wxT("I/dont/think/its/likely/this/dir/exists")));
	PhotoGroup group(wxT(""));
	finder.Find(group);
	CHECK(group.m_photos.size() == 0);
}

TEST(PhotoFinderTests, FindPhotoPath) {
	PhotoFinder finder(wxFileName(wxT("test/data/PhotoFinderTests/1.png")));
	PhotoGroup group(wxT(""));
	finder.Find(group);
	CHECK(group.m_photos.size() == 1);
	CHECK(group.m_photos[0]->m_path.GetFullName() == wxString(wxT("1.png")));
	group.ClearAndDeletePhotos();
}

TEST(PhotoFinderTests, DontFindInvalidPhoto) {
	PhotoFinder finder(wxFileName(wxT("test/data/PhotoFinderTests/not_a_photo.txt")));
	PhotoGroup group(wxT(""));
	finder.Find(group);
	CHECK(group.m_photos.size() == 0);
}

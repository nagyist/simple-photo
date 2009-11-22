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
 * BitmapCacheTests.cpp
 *
 *  Created on: Jul 19, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"

#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <cmath>

#include "simplephoto/core/Bitmap.h"
#include "simplephoto/core/BitmapCache.h"
#include "simplephoto/core/Macros.h"
#include "simplephoto/util/TempDir.h"

using namespace simplephoto;

TEST(BitmapCacheTest, TestUncachedFile) {
	Photo photo(wxT("test/data/bitmap_cache1.png"));
	BitmapCache cache(wxT("cache"), wxT("BitmapCache"));
	wxSize size(42, 42);
	scoped_ptr<Bitmap> bitmap(cache.GetBitmap(photo.m_path.GetFullPath(), size));
	CHECK(bitmap.get() != NULL);
	CHECK_EQUAL(wxSize(42, 31), bitmap->GetSize());
}

TEST(BitmapCacheTest, TestCachedFile) {
	Photo photo(wxT("test/data/bitmap_cache1.png"));
	BitmapCache cache(wxT("cache"), wxT("BitmapCache"));
	wxSize size(42, 42);
	scoped_ptr<Bitmap> bitmap(cache.GetBitmap(photo.m_path.GetFullPath(), size));
	bitmap.reset(cache.GetBitmap(photo.m_path.GetFullPath(), size));
	CHECK(bitmap.get() != NULL);
	CHECK_EQUAL(wxSize(42, 31), bitmap->GetSize());
}

TEST(BitmapCacheTest, TestClearCache) {
	Photo photo(wxT("test/data/bitmap_cache1.png"));
	BitmapCache cache(wxT("cache"), wxT("BitmapCache"));
	wxSize size(42, 42);
	scoped_ptr<Bitmap> bitmap(cache.GetBitmap(photo.m_path.GetFullPath(), size));
	wxFileName path(wxT("cache/BitmapCache/"), wxT(""));
	wxArrayString files;
  wxDir::GetAllFiles(path.GetFullPath(), &files);
	CHECK_EQUAL(1, files.Count());
	cache.Clear();
	files.Clear();
  CHECK(!path.DirExists());
}

TEST(BitmapCacheTest, TestCacheDirIsCreated) {
	wxDir dir(wxT("cache/BitmapCache/"));
	BitmapCache cache(wxT("cache"), wxT("BitmapCache"));
	CHECK(wxDir::Exists(dir.GetName()));
}

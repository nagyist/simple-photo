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
 * ResizerTests.cpp
 *
 *  Created on: Jun 28, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"

#include "simplephoto/core/Resizer.h"

using namespace simplephoto;

const wxChar TEST_SMALL_IMAGE[] = wxT("test/data/small_image.png");

TEST(ResizerTests, NeedsCropOnly) {
	Resizer resizer(Resizer::RATIO, wxSize(4, 3));
	wxSize wrong_size(500, 300);
	CHECK(resizer.NeedsCrop(wrong_size));
	CHECK(!resizer.NeedsRescale(wrong_size))
  CHECK_EQUAL(wxSize(400, 300), resizer.GetScaleSize(wrong_size));
}

TEST(ResizerTests, NeedsScaleOnly) {
	Resizer resizer(Resizer::PIXELS, wxSize(400, 300));
	wxSize wrong_size(800, 600);
	CHECK(!resizer.NeedsCrop(wrong_size));
	CHECK(resizer.NeedsRescale(wrong_size))
  CHECK_EQUAL(wxSize(400, 300), resizer.GetScaleSize(wrong_size));
}

TEST(ResizerTests, NeedsCropAndScale) {
	Resizer resizer(Resizer::PIXELS, wxSize(400, 300));
	wxSize wrong_size(900, 600);
	CHECK(resizer.NeedsCrop(wrong_size));
	CHECK(resizer.NeedsRescale(wrong_size))
  CHECK_EQUAL(wxSize(400, 300), resizer.GetScaleSize(wrong_size));
}

TEST(ResizerTests, NoCropOrScale) {
	Resizer resizer(Resizer::PIXELS, wxSize(400, 300));
	wxSize size(400, 300);
	CHECK(!resizer.NeedsCrop(size));
	CHECK(!resizer.NeedsRescale(size))
  CHECK_EQUAL(wxSize(400, 300), resizer.GetScaleSize(size));
}

TEST(ResizerTests, DefaultResizer) {
	Resizer resizer;
	wxSize size(42, 42);
	CHECK(!resizer.NeedsCrop(size));
	CHECK(!resizer.NeedsRescale(size))
  CHECK_EQUAL(size, resizer.GetScaleSize(size));
}

TEST(ResizerTests, RatioToString) {
	Resizer resizer(Resizer::RATIO, wxSize(21, 42));
	CHECK_EQUAL(wxString(wxT("21:42")), resizer.ToString());
}

TEST(ResizerTests, PixelsToString) {
	Resizer resizer(Resizer::PIXELS, wxSize(210, 420));
	CHECK_EQUAL(wxString(wxT("210x420")), resizer.ToString());
}

TEST(ResizerTests, NoneToString) {
	Resizer resizer(Resizer::NONE, wxSize(21, 42));
	CHECK_EQUAL(wxString(wxT("None")), resizer.ToString());
}

TEST(ResizerTests, CropSizeIsAlwaysRelativeToTheOriginalImage) {
    Resizer resizer(Resizer::PIXELS, wxSize(42, 42));
    CHECK_EQUAL(wxSize(84, 84), resizer.GetCropSize(wxSize(84, 168)));
    CHECK_EQUAL(wxSize(1, 1), resizer.GetCropSize(wxSize(1, 21)));
}

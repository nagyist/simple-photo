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
 * ImageTest.cpp
 *
 *  Created on: Apr 30, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"

#include <wx/wx.h>
#include <wx/filename.h>
#include <cmath>

#include "simplephoto/core/Bitmap.h"
#include "simplephoto/util/TempDir.h"

using namespace simplephoto;

TEST(BitmapTests, DealsGracefullyWithCorruptedPng) {
	Bitmap* bitmap = NULL;
	CHECK(NULL == (bitmap = Bitmap::Read(wxString(wxT("test/data/corrupted.png")))));
	delete bitmap;
}

TEST(BitmapTests, CanReadJpeg) {
	Bitmap* bitmap = NULL;
	CHECK(NULL != (bitmap = Bitmap::Read(wxString(wxT("test/data/1.jpg")))));
	delete bitmap;
}

TEST(BitmapTests, CanReadPng) {
	Bitmap* bitmap = NULL;
	CHECK(NULL != (bitmap = Bitmap::Read(wxString(wxT("test/data/8.png")))));
	delete bitmap;
}

TEST(BitmapTests, CanReadGif) {
	Bitmap* bitmap = NULL;
	CHECK(NULL != (bitmap = Bitmap::Read(wxString(wxT("test/data/9.gif")))));
	delete bitmap;
}

TEST(BitmapTests, CanReadTiff) {
	Bitmap* bitmap = NULL;
	CHECK(NULL != (bitmap = Bitmap::Read(wxString(wxT("test/data/10.tiff")))));
	delete bitmap;
}

TEST(BitmapTests, CanReadBmp) {
	Bitmap* bitmap = NULL;
	CHECK(NULL != (bitmap = Bitmap::Read(wxString(wxT("test/data/11.bmp")))));
	delete bitmap;
}

TEST(BitmapTests, CorrectBitmapSize) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/8.png"))));
	CHECK(NULL != bitmap.get());
	const wxSize size = bitmap->GetSize();
	const wxSize real_size(1000, 800);
	CHECK(size.GetWidth() == real_size.GetWidth());
	CHECK(size.GetHeight() == real_size.GetHeight());
}

TEST(BitmapTests, CanCreateWxBitmap) {
	scoped_ptr<Bitmap> src(Bitmap::Read(wxString(wxT("test/data/8.png"))));
	CHECK(src.get() != NULL);
	scoped_ptr<wxBitmap> wx(src->CreateWxBitmap());
	CHECK(wx.get() != NULL);
}

TEST(BitmapTests, CorrectWxBitmapSize) {
	scoped_ptr<Bitmap> src(Bitmap::Read(wxString(wxT("test/data/8.png"))));
	CHECK(src.get() != NULL);
	scoped_ptr<wxBitmap> wx(src->CreateWxBitmap());
	CHECK(wx.get() != NULL);
	const wxSize src_size = src->GetSize();
	CHECK(src_size.GetWidth() == wx->GetWidth());
	CHECK(src_size.GetHeight() == wx->GetHeight());
}

TEST(BitmapTests, ScaleToCorrectSize) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/8.png"))));
	CHECK(bitmap.get() != NULL);
	wxSize size = bitmap->GetSize();
	const wxSize real_size(1000, 800);
	CHECK_EQUAL(size, real_size);
	const wxSize new_size(42, 42);
	bitmap->Scale(new_size);
	size = bitmap->GetSize();
	CHECK_EQUAL(size, new_size);
}

TEST(BitmapTests, TestGradientImage1) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient1.png"))));
	wxSize size(320, 180);
	wxRect rect = bitmap->GetLargestGradient(wxSize(16, 9));
	CHECK(rect.x == 0);
	CHECK(rect.y == 0);
	CHECK(rect.width == size.x);
	CHECK(rect.height == size.y);
}

TEST(BitmapTests, TestGradientImage2) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient2.png"))));
	wxSize size(320, 180);
	wxRect rect = bitmap->GetLargestGradient(wxSize(16, 9));
	CHECK(rect.x == 0);
	CHECK(rect.y == bitmap->GetSize().y - size.y);
	CHECK(rect.width == size.x);
	CHECK(rect.height == size.y);
}


TEST(BitmapTests, TestGradientImage3) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient3.png"))));
	wxSize size(320, 180);
	wxRect rect = bitmap->GetLargestGradient(wxSize(16, 9));
	CHECK(rect.x == 0);
	CHECK(rect.y == 42);
	CHECK(rect.width == size.x);
	CHECK(rect.height == size.y);
}


TEST(BitmapTests, TestGradientImage4) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient4.png"))));
	wxSize size(180, 320);
	wxRect rect = bitmap->GetLargestGradient(wxSize(9, 16));
	CHECK(rect.x == 0);
	CHECK(rect.y == 0);
	CHECK(rect.width == size.x);
	CHECK(rect.height == size.y);
}

TEST(BitmapTests, TestGradientImage5) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient5.png"))));
	wxSize size(180, 320);
	wxRect rect = bitmap->GetLargestGradient(wxSize(9, 16));
	CHECK(rect.x == bitmap->GetSize().x - size.x);
	CHECK(rect.y == 0);
	CHECK(rect.width == size.x);
	CHECK(rect.height == size.y);
}


TEST(BitmapTests, TestGradientImage6) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient6.png"))));
	wxSize size(180, 320);
	wxRect rect = bitmap->GetLargestGradient(wxSize(9, 16));
	CHECK(rect.x == 42);
	CHECK(rect.y == 0);
	CHECK(rect.width == size.x);
	CHECK(rect.height == size.y);
}

TEST(BitmapTests, TestCropSmallerRectangle) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient5.png"))));
	wxRect crop(21, 42, 63, 84);
	bitmap->Crop(crop);
	CHECK_EQUAL(crop.width, bitmap->GetSize().x);
	CHECK_EQUAL(crop.height, bitmap->GetSize().y);
}

TEST(BitmapTests, TestCropLargerRectangle) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient5.png"))));
	wxRect crop(-10, -10, 1000, 1000);
	wxSize original = bitmap->GetSize();
	bitmap->Crop(crop);
	CHECK(bitmap->GetSize() == original);
}

TEST(BitmapTests, TestCropNoRectIntersection) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient5.png"))));
	wxSize original = bitmap->GetSize();
	wxRect crop(500, 500, 42, 42);
	bitmap->Crop(crop);
	CHECK_EQUAL(original, bitmap->GetSize());
}

TEST(BitmapTests, ScaleToSmaller) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient5.png"))));
	wxSize scale(42, 42);
	bitmap->Scale(scale);
	CHECK_EQUAL(scale, bitmap->GetSize());
}

TEST(BitmapTests, ScaleToBigger) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient5.png"))));
	wxSize scale(300, 400);
	bitmap->Scale(scale);
	CHECK_EQUAL(scale, bitmap->GetSize());
}

TEST(BitmapTests, ScaleToZero) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient5.png"))));
	wxSize original = bitmap->GetSize();
	wxSize scale(0, 0);
	bitmap->Scale(scale);
	CHECK(bitmap->GetSize() == original);
}

TEST(BitmapTests, ScaleToNegative) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient5.png"))));
	wxSize scale(-42, -42);
	wxSize original = bitmap->GetSize();
	bitmap->Scale(scale);
	CHECK_EQUAL(original, bitmap->GetSize());
}


TEST(BitmapTests, WritePng) {
	scoped_ptr<Bitmap> bitmap(Bitmap::Read(wxString(wxT("test/data/gradient5.png"))));
	TempDir dir;
	wxFileName out(wxT("rui2.png"));
  out.SetPath(dir.GetPath().GetFullPath());
	CHECK(bitmap->Write(out.GetFullPath()));
	CHECK(out.FileExists());
}

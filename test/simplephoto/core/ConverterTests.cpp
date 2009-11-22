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
 * ConverterTests.cpp
 *
 *  Created on: Jun 22, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"

#include <wx/wx.h>
#include <wx/file.h>

#include "simplephoto/core/Bitmap.h"
#include "simplephoto/core/Converter.h"
#include "simplephoto/core/Photo.h"
#include "simplephoto/core/Project.h"
#include "simplephoto/util/TempDir.h"

using namespace simplephoto;

const wxChar TEST_JPEG[] = wxT("test/data/1.jpg");
const wxChar TEST_PNG[] = wxT("test/data/6.png");
const wxChar TEST_SQUARE[] = wxT("test/data/top_left_square.png");

namespace {
class TestListener : public ConverterListener {
public:
  TestListener() {
  }

  virtual void OnConvertSuccess(const Photo& original, const Photo& destination) {
    m_originals.push_back(original);
    m_destinations.push_back(destination);
  }

  virtual void OnConvertFail(const Photo& original) {
  }

  std::vector<Photo> m_originals;
  std::vector<Photo> m_destinations;
};

class Setup {
public:
  Setup() {
    m_project.SetOutputDir(m_temp_dir.GetPath().GetFullPath());
    m_converter.reset(new Converter(m_project, m_listener));
  }

  TempDir m_temp_dir;
  TestListener m_listener;
  Project m_project;
  boost::scoped_ptr<Converter> m_converter;
};
}  // namespace

TEST(ConverterTests, AllFilesAreConverted) {
  Setup s;
  s.m_project.AddPhoto(new Photo(TEST_PNG));
  s.m_project.UpdateGroups();
  s.m_converter->Convert();
  CHECK_EQUAL(1, s.m_listener.m_originals.size());
  CHECK_EQUAL(1, s.m_listener.m_destinations.size());
  wxFileName test_png(TEST_PNG);
  test_png.MakeAbsolute();
  CHECK_EQUAL(test_png.GetFullPath(),
              s.m_listener.m_originals[0].m_path.GetFullPath());
}

TEST(ConverterTests, OutputFileIsWritten) {
  Setup s;
  s.m_project.AddPhoto(new Photo(TEST_PNG));
  s.m_project.UpdateGroups();
  s.m_converter->Convert();
  CHECK_EQUAL(1, s.m_listener.m_destinations.size());
  CHECK(wxFile::Exists(s.m_listener.m_destinations[0].m_path.GetFullPath()));
}

TEST(ConverterTests, OutputFileIsCorrectSize) {
  Setup s;
  s.m_project.SetResizer(Resizer(Resizer::RATIO, wxSize(1, 2)));
  s.m_project.AddPhoto(new Photo(TEST_PNG));
  s.m_project.UpdateGroups();
  s.m_converter->Convert();
  CHECK_EQUAL(1, s.m_listener.m_destinations.size());
  CHECK(wxFile::Exists(s.m_listener.m_destinations[0].m_path.GetFullPath()));
  CHECK_EQUAL(wxSize(400, 800), s.m_listener.m_destinations[0].m_size);
}

TEST(ConverterTests, OutputToVeryDeepUnexistentDir) {
  Setup s;
  wxFileName output_path = s.m_temp_dir.GetPath();
  output_path.AppendDir(wxT("this"));
  output_path.AppendDir(wxT("should"));
  output_path.AppendDir(wxT("not"));
  output_path.AppendDir(wxT("exist"));
  s.m_project.SetOutputDir(output_path.GetFullPath());
  s.m_project.SetResizer(Resizer(Resizer::RATIO, wxSize(1, 2)));
  s.m_project.AddPhoto(new Photo(TEST_PNG));
  s.m_project.UpdateGroups();
  s.m_converter->Convert();
  CHECK(output_path.DirExists());
}

TEST(ConverterTests, CropIsRanBeforeScale) {
  Setup s;
  s.m_project.SetResizer(Resizer(Resizer::PIXELS, wxSize(42, 21)));
  s.m_project.AddPhoto(new Photo(TEST_SQUARE));
  s.m_project.UpdateGroups();
  s.m_converter->Convert();
  CHECK_EQUAL(1, s.m_listener.m_destinations.size());
  CHECK(wxFile::Exists(s.m_listener.m_destinations[0].m_path.GetFullPath()));
  CHECK_EQUAL(wxSize(42, 21), s.m_listener.m_destinations[0].m_size);
  boost::scoped_ptr<Bitmap> bitmap(Bitmap::Read(s.m_listener.m_destinations[0].m_path.GetFullPath()));
  CHECK(bitmap.get() != NULL);
  CHECK_EQUAL(wxColour(255, 0, 0, 255), bitmap->GetPixel(0, 0));
  CHECK_EQUAL(wxColour(255, 0, 0, 255), bitmap->GetPixel(0, bitmap->GetSize().y - 1));
  CHECK_EQUAL(wxColour(0, 255, 0, 255), bitmap->GetPixel(bitmap->GetSize().x - 1, 0));
}

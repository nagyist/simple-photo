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
 * FsUtilTests.cpp
 *
 *  Created on: Jul 25, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"

#include <wx/wx.h>
#include <wx/file.h>
#include <wx/filename.h>

#include "simplephoto/core/FsUtil.h"
#include "simplephoto/core/Log.h"
#include "simplephoto/core/Macros.h"

using namespace simplephoto;

namespace {
void CreateDir(const wxString& path) {
	wxFileName::Mkdir(path);
}

void CreateFile(const wxString& path) {
	wxFile file;
  file.Create(path);
}
}  // namespace

TEST(FsUtilTests, NonExistentDir) {
	CHECK(!FsUtil::RmDir(wxT("FsUtilTestsTempNonExistentDir")));
}

TEST(FsUtilTest, EmptyDir) {
	wxString path(wxT("FsUtilTestsDir2"));
	CreateDir(path);
	CHECK(FsUtil::RmDir(path));
}

TEST(FsUtilTest, DirWithFiles) {
	CreateDir(wxT("FsUtilTestsDir3"));
	CreateFile(wxT("FsUtilTestsDir3/file1.txt"));
	CreateFile(wxT("FsUtilTestsDir3/file2.png"));
	CreateFile(wxT("FsUtilTestsDir3/file3.jpg"));
	CHECK(FsUtil::RmDir(wxT("FsUtilTestsDir3")));
}

TEST(FsUtilTest, DirWidthDirs) {
	CreateDir(wxT("FsUtilTestsDir"));
	CreateFile(wxT("FsUtilTestsDir/file1.txt"));
	CreateFile(wxT("FsUtilTestsDir/file2.png"));
	CreateFile(wxT("FsUtilTestsDir/file3.jpg"));
	CreateDir(wxT("FsUtilTestsDir/Deeper"));
	CreateFile(wxT("FsUtilTestsDir/Deeper/file1.jpg"));
	CreateFile(wxT("FsUtilTestsDir/Deeper/file2.jpg"));
	CHECK(FsUtil::RmDir(wxT("FsUtilTestsDir")));
}

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
 * TextUtilTests.cpp
 *
 *  Created on: Sep 27, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"

#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <cmath>

#include "simplephoto/core/Log.h"
#include "simplephoto/core/TextUtil.h"

using namespace simplephoto;

TEST(TextUtilTests, TestZeroSeconds) {
  CHECK_EQUAL(wxString(wxT("00s")), TextUtil::SecondsToString(0));
}

TEST(TextUtilTests, Test42Seconds) {
  CHECK_EQUAL(wxString(wxT("42s")), TextUtil::SecondsToString(42));
}

TEST(TextUtilTests, TestMoreThanOneMinute) {
  CHECK_EQUAL(wxString(wxT("01m42s")), TextUtil::SecondsToString(102));
}

TEST(TextUtilTests, TestMoreThanOneHour) {
  CHECK_EQUAL(wxString(wxT("02h00m42s")), TextUtil::SecondsToString(42 + 2 * 60 * 60));
}

TEST(TextUtilTests, TestMoreThanOneDay) {
  CHECK_EQUAL(wxString(wxT("2d00h00m42s")), TextUtil::SecondsToString(42 + 2 * 24 * 60 * 60));
}

TEST(TextUtilTests, TestBytes) {
  CHECK_EQUAL(wxString(wxT("42.0 Bytes")), TextUtil::BytesToString(42));
}

TEST(TextUtilTests, TestKiloBytes) {
  CHECK_EQUAL(wxString(wxT("42.0 KB")), TextUtil::BytesToString(42 * 1024));
}

TEST(TextUtilTests, TestMegaBytes) {
  CHECK_EQUAL(wxString(wxT("42.0 MB")), TextUtil::BytesToString(42 * 1024 * 1024));
}

TEST(TextUtilTests, TestGigaBytes) {
  CHECK_EQUAL(wxString(wxT("1.0 GB")), TextUtil::BytesToString(42 + 1024 * 1024 * 1024));
}

TEST(TextUtilTests, TestDecimalBytes) {
  CHECK_EQUAL(wxString(wxT("4.1 KB")), TextUtil::BytesToString(4200));
}

TEST(TextUtilTests, TestNegativeBytes) {
  CHECK_EQUAL(wxString(wxT("-420.0 Bytes")), TextUtil::BytesToString(-420));
}

TEST(TextUtilTests, CheckHashIsCaseSensitive) {
  CHECK(TextUtil::Hash(wxT("viva")) != TextUtil::Hash(wxT("Viva")));
}

TEST(TextUtilTests, CheckHashIsAlwaysTheSameForSameString) {
  CHECK_EQUAL(TextUtil::Hash(wxT("viva")), TextUtil::Hash(wxT("viva")));
}

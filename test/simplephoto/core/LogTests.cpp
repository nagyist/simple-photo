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
 * LogTests.cpp
 *
 *  Created on: Jul 15, 2009
 *      Author: ruibm
 */

#include "CppUnitLite/TestHarness.h"

#include "simplephoto/core/Log.h"

using namespace simplephoto;

class LogOutput : public Log::Out {
public:
	virtual ~LogOutput() {}
	virtual void Write(const wxString& text) {
		m_text = text;
	}

	wxString m_text;
};

class ChangeOut {
public:
	ChangeOut() {
		Log::d.SetOut(&m_out);
	}

	~ChangeOut() {
		Log::d.SetOut(&Log::std_out);
	}

	LogOutput m_out;
};

TEST(LogTests, TestWxString) {
	ChangeOut change;
	LogOutput& o = change.m_out;
	Log::d.SetOut(&o);
	Log::d << wxString(wxT("Hello!!!")) << Log::ENDL;
	CHECK_EQUAL(wxT("Hello!!!\n"), o.m_text);
}

TEST(LogTests, TestComposite) {
	ChangeOut change;
	LogOutput& o = change.m_out;
	Log::d.SetOut(&o);
	Log::d << wxString(wxT("Hello ")) << 2.1f << " World " << 42 << Log::ENDL;
	CHECK_EQUAL(wxT("Hello 2 World 42\n"), o.m_text);
}

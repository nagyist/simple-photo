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
 * Log.cpp
 *
 *  Created on: Jul 15, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/Log.h"

#include <iostream>

#include <wx/filename.h>

#include "simplephoto/core/Macros.h"

namespace {
class ScopedLock {
public:
	explicit ScopedLock(wxMutex& mutex) : m_mutex(mutex) {
		m_mutex.Lock();
	}

	~ScopedLock() {
		m_mutex.Unlock();
	}

private:
	wxMutex& m_mutex;
};

bool has_been_initialized = false;
}  // namespace

namespace simplephoto {

Log Log::d;
Log::Out Log::std_out;
const Log::Type Log::ENDL;

Log::Log() : m_out(NULL) {
	m_out = &std_out;
}

Log::~Log() {
}

void Log::SetOut(Out* out) {
	if (!has_been_initialized) {
		new (&Log::d) Log;
		has_been_initialized = true;
	}
	m_out = out;
}

Log& Log::operator<<(const wxString& message) {
	Append(message);
	return *this;
}

Log& Log::operator<<(const int& message) {
	Append(wxString::Format(wxT("%d"), message));
	return *this;
}

Log& Log::operator<<(const char* message) {
	Append(wxString(message, wxConvUTF8));
	return *this;
}

Log& Log::operator<<(const wxWindow* message) {
	(*this) << reinterpret_cast<const long long>(message);
	return *this;
}

Log& Log::operator<<(const wxFileName& message) {
	return (*this) << message.GetFullPath();
}

Log& Log::operator<<(const wxPoint& message) {
	return (*this) << wxString::Format(wxT("[%d, %d]"), message.x, message.y);
}

Log& Log::operator<<(const wxRect& message) {
	return (*this) << wxString::Format(wxT("[%d, %d, %d, %d]"), message.x, message.y, message.width, message.height);
}

Log& Log::operator<<(const Type&) {
	Append(wxT("\n"));
  if (m_out != NULL) {
		m_out->Write(text());
	}
	text().Empty();
	return *this;
}

void Log::Append(const wxString& to_append) {
	if (!has_been_initialized) {
		new (&Log::d) Log;
		has_been_initialized = true;
	}
	text().Append(to_append);
}

void Log::Out::Write(const wxString& message) {
  std::cerr << C_STR(message);
}

wxString& Log::text() {
	int thread_id = wxThread::GetCurrentId();
	ScopedLock lock(m_mutex);
	if (m_text.find(thread_id) == m_text.end()) {
		m_text[thread_id] = wxString();
	}
	return m_text[thread_id];
}

}

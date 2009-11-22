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
 * Photo.cpp
 *
 *  Created on: Apr 27, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/Photo.h"

#include <wx/filename.h>

#include "simplephoto/core/Macros.h"

namespace {
const wxSize SIZE_NOT_SET(-1, -1);
}  // namespace

namespace simplephoto {

Photo::Photo()
		: m_size_bytes(-1),
      m_size(SIZE_NOT_SET) {
  Init();
}

Photo::Photo(const wxString& path)
		:	m_path(path),
			m_size(-1, -1) {
  Init();
	wxFileName filename(m_path);
	if (!filename.MakeAbsolute()) {
		assert(!"Problem making filename absolute.");
	}
	m_path = filename.GetFullPath();
	LoadData();
}

Photo::~Photo() {
}

void Photo::LoadData() {
	wxFileName filename(m_path);
	filename.GetTimes(&m_accessed, &m_modified, &m_created);
	m_size_bytes = filename.GetSize().GetLo();
	// In case we are truncating the file size.
	assert(filename.GetSize().GetHi() == 0);
}

bool Photo::IsValidPhoto(const wxString& path) {
	wxFileName filename(path);
	if (!filename.FileExists()) {
		return false;
	}
	wxString extension = filename.GetExt();
	extension.LowerCase();
	const wxString extensions[] = {
			wxString(wxT("jpg")),
			wxString(wxT("jpeg")),
			wxString(wxT("png")),
			wxString(wxT("gif")),
			wxString(wxT("tiff")),
	};
	const int size = ARRAY_SIZE(extensions);
	for (int i = 0; i < size; ++i) {
		if (extensions[i] == extension) {
			return true;
		}
	}
	return false;
}

bool Photo::IsSizeSet() const {
  return m_size != SIZE_NOT_SET;
}

bool Photo::operator==(const Photo& photo) const {
	return m_path == photo.m_path;
}

bool Photo::operator!=(const Photo& photo) const {
	return m_path != photo.m_path;
}

void Photo::Init() {  
  m_created = wxDateTime::Now();
  m_accessed = wxDateTime::Now();
  m_modified = wxDateTime::Now();
}

}


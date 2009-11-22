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
 * PhotoFinder.cpp
 *
 *  Created on: May 21, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/PhotoFinder.h"

#include "simplephoto/core/Photo.h"
#include "simplephoto/core/PhotoGroup.h"

namespace simplephoto {

PhotoFinder::PhotoFinder(const wxFileName& path)
    : m_root(path),
			m_group(NULL),
      m_listener(NULL),
      m_cancel(false) {
}

PhotoFinder::~PhotoFinder() {
}

void PhotoFinder::Find(PhotoGroup& group) {
	assert(m_group == NULL);
	m_current_dir = wxT("");
	if (m_root.FileExists()) {
		Photo* photo = new Photo(m_root.GetFullPath());
		if (Photo::IsValidPhoto(m_root.GetFullPath())) {
			if (m_listener != NULL) {
				m_listener->OnPhotoFound(*photo);
			}
			group.AddPhoto(photo);
		}
	} else if (m_root.DirExists()) {
		wxDir dir(m_root.GetFullPath());
		m_group = &group;
		dir.Traverse(*this);
		m_group = NULL;
	}
}

wxDirTraverseResult PhotoFinder::OnDir(const wxString& dir) {
	if (dir != m_current_dir) {
		m_current_dir = dir;
		if (m_listener != NULL) {
			m_listener->OnDirChange(m_current_dir);
		}
	}
  return m_cancel ? wxDIR_STOP : wxDIR_CONTINUE;
}

wxDirTraverseResult PhotoFinder::OnFile(const wxString& path) {
	if (Photo::IsValidPhoto(path)) {
		Photo* photo = new Photo(path);
		if (m_listener != NULL) {
			m_listener->OnPhotoFound(*photo);
		}
		m_group->AddPhoto(photo);
  }
  return m_cancel ? wxDIR_STOP : wxDIR_CONTINUE;
}

wxDirTraverseResult PhotoFinder::OnOpenError(const wxString&) {
  return m_cancel ? wxDIR_STOP : wxDIR_IGNORE;
}

}

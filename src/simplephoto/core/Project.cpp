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
 * Project.cpp
 *
 *  Created on: Jun 27, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/Project.h"

#include <wx/wx.h>
#include <wx/stdpaths.h>

#include "simplephoto/core/Log.h"
#include "simplephoto/core/SimpleGrouper.h"

namespace simplephoto {

Project::Project()
    : m_grouper(new SimpleGrouper(SimpleGrouper::NONE)),
      m_format(PNG) {
	// TODO(ruibm): Should be the Desktop path.
	m_output_dir = GetDefaultOutputDir();  
}

Project::~Project() {
	DeletePhotos();
}

wxString Project::GetOutputDir() const {
	return m_output_dir;
}

void Project::SetOutputDir(const wxString& output_dir) {
  wxFileName abs(output_dir);
  abs.MakeAbsolute();
  m_output_dir = abs.GetFullPath();
}

const Resizer& Project::GetResizer() const {
	return m_resizer;
}

void Project::SetResizer(const Resizer& resizer) {
	m_resizer = resizer;
}

Extension Project::GetFormat() const {
	return m_format;
}

void Project::SetFormat(Extension format) {
	m_format = format;
}

Grouper& Project::GetGrouper() const {
	return *(m_grouper.get());
}

void Project::SetGrouper(Grouper* grouper) {
	assert(grouper != NULL);
	m_grouper.reset(grouper);
}

int Project::GetGroupCount() const {
	return m_groups.size();
}

const PhotoGroup& Project::GetGroup(int index) const {
	assert(index < static_cast<int>(m_groups.size()));
	return *m_groups[index];
}

bool Project::HasPhotoCrop(const Photo& photo) const {
  wxString path = photo.m_path.GetFullPath();
  return m_crops.find(path) != m_crops.end();
}

wxRect Project::GetPhotoCrop(const Photo& photo) const {
  wxString path = photo.m_path.GetFullPath();
  if (HasPhotoCrop(photo)) {
    Project* self = const_cast<Project*>(this);
    return self->m_crops[path];
	} else {
    return wxRect(-1, -1, -1, -1);
	}
}

void Project::SetPhotoCrop(const Photo& photo, const wxRect& crop) {
  m_crops[photo.m_path.GetFullPath()] = crop;
}

bool Project::AddPhoto(Photo* photo) {
	if (!ContainsPhoto(*photo)) {
		m_photos.push_back(photo);
    m_photos_map[photo->m_path.GetFullPath()] = true;
		return true;
	}
	return false;
}

bool Project::ContainsPhoto(const Photo& photo) const {
  return m_photos_map.find(photo.m_path.GetFullPath()) != m_photos_map.end();
}

int Project::GetPhotoCount() const {
	return m_photos.size();
}

void Project::UpdateGroups() {
	DeleteGroups();
	m_grouper->Group(m_photos, m_groups);
}

void Project::DeleteGroups() {
	for (unsigned int i = 0; i < m_groups.size(); ++i) {
		delete m_groups[i];
		m_groups[i] = NULL;
	}
	m_groups.clear();
}

void Project::DeletePhotos() {
	DeleteGroups();
	for (unsigned int i = 0; i < m_photos.size(); ++i) {
		delete m_photos[i];
		m_photos[i] = NULL;
	}
	m_photos.clear();
  m_photos_map.clear();
}

wxString Project::GetDefaultOutputDir() {
  wxFileName dir(wxStandardPaths::Get().GetDocumentsDir(), wxEmptyString);
  bool is_abs = dir.MakeAbsolute();
  assert(is_abs);
  return dir.GetFullPath();
}

void Project::UpdatePhotoCrop() {
	m_crops.clear();
	for (unsigned int i = 0; i < m_photos.size(); ++i) {
		Photo& photo = *m_photos[i];
		if (m_resizer.NeedsCrop(photo.m_size)) {
      wxSize size = m_resizer.GetCropSize(photo.m_size);
			SetPhotoCrop(photo, wxRect(0, 0, size.x, size.y));
		}
	}
}

}  // namespace simplephoto

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
 * SimpleGrouper.cpp
 *
 *  Created on: Jun 9, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/SimpleGrouper.h"

#include <map>
#include <set>
#include <wx/wx.h>
#include <wx/filename.h>

#include "simplephoto/core/Photo.h"
#include "simplephoto/core/PhotoGroup.h"

namespace {

using simplephoto::SimpleGrouper;

wxString PathToString(simplephoto::Photo& photo) {
	const wxArrayString& dirs = photo.m_path.GetDirs();
	if (dirs.Count() > 0) {
		return dirs[dirs.Count() - 1];
	} else {
		return wxT("root");
	}
}

wxString DayToString(simplephoto::Photo& photo) {
	return photo.m_created.Format(wxT("%Y-%m-%d"));
}

wxString GetId(SimpleGrouper::Type type, simplephoto::Photo& photo) {
	switch (type) {
		case SimpleGrouper::DIR:
			return photo.m_path.GetPath();

		case SimpleGrouper::DAY:
			return DayToString(photo);

		default:
			assert(!"Unknown enum value.");
			return wxString();
	}
}

wxString GetName(SimpleGrouper::Type type, simplephoto::Photo& photo) {
	switch (type) {
		case SimpleGrouper::DIR:
			return PathToString(photo);

		case SimpleGrouper::DAY:
			return DayToString(photo);

		default:
			assert(!"Unknown enum value.");
			return wxString();
	}
}

}  // namespace

namespace simplephoto {


SimpleGrouper::SimpleGrouper(Type type)
		: m_type(type) {
}

void SimpleGrouper::Group(std::vector<Photo*>& in, std::vector<PhotoGroup*>& out) {
	assert(out.size() == 0);
	if (m_type == NONE) {
		PhotoGroup* group = new PhotoGroup(wxT("All Photos"));
		for (unsigned int i = 0; i < in.size(); ++i) {
			group->AddPhoto(in[i]);
		}
		out.push_back(group);
		return;
	}

	// <path/day, PhotoGroup>
	std::map<wxString, PhotoGroup*> groups;
	// <group_name, PhotoGroup>
	std::set<wxString> group_names;
	for (unsigned int i = 0; i < in.size(); ++i) {
		assert(in[i] != NULL);
		Photo& photo = *(in[i]);
		wxString path = GetId(m_type, photo);
		if (groups.find(path) == groups.end()) {
			wxString name = GetName(m_type, photo);
			wxString group_name= name;
			int i = 0;
			while (group_names.find(group_name) != group_names.end()) {
				++i;
				group_name = name;
				group_name << i;
			}
			PhotoGroup* group = new PhotoGroup(group_name);
			groups[path] = group;
			out.push_back(group);
			group_names.insert(group_name);
		}
		groups[path]->AddPhoto(&photo);
	}
}

Grouper* SimpleGrouper::Clone() const {
  Grouper* grouper = new SimpleGrouper(m_type);
  return grouper;
}

}

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
 * PhotoGroup.cpp
 *
 *  Created on: May 11, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/PhotoGroup.h"

#include "simplephoto/core/Photo.h"

#include <algorithm>

namespace simplephoto {

namespace {
class Comparator {
public:
	enum Field {
		NAME,
		CREATION_DATE
	};

	Comparator(Field field, bool asc) : m_field(field), m_asc(asc) {
	}

	bool operator()(const Photo* p1, const Photo* p2) {
		bool ret = false;
		switch (m_field) {
		case NAME:
			ret = (p1->m_path.GetFullName().CompareTo(
					p2->m_path.GetFullName()) <= 0);
			break;
		case CREATION_DATE:
			ret = (p1->m_created <= p2->m_created);
			break;
		}
		if (!m_asc) {
			ret = !ret;
		}
		return ret;
	}
private:
	Field m_field;
	bool m_asc;
};
}

PhotoGroup::PhotoGroup(const wxString& name) : m_name(name) {
}

PhotoGroup::~PhotoGroup() {
}

void PhotoGroup::AddPhoto(Photo* photo) {
	m_photos.push_back(photo);
}

void PhotoGroup::SortByCreationDate(bool ascending) {
	std::sort(m_photos.begin(), m_photos.end(),
			Comparator(Comparator::CREATION_DATE, ascending));
}

void PhotoGroup::SortByName(bool ascending) {
	std::sort(m_photos.begin(), m_photos.end(),
			Comparator(Comparator::NAME, ascending));
}

void PhotoGroup::ClearAndDeletePhotos() {
	for (unsigned int i = 0; i < m_photos.size(); ++i) {
		delete m_photos[i];
	}
	m_photos.clear();
}

void PhotoGroup::Clear() {
	m_photos.clear();
}


}

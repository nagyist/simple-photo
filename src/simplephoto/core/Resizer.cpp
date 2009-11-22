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
 * Resizer.cpp
 *
 *  Created on: Jun 28, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/Resizer.h"

namespace simplephoto {

namespace {

wxSize ToRatio(const wxSize& ratio, const wxSize& size) {
	return wxSize(
			size.y * ratio.x / ratio.y,
			size.x * ratio.y / ratio.x);
}

int GetRatioDifference(const wxSize& s1, const wxSize& s2) {
	return s1.x * s2.y - s2.x * s1.y;
}

bool IsSameRatio(const wxSize& s1, const wxSize& s2) {
	return 0 == GetRatioDifference(s1, s2);
}

}  // namespace

Resizer::Resizer()
		: m_type(NONE),
			m_size(-1, -1) {
}

Resizer::Resizer(Type type, const wxSize& size)
		: m_type(type),
			m_size(size) {
}

Resizer::~Resizer() {
}

bool Resizer::NeedsCrop(const wxSize& size) const {
	return !m_type == NONE &&
			!IsSameRatio(size, m_size);
}

bool Resizer::NeedsRescale(const wxSize& size) const {
	if (m_type == RATIO) {
		return false;
	}
  return size != GetScaleSize(size);
}

wxSize Resizer::GetCropSize(const wxSize& size) const {
    int rdiff = GetRatioDifference(m_size, size);
    if (rdiff == 0) {
      return size;
    } else if (rdiff < 0) {
      return wxSize(ToRatio(m_size, size).x, size.y);
    } else {
      return wxSize(size.x, ToRatio(m_size, size).y);
    }
}

wxSize Resizer::GetScaleSize(const wxSize& size) const {
	if (m_type == RATIO) {
    return GetCropSize(size);
	} else if (m_type == PIXELS) {
		return m_size;
	} else if (m_type == NONE) {
		return size;
	}
	assert(!"Invalid Resizer::Type.");
	return wxSize(-1, -1);
}

wxString Resizer:: ToString() const {
	switch (m_type) {
		case NONE:
			return wxString(wxT("None"));

		case PIXELS:
			return wxString::Format(wxT("%dx%d"), m_size.x, m_size.y);

		case RATIO:
			return wxString::Format(wxT("%d:%d"), m_size.x, m_size.y);

		default:
			assert(!"Invalid Resizer::Type.");
			return wxString(wxT("Invalid Resizer::Type"));
	}
}

}

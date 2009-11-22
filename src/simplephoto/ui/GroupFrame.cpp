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
 * GroupFrame.cpp
 *
 *  Created on: Aug 1, 2009
 *      Author: ruibm
 */

#include "simplephoto/ui/GroupFrame.h"

#include <cmath>

#include "simplephoto/core/BitmapCache.h"
#include "simplephoto/core/Log.h"
#include "simplephoto/core/Photo.h"
#include "simplephoto/core/PhotoGroup.h"
#include "simplephoto/ui/PhotoFrame.h"

namespace {
const int MARGIN = 10;
const int DOUBLE_MARGIN = 2 * MARGIN;
const int PADDING = 10;
const int DOUBLE_PADDING = 2 * PADDING;
const int TITLE_HEIGHT = 20;
const wxColour TITLE_COLOUR(255, 255, 50);
const wxBrush BACKGROUND_BRUSH(wxColour(150, 150, 255));
const wxPen BACKGROUND_PEN(wxColour(0, 0, 0));
const float ROUNDNESS = 5.0f;
}  // namespace

namespace simplephoto {

GroupFrame::GroupFrame(SmartCache& cache)
    : m_padding(PADDING),
      m_cache(cache) {
}

GroupFrame::~GroupFrame() {
	Clear();
}

void GroupFrame::Clear() {
	while (m_photos.size() > 0) {
		delete m_photos.back();
		m_photos.pop_back();
	}
}

void GroupFrame::SetWidth(int width) {
  m_width = width;
  const int photos_per_row = GetPhotosPerRow();
  if (photos_per_row == 0) {
    m_padding = 0;
  } else {
    m_padding = (m_width - DOUBLE_MARGIN - photos_per_row * PhotoFrame::GetSize().x) /
                (photos_per_row + 1);
  }
}

void GroupFrame::Draw(wxDC& dc, wxPoint& offset, wxRect& screen) {
  if (m_photos.size() == 0) {
    return;
  }

  wxPoint p(
      offset.x + m_position.x + MARGIN,
      offset.y + m_position.y + MARGIN);

  // Draw the background.
  dc.SetBrush(BACKGROUND_BRUSH);
  dc.SetPen(BACKGROUND_PEN);  
  dc.DrawRoundedRectangle(p, wxSize(m_width - DOUBLE_MARGIN,
                                    GetHeight() - DOUBLE_MARGIN), ROUNDNESS);

  // Draw the title.
  p.x += PADDING;
  p.y += PADDING;
	dc.SetTextForeground(TITLE_COLOUR);
	dc.DrawText(m_title, p);

  // Draw the photos in the group.  
  p.x = MARGIN + m_padding;
	p.y += TITLE_HEIGHT + PADDING;
	const wxSize increments(
      m_padding + PhotoFrame::GetSize().x,
      DOUBLE_PADDING + PhotoFrame::GetSize().y);
  for (unsigned int i = 0; i < m_photos.size(); ++i) {
    if (screen.Intersects(wxRect(p, PhotoFrame::GetSize()))) {
      m_photos[i]->Draw(dc, p);
    }
		p.x += increments.x;
		if (p.x + increments.x > m_width) {
      p.x = MARGIN + m_padding;
			p.y += increments.y;
		}
	}
}

void GroupFrame::SetGroup(const PhotoGroup& group) {
	unsigned int index = 0;
	m_title = group.m_name;
	while (index < group.m_photos.size()) {
		PhotoFrame& frame = GetPhotoFrame(index);
    frame.SetPhoto(*group.m_photos[index]);
		++index;
	}
	while (m_photos.size() > group.m_photos.size()) {
		delete m_photos.back();
		m_photos.pop_back();
	}
}

int GroupFrame::GetPhotosPerRow() const {
  if (m_photos.size() == 0) {
    return 0;
  }
  const int size_per_photo = PhotoFrame::GetSize().x + DOUBLE_PADDING;
  return std::max(1, ((m_width - DOUBLE_MARGIN - DOUBLE_PADDING) / size_per_photo));
}

int GroupFrame::GetHeight() const {
  const int photos_per_row = GetPhotosPerRow();
  if (photos_per_row == 0) {
    return 0;
  }
  const int rows = ceil(static_cast<float>(m_photos.size()) / photos_per_row);
  return rows * (PhotoFrame::GetSize().y + DOUBLE_PADDING) +
      DOUBLE_PADDING + DOUBLE_MARGIN + TITLE_HEIGHT ;
}

PhotoFrame& GroupFrame::GetPhotoFrame(unsigned int index) {
	while (index >= m_photos.size()) {
    m_photos.push_back(new PhotoFrame(m_cache));
	}
	return *m_photos[index];
}

}

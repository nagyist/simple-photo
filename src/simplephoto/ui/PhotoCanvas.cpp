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
 * PhotoCanvas.cpp
 *
 *  Created on: Jul 26, 2009
 *      Author: ruibm
 */

#include "simplephoto/ui/PhotoCanvas.h"

#include "simplephoto/core/Log.h"
#include "simplephoto/core/PhotoGroup.h"
#include "simplephoto/core/Project.h"
#include "simplephoto/ui/GroupFrame.h"

BEGIN_EVENT_TABLE(simplephoto::PhotoCanvas, wxWindow)
  EVT_PAINT(simplephoto::PhotoCanvas::OnPaint)
  EVT_ERASE_BACKGROUND(simplephoto::PhotoCanvas::OnEraseBackground)
  EVT_MOUSE_EVENTS(simplephoto::PhotoCanvas::OnMouseEvent)
END_EVENT_TABLE()

namespace {
const wxColour BACKGROUND_COLOUR(192, 213, 255);
}  // namespace

namespace simplephoto {

PhotoCanvas::PhotoCanvas(wxWindow* parent, wxScrollBar& scroll)
		: wxWindow(parent, -1),
			m_y_offset(0),
      m_scroll(scroll) {
	m_scroll.SetScrollbar(0, 1, 2, 1, true);
}

PhotoCanvas::~PhotoCanvas() {
}

void PhotoCanvas::OnPaint(wxPaintEvent& event) {
	wxPaintDC dc(this);
  dc.SetPen(*wxTRANSPARENT_PEN);
  dc.SetBrush(wxBrush(BACKGROUND_COLOUR));
	dc.DrawRectangle(wxPoint(), GetSize());

  wxRect screen(wxPoint(), GetSize());
  wxPoint offset(0, -m_y_offset);
	for (unsigned int i = 0; i < m_groups.size(); ++i) {
    m_groups[i]->Draw(dc, offset, screen);
	}

  // dc.SetBrush(wxBrush(*wxRED));
  // dc.DrawCircle(m_mouse, 21);
}

void PhotoCanvas::OnEraseBackground(wxEraseEvent& event) {
}

void PhotoCanvas::OnScroll(wxScrollEvent& event) {
//	Log::d << "OnScroll: " << event.GetPosition() << Log::ENDL;
	m_y_offset = event.GetPosition();
	Refresh();
}

void PhotoCanvas::OnMouseEvent(wxMouseEvent& event) {
  // Log::d << "Mouse event " << event.GetEventType() << Log::ENDL;
	if (event.Moving()) {
		m_mouse = event.GetPosition();
    // Refresh();
	} else if (event.GetWheelRotation() != 0) {
//		Log::d << "Moving from: " << m_scroll.GetThumbSize() << " by: " << event.GetWheelRotation() << Log::ENDL;
		m_scroll.SetThumbPosition(m_scroll.GetThumbPosition() - event.GetWheelRotation());
		m_y_offset = m_scroll.GetThumbPosition();
    Refresh();
	}
}

void PhotoCanvas::ProjectChanged(Project& project) {  
	const unsigned int group_count = project.GetGroupCount();
	unsigned int index = 0;
	while (index < group_count) {
		GroupFrame& frame = GetGroupFrame(index);
    frame.SetGroup(project.GetGroup(index));
		++index;
	}
	while (index < m_groups.size()) {
		GetGroupFrame(index).Clear();
		++index;
	}
	LayoutGroups();
}

GroupFrame& PhotoCanvas::GetGroupFrame(unsigned int index) {
	while (m_groups.size() <= index) {
    assert(m_cache != NULL);
    m_groups.push_back(new GroupFrame(*m_cache));
	}
	return *m_groups[index];
}

void PhotoCanvas::LayoutGroups() {
	wxPoint p(0, 0);
	for (unsigned int i = 0; i < m_groups.size(); ++i) {
		m_groups[i]->SetWidth(GetSize().x);
		m_groups[i]->SetPosition(p);
		p.y += m_groups[i]->GetHeight();
	}
	const int height = GetSize().y;
	m_y_offset = 0;
	m_scroll.SetScrollbar(m_y_offset, height, p.y, height * 8 / 10, true);
	Refresh();
}

}

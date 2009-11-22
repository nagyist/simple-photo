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
 * PhotoWidget.cpp
 *
 *  Created on: Oct 1, 2009
 *      Author: ruibm
 */

#include "simplephoto/ui/PhotoWidget.h"

#include <wx/dc.h>
#include <wx/dcclient.h>

BEGIN_EVENT_TABLE(simplephoto::PhotoWidget, wxWindow)
  EVT_PAINT(simplephoto::PhotoWidget::OnPaint)
  EVT_ERASE_BACKGROUND(simplephoto::PhotoWidget::OnEraseBackground)
END_EVENT_TABLE()

namespace simplephoto {

PhotoWidget::PhotoWidget(wxWindow* parent)
    : wxWindow(parent, -1, wxPoint(0, 0), PhotoFrame::GetSize()) {
  assert(parent != NULL);
}

void PhotoWidget::OnPaint(wxPaintEvent& event) {
  wxPaintDC dc(this);
  wxPoint point;
  if (m_frame.get() != NULL) {
    m_frame->Draw(dc, point);
  }
}

void PhotoWidget::OnEraseBackground(wxEraseEvent& event) {
}

void PhotoWidget::Init(SmartCache& cache) {
  m_frame.reset(new PhotoFrame(cache));
}

}  // simplephoto

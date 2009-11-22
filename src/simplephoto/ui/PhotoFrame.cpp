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
 * PhotoFrame.cpp
 *
 *  Created on: Jul 26, 2009
 *      Author: ruibm
 */

#include "simplephoto/ui/PhotoFrame.h"

#include "simplephoto/core/BitmapCache.h"
#include "simplephoto/core/Log.h"
#include "simplephoto/core/Photo.h"

namespace {
const wxBrush BACKGROUND_BRUSH(wxColour(200, 200, 255));
const wxPen BACKGROUND_PEN(*wxBLACK);
const float CORNER_RADIUS = 10.0f;
const wxSize SMALL_BITMAP_SIZE(100, 100);
const wxSize SMALL_SIZE(120, 120);
} // namespace

namespace simplephoto {


PhotoFrame::PhotoFrame(SmartCache& cache)
    : m_cache(cache) {
}

PhotoFrame::~PhotoFrame() {
}

const wxSize& PhotoFrame::GetSize() {
  return SMALL_SIZE;
}

const wxSize& PhotoFrame::GetBitmapSize() {
  return SMALL_BITMAP_SIZE;
}

void PhotoFrame::Draw(wxDC& dc, wxPoint& origin) {
	dc.SetBrush(BACKGROUND_BRUSH);
	dc.SetPen(BACKGROUND_PEN);
  dc.DrawRoundedRectangle(origin, SMALL_SIZE, CORNER_RADIUS);
  wxRect rect(
      origin.x + (SMALL_SIZE.x - SMALL_BITMAP_SIZE.x) / 2,
      origin.y + (SMALL_SIZE.y - SMALL_BITMAP_SIZE.y) / 2,
      SMALL_BITMAP_SIZE.x,
      SMALL_BITMAP_SIZE.y);
  if (!m_path.IsEmpty()) {
    wxBitmap* bitmap = m_cache.Get(m_path);
    if (bitmap != NULL) {
      rect.SetSize(wxSize(bitmap->GetWidth(), bitmap->GetHeight()));
      rect.x += (SMALL_BITMAP_SIZE.x - rect.width) / 2;
      rect.y += (SMALL_BITMAP_SIZE.y - rect.height) / 2;
      dc.DrawBitmap(*bitmap, rect.GetPosition());
    }
  }
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  dc.DrawRectangle(rect.x, rect.y, rect.width, rect.height);
}

void PhotoFrame::SetPhoto(const Photo& photo) {  
  m_path = photo.m_path.GetFullPath();
}

}

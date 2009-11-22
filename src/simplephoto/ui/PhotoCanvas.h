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
 * PhotoCanvas.h
 *
 *  Created on: Jul 26, 2009
 *      Author: ruibm
 */

#ifndef PHOTOCANVAS_H_
#define PHOTOCANVAS_H_

#include <wx/wx.h>

#include <vector>

#include "simplephoto/core/SmartCache.h"

namespace simplephoto {

class GroupFrame;
class Project;

class PhotoCanvas : public wxWindow {
public:
	explicit PhotoCanvas(wxWindow* parent, wxScrollBar& scroll);
	virtual ~PhotoCanvas();

	void ProjectChanged(Project& project);
  void SetCache(SmartCache& cache) { m_cache = &cache; }
	virtual void OnScroll(wxScrollEvent& event);
	void LayoutGroups();

	DECLARE_EVENT_TABLE();

private:
	virtual void OnPaint(wxPaintEvent& event);
	virtual void OnEraseBackground(wxEraseEvent& event);
	virtual void OnMouseEvent(wxMouseEvent& event);

	GroupFrame& GetGroupFrame(unsigned int index);

	wxPoint m_mouse;
  SmartCache* m_cache;
	int m_y_offset;
	std::vector<GroupFrame*> m_groups;
  wxScrollBar& m_scroll;
};

}

#endif /* PHOTOCANVAS_H_ */

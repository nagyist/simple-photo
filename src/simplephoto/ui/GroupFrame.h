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
 * GroupFrame.h
 *
 *  Created on: Aug 1, 2009
 *      Author: ruibm
 */

#ifndef GROUPFRAME_H_
#define GROUPFRAME_H_

#include <wx/wx.h>

#include "simplephoto/core/SmartCache.h"
#include "simplephoto/core/Macros.h"

#include <vector>

namespace simplephoto {

class BitmapCache;
class PhotoFrame;
class PhotoGroup;

class GroupFrame {
public:
  explicit GroupFrame(SmartCache& cache);
	virtual ~GroupFrame();

  void Draw(wxDC& dc, wxPoint& offset, wxRect& screen);
  void SetGroup(const PhotoGroup& group);
	void Clear();
  void SetWidth(int width);
	int GetHeight() const;
	void SetPosition(const wxPoint& position ) { m_position = position; }

private:
	PhotoFrame& GetPhotoFrame(unsigned int index);
  int GetPhotosPerRow() const;

	std::vector<PhotoFrame*> m_photos;
	wxString m_title;
	int m_width;
  int m_padding;
  wxPoint m_position;
  SmartCache& m_cache;
};

}

#endif /* GROUPFRAME_H_ */

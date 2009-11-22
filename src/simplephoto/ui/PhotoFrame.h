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
 * PhotoFrame.h
 *
 *  Created on: Jul 26, 2009
 *      Author: ruibm
 */

#ifndef PHOTOFRAME_H_
#define PHOTOFRAME_H_

#include <wx/wx.h>

#include "simplephoto/core/Macros.h"
#include "simplephoto/core/SmartCache.h"

namespace simplephoto {

class Photo;

class PhotoFrame {
public:
  explicit PhotoFrame(SmartCache& cache);
	virtual ~PhotoFrame();

  static const wxSize& GetSize();
  static const wxSize& GetBitmapSize() ;
	void Draw(wxDC& dc, wxPoint& origin);
  void SetPhoto(const Photo& photo);
  void ClearPhoto() { m_path = wxEmptyString; }
  void SetPosition(const wxPoint& point) { m_position = point; }
  const wxString& GetPath() const { return m_path; }

private:
	wxString m_path;
  wxPoint m_position;
  SmartCache& m_cache;
  
  DISABLE_MAGIC_METHODS(PhotoFrame);
};

}

#endif /* PHOTOFRAME_H_ */

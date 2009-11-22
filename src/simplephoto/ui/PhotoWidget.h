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
 * PhotoWidget.h
 *
 *  Created on: Oct 1, 2009
 *      Author: ruibm
 */

#ifndef PHOTOWIDGET_H
#define PHOTOWIDGET_H

#include <wx/wx.h>

#include "simplephoto/ui/PhotoFrame.h"

namespace simplephoto {

class PhotoWidget : public wxWindow {
public:
  PhotoWidget(wxWindow* parent);

  void Init(SmartCache& cache);
  PhotoFrame& GetFrame() { return *m_frame.get(); }

  DECLARE_EVENT_TABLE();

private:
  virtual void OnPaint(wxPaintEvent& event);
  virtual void OnEraseBackground(wxEraseEvent& event);

  boost::scoped_ptr<PhotoFrame> m_frame;
};

}  // simplephoto

#endif // PHOTOWIDGET_H

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
 * DragAndDropTarget.h
 *
 *  Created on: Oct 10, 2009
 *      Author: ruibm
 */

#ifndef DRAGANDDROPTARGET_H
#define DRAGANDDROPTARGET_H

#include <wx/dnd.h>

#include "simplephoto/ui/uilistener.h"

namespace simplephoto {

class DragAndDropTarget : public wxFileDropTarget {
public:
  explicit DragAndDropTarget(UiListener& listener);

private:
  virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames);

  UiListener& m_listener;
};

}  // namespace simplephoto

#endif // DRAGANDDROPTARGET_H

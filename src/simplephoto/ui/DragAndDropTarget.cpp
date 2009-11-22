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
 * DragAndDropTarget.cpp
 *
 *  Created on: Oct 10, 2009
 *      Author: ruibm
 */

#include "simplephoto/ui/DragAndDropTarget.h"

namespace simplephoto {

DragAndDropTarget::DragAndDropTarget(UiListener& listener)
    : m_listener(listener) {
}

bool DragAndDropTarget::OnDropFiles(wxCoord x, wxCoord y,
                                    const wxArrayString& filenames) {
  m_listener.OnAddPhoto(filenames);
  return true;
}

}  // namespace simplephoto

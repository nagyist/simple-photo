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
 * RunDialog.h
 *
 *  Created on: Aug 6, 2009
 *      Author: ruibm
 */

#ifndef RUNDIALOG_H_
#define RUNDIALOG_H_

#include <wx/wx.h>

#include "simplephoto/ui/UiResources.h"

namespace simplephoto {

class BitmapCache;
class Photo;
class UiListener;

class RunDialog : public RunDialogUi {
public:
  explicit RunDialog(wxWindow* parent, SmartCache& cache);
	virtual ~RunDialog();

  void SetUiListener(UiListener* listener) {
    m_listener = listener;
  }

  void SetOriginal(const Photo& photo);
  void SetDestination(const Photo& photo);
  void SetStats(float photos_per_sec, int space_delta_bytes,
                int elapsed_time_ms, int estimated_time_ms);
  void SetProgress(int converted_photos, int total_photos);  
  void Reset(int total_photos);

  virtual void OnClose(wxCloseEvent& event);
  virtual void OnCancel(wxCommandEvent& event);

private:
  void CloseOrCancel();

  UiListener* m_listener;
  bool m_is_done;
};

}

#endif /* RUNDIALOG_H_ */

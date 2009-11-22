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
 * CrawlerDialog.h
 *
 *  Created on: Aug 6, 2009
 *      Author: ruibm
 */

#ifndef CRAWLERDIALOG_H_
#define CRAWLERDIALOG_H_

#include <wx/wx.h>

#include "simplephoto/ui/UiListener.h"
#include "simplephoto/ui/UiResources.h"

namespace simplephoto {

class BitmapCache;
class Photo;

class CrawlerDialog : public CrawlerDialogUi {
public:
  explicit CrawlerDialog(wxWindow* parent, SmartCache& cache);
	virtual ~CrawlerDialog();

  void Reset();
	void SetListener(UiListener* listener) { m_listener = listener; }
  void SetDir(const wxString& dir);
  void SetPhoto(const Photo& photo);
  void SetTotalPhotos(int total_photos);

protected:
	virtual void OnCancel(wxCommandEvent& event);
  virtual void OnClose(wxCloseEvent& event);

private:
  UiListener* m_listener;
  wxStopWatch m_stop_watch;
};

}

#endif /* CRAWLERDIALOG_H_ */

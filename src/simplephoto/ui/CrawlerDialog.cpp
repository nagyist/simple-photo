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
 * CrawlerDialog.cpp
 *
 *  Created on: Aug 6, 2009
 *      Author: ruibm
 */

#include "simplephoto/ui/CrawlerDialog.h"

#include "simplephoto/core/Bitmap.h"
#include "simplephoto/core/BitmapCache.h"
#include "simplephoto/core/Photo.h"
#include "simplephoto/core/TextUtil.h"

namespace simplephoto {
CrawlerDialog::CrawlerDialog(wxWindow* parent, SmartCache& cache)
		: CrawlerDialogUi(parent),
      m_listener(NULL) {
  m_bitmap->Init(cache);
}

CrawlerDialog::~CrawlerDialog() {
}

void CrawlerDialog::OnClose(wxCloseEvent& event) {
  m_listener->OnCancelAddPhoto();
	event.Veto();
}

void CrawlerDialog::OnCancel(wxCommandEvent& event) {
  m_listener->OnCancelAddPhoto();
}

void CrawlerDialog::SetTotalPhotos(int total_photos) {
  m_photos_found->SetLabel(wxString::Format(wxT("Photos: %d"), total_photos));
}

void CrawlerDialog::SetDir(const wxString& dir) {
  m_current_search_dir->SetLabel(wxString::Format(wxT("Dir: %s"), dir.c_str()));
}

void CrawlerDialog::SetPhoto(const Photo& photo) {
  m_elapsed_time->SetLabel(wxString::Format(wxT("Elapsed Time: %d secs"), m_stop_watch.Time() / 1000));
  m_bitmap->GetFrame().SetPhoto(photo);
  m_bitmap->Refresh();
  m_path->SetLabel(wxString::Format(wxT("Photo: %s"), photo.m_path.GetFullName().c_str()));
  m_file_size->SetLabel(wxString::Format(wxT("Size: %s"),
                                         TextUtil::BytesToString(photo.m_size_bytes).c_str()));
  m_resolution->SetLabel(wxString::Format(wxT("Resolution: %dx%d pixels"),
                         photo.m_size.x, photo.m_size.y));
}

void CrawlerDialog::Reset() {  
  m_bitmap->GetFrame().ClearPhoto();
  m_progress->Pulse();
  SetTotalPhotos(0);
  m_path->SetLabel(wxT("Photo:"));
  m_file_size->SetLabel(wxT("Size:"));
  m_resolution->SetLabel(wxT("Resolution:"));
  m_current_search_dir->SetLabel(wxT("Dir:"));
}

}

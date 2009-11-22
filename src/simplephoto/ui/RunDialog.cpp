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
 * RunDialog.cpp
 *
 *  Created on: Aug 6, 2009
 *      Author: ruibm
 */

#include "simplephoto/ui/RunDialog.h"

#include "simplephoto/core/BitmapCache.h"
#include "simplephoto/core/Photo.h"
#include "simplephoto/core/TextUtil.h"
#include "simplephoto/ui/UiListener.h"

#include <wx/stattext.h>

namespace {
void SetPhotoName(wxStaticText& text, const wxString& name) {
  text.SetLabel(wxString::Format(wxT("File: %s"), name.c_str()));
}

void SetPhotoResolution(wxStaticText& text, const wxSize& resolution) {
  text.SetLabel(
      wxString::Format(wxT("Resolution: %dx%d pixels"), resolution.x, resolution.y));
}
}  // namespace

namespace simplephoto {

RunDialog::RunDialog(wxWindow* parent, SmartCache& cache)
    : RunDialogUi(parent),
      m_listener(NULL),
      m_is_done(false) {  
  m_bitmap->Init(cache);
}

RunDialog::~RunDialog() {
}

void RunDialog::CloseOrCancel() {  
  if (!m_is_done) {
    m_listener->OnCancelRun();
  }
  EndModal(0);
}

void RunDialog::OnClose(wxCloseEvent& event) {
  event.Veto();
  CloseOrCancel();
}

void RunDialog::OnCancel(wxCommandEvent& event) {
  CloseOrCancel();
}

void RunDialog::SetOriginal(const Photo& photo) {
  SetPhotoName(*m_from_path, photo.m_path.GetFullName());
  SetPhotoResolution(*m_from_resolution, photo.m_size);
  m_bitmap->GetFrame().SetPhoto(photo);
  m_bitmap->Refresh();
}

void RunDialog::SetDestination(const Photo& photo) {
  SetPhotoName(*m_to_path, photo.m_path.GetFullName());
  SetPhotoResolution(*m_to_resolution, photo.m_size);
}

void RunDialog::SetStats(float photos_per_sec, int space_delta_bytes,
                         int elapsed_time_ms, int estimated_time_ms) {    
  m_photos_per_sec->SetLabel(
      wxString::Format(wxT("Photos per sec: %.3f"), photos_per_sec));  
  m_space_delta->SetLabel(
      wxString::Format(wxT("Space delta: %s"),
                       TextUtil::BytesToString(space_delta_bytes).c_str()));
  m_elapsed_time->SetLabel(
      wxString::Format(wxT("Elapsed time: %s"),
                       TextUtil::SecondsToString(elapsed_time_ms / 1000).c_str()));
  m_estimated_time->SetLabel(
      wxString::Format(wxT("Estimated time: %s"),
                       TextUtil::SecondsToString(estimated_time_ms / 1000).c_str()));
}

void RunDialog::SetProgress(int converted_photos, int total_photos) {  
  m_photo_count->SetLabel(
      wxString::Format(wxT("%d/%d photos"), converted_photos, total_photos));
  m_progress->SetRange(total_photos);
  m_progress->SetValue(converted_photos);
  if (converted_photos == total_photos) {
    m_cancel->SetLabel(wxT("Done"));
    m_is_done = true;
  }
}

void RunDialog::Reset(int total_photos) {  
  m_bitmap->GetFrame().ClearPhoto();
  SetPhotoName(*m_from_path, wxEmptyString);
  SetPhotoResolution(*m_from_resolution, wxSize());
  SetPhotoName(*m_to_path, wxEmptyString);
  SetPhotoResolution(*m_to_resolution, wxSize());
  m_photos_per_sec->SetLabel(
      wxString::Format(wxT("Photos per sec: %.3f"), 0.0));
  m_space_delta->SetLabel(
      wxString::Format(wxT("Space delta: %s"), TextUtil::BytesToString(0).c_str()));
  m_elapsed_time->SetLabel(
      wxString::Format(wxT("Elapsed time: %s"), TextUtil::SecondsToString(0).c_str()));
  m_estimated_time->SetLabel(
      wxString::Format(wxT("Estimated time: %s"), TextUtil::SecondsToString(0).c_str()));
  m_photo_count->SetLabel(
      wxString::Format(wxT("%d/%d photos"), 0, total_photos));
  m_progress->SetRange(total_photos);
  m_progress->SetValue(0);
  m_is_done = false;
  m_cancel->SetLabel(wxString(wxT("Cancel")));
}

}

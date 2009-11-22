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
 * FrameUiController.cpp
 *
 *  Created on: Jul 19, 2009
 *      Author: ruibm
 */

#include "simplephoto/ui/FrameUiController.h"

#include "simplephoto/core/Project.h"
#include "simplephoto/ui/CrawlerDialog.h"
#include "simplephoto/ui/Frame.h"
#include "simplephoto/ui/PhotoCanvas.h"

#include <wx/button.h>
#include <wx/wx.h>

namespace {
template<typename T>
void ShowDialog(scoped_ptr<T>& dialog, bool show) {
}
}  // namespace

namespace simplephoto {

FrameUiController::FrameUiController(Frame& frame)
		: m_listener(NULL),
			m_frame(frame) {
}

FrameUiController::~FrameUiController() {
}

void FrameUiController::SetListener(UiListener* listener) {
	m_listener = listener;
	m_frame.GetCrawlerDialog().SetListener(listener);
}

UiListener* FrameUiController::GetListener() {
	assert(m_listener != NULL);
	return m_listener;
}

void FrameUiController::SetSizes(const wxArrayString& sizes, unsigned int default_index) {
	wxComboBox& box = m_frame.GetResizer();
	box.Clear();
	box.Append(sizes);
	box.SetSelection(default_index);
}

void FrameUiController::SetExtensions(const wxArrayString& extensions, unsigned int default_index) {
	wxComboBox& box = m_frame.GetExtension();
	box.Clear();
	box.Append(extensions);
	box.SetSelection(default_index);
}

void FrameUiController::SetGroupers(const wxArrayString& groups, unsigned int default_index) {
	wxComboBox& box = m_frame.GetGrouper();
	box.Clear();
	box.Append(groups);
	box.SetSelection(default_index);
}

void FrameUiController::Update(Project& project) {
  m_frame.GetOutputDir().SetPath(project.GetOutputDir());
	m_frame.GetPhotoCanvas().ProjectChanged(project);
  m_frame.Update();
}

void FrameUiController::SetCache(SmartCache& cache) {
  m_frame.GetPhotoCanvas().SetCache(cache);
}

CrawlerDialog& FrameUiController::GetCrawlerDialog() {
	return m_frame.GetCrawlerDialog();
}

RunDialog& FrameUiController::GetRunDialog() {
	return m_frame.GetRunDialog();
}

void FrameUiController::SetRunEnabled(bool enabled) {
  wxButton& button = m_frame.GetRunButton();
  button.Enable(enabled);
}

}

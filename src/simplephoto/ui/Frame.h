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
 * Frame.h
 *
 *  Created on: Jul 10, 2009
 *      Author: ruibm
 */

#ifndef FRAME_H_
#define FRAME_H_

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/filepicker.h>

#include "simplephoto/core/Macros.h"
#include "simplephoto/ui/DragAndDropTarget.h"
#include "simplephoto/ui/UiController.h"

namespace simplephoto {

class CrawlerDialog;
class DebugFrame;
class PhotoCanvas;
class RunDialog;

class Frame : public wxFrame {
public:
  explicit Frame(const wxString& app_name);
	virtual ~Frame();

  void OnInit(SmartCache& cache);
	void OnDestroy();
	UiController* GetUiController();
	wxComboBox& GetResizer() { return *m_resizer; }
	wxComboBox& GetGrouper() { return *m_grouper; }
	wxComboBox& GetExtension() { return *m_file_extension; }
  PhotoCanvas& GetPhotoCanvas() { return *m_canvas; }
	CrawlerDialog& GetCrawlerDialog() { return *m_crawler_dialog; }
	RunDialog& GetRunDialog() { return *m_run_dialog; }
  wxButton& GetRunButton() { return *m_run_button; }
  wxDirPickerCtrl& GetOutputDir() { return *m_output_dir; }

	virtual void OnSize(wxSizeEvent& event);
	virtual void OnCommand(wxCommandEvent& event);
	virtual void OnOutputDirChanged(wxFileDirPickerEvent& event);
  virtual void OnScroll(wxScrollEvent& event);

protected:
	DECLARE_EVENT_TABLE();

private:
	void AddToolbarTopLine(wxWindow* parent);
	void AddToolbarBottomLine(wxWindow* parent);
	void AddToolbarLeftPart(wxWindow* parent);
	void AddToolbarRightPart(wxWindow* parent);
	void ShowDebugPanel();
	void CreateMenu();
	void InitAccelerators();
  void ReadClipboard();

	wxScrollBar* m_scroll;
	PhotoCanvas* m_canvas;
	wxPanel* m_toolbar;
	wxComboBox* m_file_extension;
	wxComboBox* m_grouper;
	wxComboBox* m_resizer;
	wxDirPickerCtrl* m_output_dir;
	RunDialog* m_run_dialog;
	CrawlerDialog* m_crawler_dialog;
  wxButton* m_run_button;
  boost::scoped_ptr<DebugFrame> m_debug;
  boost::scoped_ptr<UiController> m_controller;
};

}

#endif /* FRAME_H_ */

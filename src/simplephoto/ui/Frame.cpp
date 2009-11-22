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
 * Frame.cpp
 *
 *  Created on: Jul 10, 2009
 *      Author: ruibm
 */

#include "simplephoto/ui/Frame.h"

#include "simplephoto/core/Log.h"
#include "simplephoto/ui/CrawlerDialog.h"
#include "simplephoto/ui/DebugFrame.h"
#include "simplephoto/ui/FrameUiController.h"
#include "simplephoto/ui/PhotoCanvas.h"
#include "simplephoto/ui/RunDialog.h"
#include "simplephoto/ui/UiResources.h"

#include <wx/clipbrd.h>
#include <wx/dataobj.h>
#include <wx/gdicmn.h>
#include <wx/stdpaths.h>
#include <algorithm>

namespace simplephoto {
enum FrameEventId {
	ID_DEBUG = 42,
	ID_ADD_PHOTO_FILES,
	ID_ADD_PHOTO_DIR,
	ID_REMOVE_PHOTO,
	ID_RUN,
	ID_SIZE_SELECTED,
	ID_GROUP_SELECTED,
	ID_EXTENSION_SELECTED,
	ID_OUTPUT_DIR_CHANGED,
  ID_SCROLL_BAR,
  ID_NEW_PROJECT,
  ID_TOGGLE_DEBUG
};
}  // simplephoto

BEGIN_EVENT_TABLE(simplephoto::Frame, wxFrame)
  EVT_SIZE(simplephoto::Frame::OnSize)
  EVT_MENU(wxID_ABOUT, simplephoto::Frame::OnCommand)
  EVT_MENU(wxID_CLOSE, simplephoto::Frame::OnCommand)
  EVT_MENU(wxID_PASTE, simplephoto::Frame::OnCommand)
  EVT_MENU(ID_NEW_PROJECT, simplephoto::Frame::OnCommand)
  EVT_MENU(ID_DEBUG, simplephoto::Frame::OnCommand)
  EVT_MENU(ID_TOGGLE_DEBUG, simplephoto::Frame::OnCommand)
  EVT_BUTTON(ID_ADD_PHOTO_FILES, simplephoto::Frame::OnCommand)
  EVT_BUTTON(ID_ADD_PHOTO_DIR, simplephoto::Frame::OnCommand)
  EVT_BUTTON(ID_REMOVE_PHOTO, simplephoto::Frame::OnCommand)
  EVT_BUTTON(ID_RUN, simplephoto::Frame::OnCommand)
  EVT_COMBOBOX(ID_SIZE_SELECTED, simplephoto::Frame::OnCommand)
  EVT_COMBOBOX(ID_GROUP_SELECTED, simplephoto::Frame::OnCommand)
  EVT_COMBOBOX(ID_EXTENSION_SELECTED, simplephoto::Frame::OnCommand)
  EVT_DIRPICKER_CHANGED(ID_OUTPUT_DIR_CHANGED, simplephoto::Frame::OnOutputDirChanged)
  EVT_COMMAND_SCROLL(ID_SCROLL_BAR, simplephoto::Frame::OnScroll)
END_EVENT_TABLE()

namespace {
const wxSize DEFAULT_SIZE(800, 600);
const int TOOLBAR_HEIGHT = 75;
const wxColour LEFT_TOOLBAR_COLOUR(255, 250, 111);
const wxColour RIGHT_TOOLBAR_COLOUR(136, 255, 130);

wxComboBox* GetComboBox(wxWindow* parent, const wxString& text, int id) {
	assert(parent != NULL);

	wxStaticText* label = new wxStaticText(parent, -1, text);
	parent->GetSizer()->Add(label, 0, wxFIXED_MINSIZE | wxALIGN_CENTER_VERTICAL, 2);

	wxComboBox* combo_box = new wxComboBox(parent, id);
	combo_box->SetEditable(false);
	combo_box->Append(wxT("PNG"));
	combo_box->Append(wxT("JPG"));
	combo_box->Append(wxT("Rui"));
  combo_box->SetSelection(0);
	parent->GetSizer()->Add(combo_box, 1, wxALIGN_CENTER | wxALL, 2);
	return combo_box;
}

}  // namespace

namespace simplephoto {

Frame::Frame(const wxString& app_name)
		: wxFrame(NULL, -1, app_name),
      m_run_dialog(NULL),
      m_run_button(NULL) {
}

Frame::~Frame() {
}

void Frame::OnInit(SmartCache& cache) {

	// Canvas
	m_scroll = new wxScrollBar(this, ID_SCROLL_BAR, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL);
  m_canvas = new PhotoCanvas(this, *m_scroll);

	// Toolbar
	m_toolbar = new wxPanel(this);
	wxBoxSizer* toolbar_sizer = new wxBoxSizer(wxHORIZONTAL);
	m_toolbar->SetSizer(toolbar_sizer, true);

	AddToolbarLeftPart(m_toolbar);

	wxPanel* toolbar_middle = new wxPanel(m_toolbar, -1);
  m_toolbar->GetSizer()->Add(toolbar_middle, 5, wxALIGN_CENTER | wxEXPAND | wxALL, 1);
	toolbar_middle->SetSizer(new wxBoxSizer(wxVERTICAL));
	AddToolbarTopLine(toolbar_middle);
	AddToolbarBottomLine(toolbar_middle);
  // toolbar_middle->SetBackgroundColour(LEFT_TOOLBAR_COLOUR);

	AddToolbarRightPart(m_toolbar);

	CreateMenu();
	InitAccelerators();

	// General
	SetSize(DEFAULT_SIZE);
	Center(wxHORIZONTAL);
	SetPosition(wxPoint(100, 20));

	m_controller.reset(new FrameUiController(*this));
  Show(true);

  m_run_dialog = new RunDialog(this, cache);
  m_crawler_dialog = new CrawlerDialog(this, cache);

  
  // Set the app icon Windows.
  wxFileName path(wxStandardPaths::Get().GetResourcesDir(), wxT("simplephoto.png"));
  if (path.FileExists()) {
    boost::scoped_ptr<Bitmap> bitmap(Bitmap::Read(path.GetFullPath()));
    if (bitmap.get() != NULL) {
      bitmap->Scale(wxSize(32, 32));
      boost::scoped_ptr<wxBitmap> b(bitmap->CreateWxBitmap());
      wxIcon icon;
      icon.CopyFromBitmap(*b.get());
      assert(icon.IsOk());
      SetIcon(icon);
    }
  }
  // wxIcon i1(wxICON(IDI_ICON1));
  // SetIcon(i1);

  //char buffer[1024];
  //memset(buffer, 2, 1024);
  //wxIcon i2(buffer, 32, 32);
  //SetIcon(i2);
}

void Frame::CreateMenu() {
  wxMenuBar* menu = new wxMenuBar();

  // File Menu
  wxMenu* file = new wxMenu();
  file->Append(ID_NEW_PROJECT, wxT("New Project"));
  file->AppendSeparator();
  file->Append(wxID_CLOSE, wxT("Exit"));
  menu->Append(file, wxT("&File"));

  // Edit Menu.
  wxMenu* edit = new wxMenu();
  edit->Append(wxID_PASTE, wxT("Paste\tCTRL+V"));
  menu->Append(edit, wxT("&Edit"));

  // Window Menu.
  wxMenu* window = new wxMenu();
  window->Append(ID_TOGGLE_DEBUG, wxT("&Debug View"));
  menu->Append(window, wxT("Window"));

  // Help Menu.
  wxMenu* help = new wxMenu();
  help->Append(wxID_ABOUT, wxT("About..."));
  menu->Append(help, wxT("&Help"));

  SetMenuBar(menu);
}

void Frame::InitAccelerators() {
  return;
	wxAcceleratorEntry entries[] = {
      wxAcceleratorEntry(wxACCEL_CTRL, 'd', ID_DEBUG),
	};
	SetAcceleratorTable(wxAcceleratorTable(ARRAY_SIZE(entries), entries));
}

void Frame::ShowDebugPanel() {
	if (m_debug.get() == NULL) {
		m_debug.reset(new DebugFrame(this));
		m_debug->OnInit();
		wxSize screen;
		wxDisplaySize(&screen.x, &screen.y);
		wxSize size(400, 400);
		m_debug->SetSize(size);
		wxPoint position(screen.x - size.x, screen.y - size.y);
		m_debug->SetPosition(position);
	}
  m_debug->Show(!m_debug->IsVisible());
	Raise();
}

void Frame::AddToolbarLeftPart(wxWindow* parent) {
	wxPanel* panel = new wxPanel(parent, -1);
  // panel->SetBackgroundColour(LEFT_TOOLBAR_COLOUR);
	panel->SetSizer(new wxGridSizer(1, 3));
  parent->GetSizer()->Add(panel, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 1);
	wxButton* plus = new wxButton(panel, ID_ADD_PHOTO_FILES, wxT("Add Photos"));
	panel->GetSizer()->Add(plus, 0, wxALIGN_CENTER | wxALL, 1);
	wxButton* plus_dir = new wxButton(panel, ID_ADD_PHOTO_DIR, wxT("Add Dir"));
  panel->GetSizer()->Add(plus_dir, 0, wxALIGN_CENTER | wxALL, 1);
//	wxButton* minus = new wxButton(panel, ID_REMOVE_PHOTO, wxT("Remove Selected"));
//	panel->GetSizer()->Add(minus, 0, wxALIGN_CENTER | wxALL, 1);
}

void Frame::AddToolbarRightPart(wxWindow* parent) {
	wxPanel* panel = new wxPanel(parent, -1);
	panel->SetSizer(new wxGridSizer(1, 1));
	parent->GetSizer()->Add(panel, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 1);
	wxButton* button = new wxButton(panel, ID_RUN, wxT("Run"));
	panel->GetSizer()->Add(button, 0, wxALIGN_CENTER | wxALL, 1);
  m_run_button = button;

  // panel->SetBackgroundColour(RIGHT_TOOLBAR_COLOUR);
}

void Frame::AddToolbarTopLine(wxWindow* parent) {
	// Toolbar top line
	wxPanel* panel = new wxPanel(parent);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	panel->SetSizer(sizer, true);
	m_file_extension = GetComboBox(panel, wxT("Extension:"), ID_EXTENSION_SELECTED);
	m_grouper = GetComboBox(panel, wxT("Group:"), ID_GROUP_SELECTED);
	m_resizer = GetComboBox(panel, wxT("Size:"), ID_SIZE_SELECTED);
	parent->GetSizer()->Add(panel, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 1);
	sizer->Layout();
}

void Frame::AddToolbarBottomLine(wxWindow* parent) {
	// Toolbar top line
	wxPanel* panel = new wxPanel(parent);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	panel->SetSizer(sizer, true);

	wxStaticText* label = new wxStaticText(panel, -1, wxT("Output Dir:"));
	sizer->Add(label, 0, wxALIGN_CENTER_VERTICAL, 3);

	m_output_dir = new wxDirPickerCtrl(panel, ID_OUTPUT_DIR_CHANGED);
	m_output_dir->SetPath(wxT("/Users/ruibm/"));
	sizer->Add(m_output_dir, 1, wxALIGN_CENTER | wxALL, 3);

	parent->GetSizer()->Add(panel, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 1);
	sizer->Layout();
}

void Frame::OnDestroy() {
	if (m_debug.get() != NULL) {
		m_debug->Show(false);
		m_debug->OnDestroy();
		m_debug.reset();
	}
}

void Frame::OnSize(wxSizeEvent& event) {
	wxFrame::OnSize(event);
	wxSize size = GetClientSize();
	const int width = size.x;
	const int height = size.y;
	const int toolbar_y = std::max(0, height - TOOLBAR_HEIGHT);
	const int scroll_width = m_scroll->GetSize().x;

	m_toolbar->SetSize(wxRect(0, toolbar_y, width, TOOLBAR_HEIGHT));
  // m_toolbar->SetBackgroundColour(*wxRED);
	m_canvas->SetSize(wxRect(0, 0, width - scroll_width, toolbar_y));
	m_canvas->LayoutGroups();
	m_toolbar->GetSizer()->Layout();
	m_scroll->SetSize(wxRect(width - scroll_width, 0, scroll_width, m_canvas->GetSize().y));
}

void Frame::OnCommand(wxCommandEvent& event) {
	Log::d << "OnCommand id=" << event.GetId() << Log::ENDL;
	switch (event.GetId()) {
		case ID_DEBUG:
			ShowDebugPanel();
			return;

		case ID_RUN:
			m_controller->GetListener()->OnRun();
			return;

		case ID_ADD_PHOTO_FILES: {
			wxFileDialog dialog(this, wxT("Choose photos to add..."),
					wxT(""), wxT(""), wxT("*.*"),
					wxFD_MULTIPLE | wxFD_FILE_MUST_EXIST | wxFD_OPEN);
			if (wxID_OK == dialog.ShowModal()) {
				wxArrayString paths;
				dialog.GetPaths(paths);
				m_controller->GetListener()->OnAddPhoto(paths);
			}
			return;
		}

		case ID_ADD_PHOTO_DIR: {
			wxDirDialog dialog(this, wxT("Choose photos dir..."));
			if (wxID_OK == dialog.ShowModal()) {
				wxArrayString paths;
				paths.Add(dialog.GetPath());
				m_controller->GetListener()->OnAddPhoto(paths);
			}
		}

		case ID_REMOVE_PHOTO:
			return;

		case ID_GROUP_SELECTED:
      m_controller->GetListener()->OnGroupSelected(m_grouper->GetValue());
			return;

		case ID_SIZE_SELECTED:
      m_controller->GetListener()->OnSizeSelected(m_resizer->GetValue());
			return;

		case ID_EXTENSION_SELECTED:
			m_controller->GetListener()->OnExtensionSelected(m_file_extension->GetValue());
			return;

    case wxID_ABOUT: {
      Log::d << "About menu clicked!!! Hurrah!!!" << Log::ENDL;
      AboutDialogUi* about = new AboutDialogUi(this);
      about->CenterOnParent();
      wxFileName path(wxStandardPaths::Get().GetResourcesDir(), wxT("simplephoto.png"));
      Log::d << "Search in path " << path.GetFullPath() << Log::ENDL;
      if (path.FileExists()) {
        about->m_bitmap->Init(m_controller->GetListener()->GetSmartCache());
        m_controller->GetListener()->GetSmartCache().GetBitmapCache().Cache(path.GetFullPath(), NULL);
        Photo photo(path.GetFullPath());
        about->m_bitmap->GetFrame().SetPhoto(photo);
      }
      about->ShowModal();
      return;
    }

    case wxID_CLOSE:
      Close();
      return;

    case ID_NEW_PROJECT:
      m_controller->GetListener()->OnNewProject();
      return;

    case ID_TOGGLE_DEBUG:
      ShowDebugPanel();
      return;

    case wxID_PASTE:
      ReadClipboard();
      return;

		default:
			break;
	}
}

void Frame::ReadClipboard() {
  wxClipboard clipboard;
  if (!clipboard.Open()) {
    return;
  }

  wxFileDataObject data;
  if (clipboard.IsSupported(wxDF_FILENAME) &&
      clipboard.GetData(data)) {
    const wxArrayString& files = data.GetFilenames();
    m_controller->GetListener()->OnAddPhoto(files);
  }

  clipboard.Close();
}

void Frame::OnOutputDirChanged(wxFileDirPickerEvent& event) {
	Log::d << "OnOutputDirChanged id=" << event.GetId() << Log::ENDL;
	assert(ID_OUTPUT_DIR_CHANGED == event.GetId());
	m_controller->GetListener()->OnOutputDirChanged(m_output_dir->GetPath());
}

void Frame::OnScroll(wxScrollEvent& event) {
	m_canvas->OnScroll(event);
}

UiController* Frame::GetUiController() {
	return m_controller.get();
}

}

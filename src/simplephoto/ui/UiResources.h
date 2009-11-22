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

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __UiResources__
#define __UiResources__

#include "simplephoto/ui/PhotoWidget.h"
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/gauge.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/scrolwin.h>

///////////////////////////////////////////////////////////////////////////

namespace simplephoto
{
	
	///////////////////////////////////////////////////////////////////////////////
	/// Class RunDialogUi
	///////////////////////////////////////////////////////////////////////////////
	class RunDialogUi : public wxDialog 
	{
		private:
		
		protected:
			wxPanel* m_panel4;
			simplephoto::PhotoWidget* m_bitmap;
			wxStaticText* m_from_path;
			wxStaticText* m_from_resolution;
			wxStaticText* m_to_path;
			wxStaticText* m_to_resolution;
			wxStaticText* m_photos_per_sec;
			wxStaticText* m_space_delta;
			wxStaticText* m_elapsed_time;
			wxStaticText* m_estimated_time;
			wxPanel* m_panel2;
			wxStaticText* m_photo_count;
			wxGauge* m_progress;
			wxButton* m_cancel;
			
			// Virtual event handlers, overide them in your derived class
			virtual void OnClose( wxCloseEvent& event ){ event.Skip(); }
			virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
			
		
		public:
			RunDialogUi( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Processing Photos..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
			~RunDialogUi();
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	/// Class CrawlerDialogUi
	///////////////////////////////////////////////////////////////////////////////
	class CrawlerDialogUi : public wxDialog 
	{
		private:
		
		protected:
			simplephoto::PhotoWidget* m_bitmap;
			wxStaticText* m_path;
			wxStaticText* m_file_size;
			wxStaticText* m_resolution;
			wxStaticText* m_created;
			wxPanel* m_panel21;
			wxStaticText* m_current_search_dir;
			wxStaticText* m_photos_found;
			wxStaticText* m_elapsed_time;
			wxPanel* m_panel2;
			wxGauge* m_progress;
			wxButton* m_cancel;
			
			// Virtual event handlers, overide them in your derived class
			virtual void OnClose( wxCloseEvent& event ){ event.Skip(); }
			virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
			
		
		public:
			CrawlerDialogUi( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Searching For Photos..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
			~CrawlerDialogUi();
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	/// Class AboutDialogUi
	///////////////////////////////////////////////////////////////////////////////
	class AboutDialogUi : public wxDialog 
	{
		private:
		
		protected:
			wxPanel* m_panel5;
			wxStaticText* m_about;
			wxPanel* m_panel6;
			wxScrolledWindow* m_scrolledWindow1;
			wxStaticText* m_thanks;
		
		public:
			simplephoto::PhotoWidget* m_bitmap;
			AboutDialogUi( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About SimplePhoto"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxSYSTEM_MENU );
			~AboutDialogUi();
		
	};
	
} // namespace simplephoto

#endif //__UiResources__

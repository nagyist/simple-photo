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

#include "UiResources.h"

///////////////////////////////////////////////////////////////////////////
using namespace simplephoto;

RunDialogUi::RunDialogUi( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_bitmap = new PhotoWidget(this);
	bSizer7->Add( m_bitmap, 0, wxALIGN_CENTER|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel4, wxID_ANY, wxT("Original Photo:") ), wxVERTICAL );
	
	m_from_path = new wxStaticText( m_panel4, wxID_ANY, wxT("Path: /Users/ruibm/bla"), wxDefaultPosition, wxDefaultSize, 0 );
	m_from_path->Wrap( -1 );
	sbSizer1->Add( m_from_path, 0, wxALL, 5 );
	
	m_from_resolution = new wxStaticText( m_panel4, wxID_ANY, wxT("Resolution: 2680x1280 pixels"), wxDefaultPosition, wxDefaultSize, 0 );
	m_from_resolution->Wrap( -1 );
	sbSizer1->Add( m_from_resolution, 0, wxALL, 5 );
	
	bSizer7->Add( sbSizer1, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel4, wxID_ANY, wxT("Destination Photo:") ), wxVERTICAL );
	
	m_to_path = new wxStaticText( m_panel4, wxID_ANY, wxT("Path: /Users/ruibm/bla"), wxDefaultPosition, wxDefaultSize, 0 );
	m_to_path->Wrap( -1 );
	sbSizer2->Add( m_to_path, 0, wxALL, 5 );
	
	m_to_resolution = new wxStaticText( m_panel4, wxID_ANY, wxT("Resolution: 2680x1280 pixels"), wxDefaultPosition, wxDefaultSize, 0 );
	m_to_resolution->Wrap( -1 );
	sbSizer2->Add( m_to_resolution, 0, wxALL, 5 );
	
	bSizer7->Add( sbSizer2, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_photos_per_sec = new wxStaticText( m_panel4, wxID_ANY, wxT("Photos Per Second: 5.3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_photos_per_sec->Wrap( -1 );
	gSizer1->Add( m_photos_per_sec, 0, wxALL, 5 );
	
	m_space_delta = new wxStaticText( m_panel4, wxID_ANY, wxT("Space Delta: -10MB"), wxDefaultPosition, wxDefaultSize, 0 );
	m_space_delta->Wrap( -1 );
	gSizer1->Add( m_space_delta, 0, wxALL, 5 );
	
	m_elapsed_time = new wxStaticText( m_panel4, wxID_ANY, wxT("Elapsed Time: 00:00:42"), wxDefaultPosition, wxDefaultSize, 0 );
	m_elapsed_time->Wrap( -1 );
	gSizer1->Add( m_elapsed_time, 0, wxALL, 5 );
	
	m_estimated_time = new wxStaticText( m_panel4, wxID_ANY, wxT("Estimated Time: 00:01:03"), wxDefaultPosition, wxDefaultSize, 0 );
	m_estimated_time->Wrap( -1 );
	gSizer1->Add( m_estimated_time, 0, wxALL, 5 );
	
	bSizer2->Add( gSizer1, 1, wxEXPAND, 5 );
	
	m_panel2 = new wxPanel( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer2->Add( m_panel2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_photo_count = new wxStaticText( m_panel4, wxID_ANY, wxT("420/1074 photos"), wxDefaultPosition, wxDefaultSize, 0 );
	m_photo_count->Wrap( -1 );
	bSizer3->Add( m_photo_count, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_progress = new wxGauge( m_panel4, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_progress->SetValue( 42 ); 
	bSizer3->Add( m_progress, 1, wxALIGN_CENTER|wxALL, 5 );
	
	m_cancel = new wxButton( m_panel4, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_cancel, 0, wxALIGN_CENTER|wxALL, 5 );
	
	bSizer2->Add( bSizer3, 0, wxEXPAND, 5 );
	
	bSizer7->Add( bSizer2, 0, wxEXPAND, 5 );
	
	m_panel4->SetSizer( bSizer7 );
	m_panel4->Layout();
	bSizer7->Fit( m_panel4 );
	bSizer1->Add( m_panel4, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( RunDialogUi::OnClose ) );
	m_cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( RunDialogUi::OnCancel ), NULL, this );
}

RunDialogUi::~RunDialogUi()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( RunDialogUi::OnClose ) );
	m_cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( RunDialogUi::OnCancel ), NULL, this );
}

CrawlerDialogUi::CrawlerDialogUi( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bitmap = new PhotoWidget(this);
	bSizer5->Add( m_bitmap, 0, wxALL, 5 );
	
	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 1, 1, 0, 0 );
	
	m_path = new wxStaticText( this, wxID_ANY, wxT("Photo Path: /Users/ruibm/bla.jpg"), wxDefaultPosition, wxDefaultSize, 0 );
	m_path->Wrap( -1 );
	gSizer4->Add( m_path, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_file_size = new wxStaticText( this, wxID_ANY, wxT("File Size: 200kb"), wxDefaultPosition, wxDefaultSize, 0 );
	m_file_size->Wrap( -1 );
	gSizer4->Add( m_file_size, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	m_resolution = new wxStaticText( this, wxID_ANY, wxT("Resolution: 1280x768"), wxDefaultPosition, wxDefaultSize, 0 );
	m_resolution->Wrap( -1 );
	gSizer4->Add( m_resolution, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	m_created = new wxStaticText( this, wxID_ANY, wxT("Created: 2009/06/04"), wxDefaultPosition, wxDefaultSize, 0 );
	m_created->Wrap( -1 );
	gSizer4->Add( m_created, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	bSizer5->Add( gSizer4, 1, wxEXPAND, 5 );
	
	bSizer91->Add( bSizer5, 1, wxEXPAND, 5 );
	
	m_panel21 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer91->Add( m_panel21, 0, wxEXPAND | wxALL, 5 );
	
	m_current_search_dir = new wxStaticText( this, wxID_ANY, wxT("Current Search Dir: /Users/ruibm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_current_search_dir->Wrap( -1 );
	bSizer91->Add( m_current_search_dir, 0, wxALL, 5 );
	
	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 1, 2, 0, 0 );
	
	m_photos_found = new wxStaticText( this, wxID_ANY, wxT("Photos Found: 42"), wxDefaultPosition, wxDefaultSize, 0 );
	m_photos_found->Wrap( -1 );
	gSizer3->Add( m_photos_found, 0, wxALL, 5 );
	
	m_elapsed_time = new wxStaticText( this, wxID_ANY, wxT("Elapsed Time: 00:00:42"), wxDefaultPosition, wxDefaultSize, 0 );
	m_elapsed_time->Wrap( -1 );
	gSizer3->Add( m_elapsed_time, 0, wxALL, 5 );
	
	bSizer91->Add( gSizer3, 0, wxEXPAND, 5 );
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer91->Add( m_panel2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_progress = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_progress->SetValue( 42 ); 
	bSizer9->Add( m_progress, 1, wxALIGN_CENTER|wxALL, 5 );
	
	m_cancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_cancel, 0, wxALIGN_CENTER|wxALL, 5 );
	
	bSizer91->Add( bSizer9, 0, wxEXPAND, 5 );
	
	bSizer4->Add( bSizer91, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer4 );
	this->Layout();
	bSizer4->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CrawlerDialogUi::OnClose ) );
	m_cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CrawlerDialogUi::OnCancel ), NULL, this );
}

CrawlerDialogUi::~CrawlerDialogUi()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CrawlerDialogUi::OnClose ) );
	m_cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CrawlerDialogUi::OnCancel ), NULL, this );
}

AboutDialogUi::AboutDialogUi( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	m_panel5 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bitmap = new PhotoWidget(this);
	m_bitmap->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	
	bSizer10->Add( m_bitmap, 0, wxALL, 5 );
	
	m_about = new wxStaticText( m_panel5, wxID_ANY, wxT("SimplePhoto \n\nVersion: 1.0.0\nRelease Date: 2009-11-21\nAuthor: Rui Barbosa Martins\nLicense: Apache License"), wxDefaultPosition, wxDefaultSize, 0 );
	m_about->Wrap( -1 );
	bSizer10->Add( m_about, 0, wxALL, 5 );
	
	m_panel5->SetSizer( bSizer10 );
	m_panel5->Layout();
	bSizer10->Fit( m_panel5 );
	bSizer9->Add( m_panel5, 0, wxEXPAND | wxALL, 5 );
	
	m_panel6 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_panel6, wxID_ANY, wxT("Special Thanks:") ), wxVERTICAL );
	
	m_scrolledWindow1 = new wxScrolledWindow( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	m_scrolledWindow1->SetMinSize( wxSize( -1,200 ) );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_thanks = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Special thanks to all the projects below:\n- wxWidgets\n- GraphicsMagick\n- libjpeg\n- libpng\n- libtiff\n- libgif\n- wxFormBuilder\n- QtCreator"), wxDefaultPosition, wxDefaultSize, 0 );
	m_thanks->Wrap( -1 );
	bSizer11->Add( m_thanks, 0, wxALL, 5 );
	
	m_scrolledWindow1->SetSizer( bSizer11 );
	m_scrolledWindow1->Layout();
	bSizer11->Fit( m_scrolledWindow1 );
	sbSizer3->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 0 );
	
	m_panel6->SetSizer( sbSizer3 );
	m_panel6->Layout();
	sbSizer3->Fit( m_panel6 );
	bSizer9->Add( m_panel6, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( bSizer9 );
	this->Layout();
	bSizer9->Fit( this );
}

AboutDialogUi::~AboutDialogUi()
{
}

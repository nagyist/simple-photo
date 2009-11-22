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
 * Application.cpp
 *
 *  Created on: Jul 10, 2009
 *      Author: ruibm
 */

#include "simplephoto/logic/Application.h"

#include <Magick++.h>

#include <wx/stdpaths.h>

#include <iostream>

#include "simplephoto/core/Log.h"
#include "simplephoto/logic/LogicCore.h"
#include "simplephoto/ui/DragAndDropTarget.h"
#include "simplephoto/ui/Frame.h"
#include "simplephoto/ui/PhotoCanvas.h"
#include "simplephoto/ui/PhotoFrame.h"
#include "simplephoto/ui/UiThreadRunner.h"

namespace {

const wxString APP_NAME(wxT("SimplePhoto"));
const int MAX_IN_MEMORY_IMAGES = 42;

}  // namespace

namespace simplephoto {

Application::Application()
    : m_frame(NULL),
      m_cache(MAX_IN_MEMORY_IMAGES, PhotoFrame::GetBitmapSize()) {
}

Application::~Application() {
}

bool Application::OnInit() {
	// To get command line arguments.
	wxApp::OnInit();

  wxString text(*argv);

//  wxString text(wxStandardPaths::Get().GetResourcesDir());
//  text.Append(wxFileName::GetPathSeparator());
//  Magick::InitializeMagick(C_STR(text));

  std::cerr << C_STR(text) << std::endl;
  Magick::InitializeMagick(C_STR(text));
	m_runner.reset(new UiThreadRunner);
	m_runner->SetEvtHandlerEnabled(true);
  m_frame = new Frame(APP_NAME);
  m_frame->OnInit(m_cache);
  m_core.reset(new LogicCore(*m_frame->GetUiController(), m_cache));
  m_frame->GetPhotoCanvas().SetDropTarget(new DragAndDropTarget(*(m_core.get())));
  Log::d << "ImageMagick Path: " << text << Log::ENDL;
#if wxUSE_DRAG_AND_DROP
  Log::d << "wxUSE_DRAG_AND_DROP is on!!!" << Log::ENDL;
#endif
	m_frame->Show(true);
	Log::d << "Application " << APP_NAME << " starting" << Log::ENDL;
	return true;
}

int Application::OnExit() {
	wxApp::OnExit();
	return 0;
}

}

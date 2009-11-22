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
 * DebugFrame.cpp
 *
 *  Created on: Jul 18, 2009
 *      Author: ruibm
 */

#include "simplephoto/ui/DebugFrame.h"

#include "simplephoto/core/Log.h"
#include "simplephoto/core/Runnable.h"
#include "simplephoto/ui/UiThreadRunner.h"

using simplephoto::DebugFrame;
using simplephoto::Log;

BEGIN_EVENT_TABLE(simplephoto::DebugFrame, wxFrame)
  EVT_CLOSE(simplephoto::DebugFrame::OnClose)
END_EVENT_TABLE()

namespace {

class ThreadMessage : public simplephoto::Runnable {
public:
	explicit ThreadMessage(const wxString& text)
			: m_text(text) {
		m_text.Trim();
		m_text.Prepend(wxString(wxT("-thread-")));
	}

	virtual void Run() {
		Log::d << m_text << Log::ENDL;
	}

private:
	wxString m_text;
};

class DebugFrameOut : public Log::Out {
public:
	DebugFrameOut(DebugFrame& frame) : m_frame(frame) {}
	virtual ~DebugFrameOut() {}
	virtual void Write(const wxString& message) {
		if (::wxIsMainThread()) {
			m_frame.AddText(message);
			m_frame.Update();
		} else {
			simplephoto::UiThreadRunner::Run(new ThreadMessage(message));
		}
	}

private:
	DebugFrame& m_frame;
};
}  // namespace

namespace simplephoto {

DebugFrame::DebugFrame(wxWindow* parent)
		: wxFrame(parent, -1, wxString(wxT("SimplePhoto Debug")), wxDefaultPosition, wxDefaultSize,
			wxFRAME_FLOAT_ON_PARENT | wxMINIMIZE_BOX |
			wxMAXIMIZE_BOX | wxCLOSE_BOX |
			wxRESIZE_BORDER | wxFRAME_NO_TASKBAR),
			m_text(NULL) {
}

DebugFrame::~DebugFrame() {
}

void DebugFrame::OnInit() {
	m_text = new wxTextCtrl(this, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	m_text->SetEditable(false);
	Log::d.SetOut(new DebugFrameOut(*this));
}

void DebugFrame::OnDestroy() {
	Log::d.SetOut(NULL);
}

void DebugFrame::AddText(const wxString& text) {
	wxWindow* window = GetParent()->GetCapture();
	m_text->AppendText(text);
	if (window != NULL) {
		// Gives focus back to the previously focused window.
		window->Raise();
	}
}

void DebugFrame::OnClose(wxCloseEvent& event) {
	Show(false);
	event.Veto();
}

}

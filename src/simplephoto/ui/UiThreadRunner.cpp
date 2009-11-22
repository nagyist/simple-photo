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
 * UiThreadRunner.cpp
 *
 *  Created on: Aug 23, 2009
 *      Author: ruibm
 */

#include "simplephoto/ui/UiThreadRunner.h"

#include <wx/wx.h>

#include "simplephoto/core/Log.h"
#include "simplephoto/ui/RunEvent.h"


BEGIN_EVENT_TABLE(simplephoto::UiThreadRunner, wxEvtHandler)
  EVT_CUSTOM(wxRunEvent, -1, simplephoto::UiThreadRunner::OnRunEvent)
END_EVENT_TABLE()

namespace {
	simplephoto::UiThreadRunner* s_instance = NULL;
}  // namespace

namespace simplephoto {

UiThreadRunner::UiThreadRunner() {
	s_instance = this;
}

UiThreadRunner::~UiThreadRunner() {
	if (s_instance == this) {
		s_instance = NULL;
	}
}

void UiThreadRunner::OnRunEvent(wxEvent& event) {
	RunEvent& run_event = *(static_cast<RunEvent*>(&event));
	Log::d << "Running event [" << reinterpret_cast<long long>(&run_event) << "]." << Log::ENDL;
	run_event.Run();

}

void UiThreadRunner::Run(Runnable* runnable) {
	assert(s_instance != NULL);
	RunEvent event(runnable);
	::wxPostEvent(s_instance, event);
}

}

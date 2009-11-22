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
 * RunEvent.cpp
 *
 *  Created on: Aug 23, 2009
 *      Author: ruibm
 */

#include "simplephoto/ui/RunEvent.h"

#include "simplephoto/core/Runnable.h"

DEFINE_EVENT_TYPE(wxRunEvent)

namespace simplephoto {

RunEvent::RunEvent(Runnable* runnable)
		: wxEvent(0, wxRunEvent),
			m_runnable(runnable) {
	assert(m_runnable != NULL);
}

RunEvent::~RunEvent() {
}

void RunEvent::Run() {
	m_runnable->Run();
	delete m_runnable;
	m_runnable = NULL;
}

wxEvent* RunEvent::Clone() const {
	RunEvent* event = new RunEvent(m_runnable);
	return event;
}

}

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
 * RunnerThread.cpp
 *
 *  Created on: Sep 19, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/RunnerThread.h"

#include "simplephoto/core/Project.h"
#include "simplephoto/logic/RunnerListener.h"

namespace simplephoto {

RunnerThread::RunnerThread(Project& project, RunnerListener& listener)
    : wxThread(wxTHREAD_JOINABLE),
      m_converter(project, listener) {
}

void RunnerThread::StartRunning() {  
  wxThreadError error = Create();
  assert(error == wxTHREAD_NO_ERROR);
  error = Run();
  assert(error ==	 wxTHREAD_NO_ERROR);
}

void RunnerThread::WaitToExit() {
  const int ret_value = reinterpret_cast<int>(Wait());
  assert(ret_value == 0);
}

void RunnerThread::Cancel() {
  m_converter.Cancel();
}

wxThread::ExitCode RunnerThread::Entry() {
  m_converter.Convert();
  return 0;
}

}  // namespace simplephoto

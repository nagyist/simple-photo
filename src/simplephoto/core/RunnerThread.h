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
 * RunnerThread.h
 *
 *  Created on: Sep 19, 2009
 *      Author: ruibm
 */

#ifndef RUNNERTHREAD_H
#define RUNNERTHREAD_H

#include <wx/thread.h>

#include "simplephoto/core/Converter.h"

namespace simplephoto {
class Project;
class RunnerListener;

class RunnerThread : private wxThread {
public:
  RunnerThread(Project& project, RunnerListener& listener);

  void StartRunning();
  void WaitToExit();
  void Cancel();

private:
  virtual wxThread::ExitCode Entry();

  Converter m_converter;
};
}  // namespace simplephoto

#endif // RUNNERTHREAD_H

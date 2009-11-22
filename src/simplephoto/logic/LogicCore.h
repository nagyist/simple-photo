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
 * LogicCore.h
 *
 *  Created on: Jul 19, 2009
 *      Author: ruibm
 */

#ifndef LOGICCORE_H_
#define LOGICCORE_H_

#include <wx/wx.h>

#include "simplephoto/ui/UiListener.h"
#include "simplephoto/core/Macros.h"
#include "simplephoto/core/SmartCache.h"

namespace simplephoto {

class CrawlerThread;
class Project;
class RunnerThread;
class UiController;

class LogicCore : public UiListener {
public:
  LogicCore(UiController& controller, SmartCache& cache);
  virtual ~LogicCore();

	virtual void OnAddPhoto(const wxArrayString& paths);
  virtual void OnCancelAddPhoto();
	virtual void OnRun();
	virtual void OnGroupSelected(const wxString& selection);
	virtual void OnSizeSelected(const wxString& selection);
	virtual void OnExtensionSelected(const wxString& selection);
  virtual void OnOutputDirChanged(const wxString& path);  
  virtual void OnCancelRun();
  virtual void OnNewProject();
  virtual SmartCache& GetSmartCache() { return m_cache; }

private:
	void ResetUi();

	UiController& m_controller;
  boost::scoped_ptr<Project> m_project;
  SmartCache& m_cache;
  CrawlerThread* m_crawler_thread;
  RunnerThread* m_runner_thread;
};

}

#endif /* LOGICCORE_H_ */

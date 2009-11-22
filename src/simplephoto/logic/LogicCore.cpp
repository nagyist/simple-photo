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
 * LogicCore.cpp
 *
 *  Created on: Jul 19, 2009
 *      Author: ruibm
 */

#include "simplephoto/logic/LogicCore.h"

#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

#include "simplephoto/core/CrawlerThread.h"
#include "simplephoto/core/Grouper.h"
#include "simplephoto/core/Log.h"
#include "simplephoto/core/PhotoFinder.h"
#include "simplephoto/core/PhotoGroup.h"
#include "simplephoto/core/Project.h"
#include "simplephoto/core/RunnerThread.h"
#include "simplephoto/logic/ConversionOptions.h"
#include "simplephoto/logic/CrawlerListener.h"
#include "simplephoto/logic/RunnerListener.h"
#include "simplephoto/ui/CrawlerDialog.h"
#include "simplephoto/ui/RunDialog.h"
#include "simplephoto/ui/UiController.h"

namespace simplephoto {

LogicCore::LogicCore(UiController& controller, SmartCache& cache)
    : m_controller(controller),
      m_crawler_thread(NULL),
      m_runner_thread(NULL),
      m_cache(cache) {
	m_controller.SetListener(this);
  m_project.reset(new Project);
	ResetUi();
}

LogicCore::~LogicCore() {
}

void LogicCore::ResetUi() {
	wxArrayString entries;
	ConversionOptions::GetResizers(entries);
	m_controller.SetSizes(entries, 0);
	ConversionOptions::GetGroupers(entries);
	m_controller.SetGroupers(entries, 0);
	ConversionOptions::GetExtensions(entries);
	m_controller.SetExtensions(entries, 0);
  m_controller.SetCache(m_cache);
  m_controller.SetRunEnabled(m_project->GetPhotoCount() > 0);  
  m_controller.Update(*m_project.get());
}

void LogicCore::OnAddPhoto(const wxArrayString& paths) {
  PhotoGroup out(wxT("LogicCore::OnAddPhoto::temp_group"));
  CrawlerListener listener(m_cache.GetBitmapCache(), m_controller.GetCrawlerDialog());
  CrawlerThread crawler(paths, listener, out);
  m_crawler_thread = &crawler;
  crawler.StartRunning();
  m_controller.GetCrawlerDialog().CenterOnParent();
  m_controller.GetCrawlerDialog().Reset();
  m_controller.GetCrawlerDialog().ShowModal();

  crawler.WaitToExit();

  // Check if the user cancelled the search.
  if (m_crawler_thread != NULL) {
    for (int i = 0; i < out.m_photos.size(); ++i) {
      Photo* photo = out.m_photos[i];
      if (!m_project->ContainsPhoto(*photo)) {
        m_project->AddPhoto(photo);
      } else {
        delete photo;
      }
    }

    m_project->UpdateGroups();
    m_controller.Update(*m_project.get());
    m_crawler_thread = NULL;
  } else {
    out.ClearAndDeletePhotos();
  }

  m_controller.SetRunEnabled(m_project->GetPhotoCount() > 0);
}

void LogicCore::OnCancelAddPhoto() {
  if (m_crawler_thread != NULL) {
    m_crawler_thread->Cancel();
    m_crawler_thread = NULL;
  }
}

void LogicCore::OnGroupSelected(const wxString& selection) {
	Log::d << "Listener OnGroupSelected: " << selection << Log::ENDL;
  const Grouper* grouper = ConversionOptions::GetGrouper(selection);
  assert(grouper != NULL);
  m_project->SetGrouper(grouper->Clone());
  m_project->UpdateGroups();
  m_controller.Update(*m_project.get());
}

void LogicCore::OnSizeSelected(const wxString& selection) {
	Log::d << "Listener OnSizeSelected: " << selection << Log::ENDL;
  const Resizer* resizer = ConversionOptions::GetResizer(selection);
  assert(resizer != NULL);
  m_project->SetResizer(*resizer);
  m_project->UpdatePhotoCrop();
  m_controller.Update(*m_project.get());
}

void LogicCore::OnExtensionSelected(const wxString& selection) {
	Log::d << "Listener OnExtensionSelected: " << selection << Log::ENDL;
  Extension extension = ConversionOptions::GetExtension(selection);
  assert(extension != INVALID);
  m_project->SetFormat(extension);
}

void LogicCore::OnOutputDirChanged(const wxString& path) {
	Log::d << "Listener OnOutputDirChanged: " << path << Log::ENDL;
  m_project->SetOutputDir(path);
}

void LogicCore::OnRun() {
  Log::d << "Listener OnRun: " << Log::ENDL;
  simplephoto::RunDialog& dialog = m_controller.GetRunDialog();
  dialog.SetUiListener(this);
  RunnerListener listener(dialog, m_cache.GetBitmapCache(), m_project->GetPhotoCount());
  RunnerThread thread(*m_project.get(), listener);
  m_runner_thread = &thread;
  thread.StartRunning();
  dialog.CenterOnParent();
  dialog.Reset(m_project->GetPhotoCount());
  dialog.ShowModal();
  thread.WaitToExit();
  m_runner_thread = NULL;
}

void LogicCore::OnCancelRun() {
  Log::d << "Listener OnCancelRun: "<< Log::ENDL;
  if (m_runner_thread != NULL) {
    m_runner_thread->Cancel();    
  }
}

void LogicCore::OnNewProject() {
  m_project.reset(new Project);
  m_controller.Update(*m_project.get());
}

}

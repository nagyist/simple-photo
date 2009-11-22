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
 * CrawlerThread.cpp
 *
 *  Created on: Aug 16, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/CrawlerThread.h"

#include <wx/filename.h>

#include "simplephoto/core/Log.h"
#include "simplephoto/core/PhotoFinder.h"
#include "simplephoto/core/PhotoGroup.h"
#include "simplephoto/logic/CrawlerListener.h"

namespace simplephoto {

CrawlerThread::CrawlerThread(const wxArrayString& paths, CrawlerListener& listener,
                             PhotoGroup& out)
		: wxThread(wxTHREAD_JOINABLE),
			m_paths(paths),
			m_listener(listener),
      m_group(out),
      m_finder(NULL) {
  Log::d << "CrawlerThread::CrawlerThread()" << Log::ENDL;
}

CrawlerThread::~CrawlerThread() {
	Log::d << "CrawlerThread::~CrawlerThread()" << Log::ENDL;
}

wxThread::ExitCode CrawlerThread::Entry() {
	Log::d << "CrawlerThread is starting..." << Log::ENDL;
	for (unsigned int i = 0; i < m_paths.Count(); ++i) {
		wxFileName path(m_paths[i]);
		Log::d << "Crawling " << path.GetFullPath() << Log::ENDL;
    PhotoFinder finder(path);

    m_mutex.Lock();
    m_finder = &finder;
    m_mutex.Unlock();

    finder.SetListener(&m_listener);
    finder.Find(m_group);

    m_mutex.Lock();
    m_finder = NULL;
    m_mutex.Unlock();
	}
  m_listener.OnCrawlFinished();
	Log::d << "CrawlerThread is finished..." << Log::ENDL;
	return 0;
}

void CrawlerThread::StartRunning() {
  wxThreadError error = Create();
  assert(error == wxTHREAD_NO_ERROR);
  error = Run();
  assert(error ==	 wxTHREAD_NO_ERROR);
}

void CrawlerThread::WaitToExit() {
  const int ret_value = reinterpret_cast<int>(Wait());
  assert(ret_value == 0);
}

void CrawlerThread::Cancel() {
  m_mutex.Lock();
  if (m_finder != NULL) {
    m_finder->Cancel();
  }
  m_mutex.Unlock();
}

}

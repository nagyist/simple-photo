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
 * CrawlerThread.h
 *
 *  Created on: Aug 16, 2009
 *      Author: ruibm
 */

#ifndef CRAWLERTHREAD_H_
#define CRAWLERTHREAD_H_

#include <wx/wx.h>
#include <wx/thread.h>

#include <simplephoto/core/PhotoGroup.h>

namespace simplephoto {

class CrawlerListener;
class PhotoFinder;

class CrawlerThread : protected wxThread {
public:
  CrawlerThread(const wxArrayString& m_paths, CrawlerListener& listener,
                PhotoGroup& out);
	virtual ~CrawlerThread();

  void StartRunning();
  void WaitToExit();
  void Cancel();

private:
  virtual wxThread::ExitCode Entry();

	const wxArrayString& m_paths;
  CrawlerListener& m_listener;
  PhotoGroup& m_group;

  // Lock this mutex to access m_finder.
  wxMutex m_mutex;
  PhotoFinder* m_finder;
};

}

#endif /* CRAWLERTHREAD_H_ */

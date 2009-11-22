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
 * CrawlerListener.h
 *
 *  Created on: Aug 23, 2009
 *      Author: ruibm
 */

#ifndef CRAWLERLISTENER_H_
#define CRAWLERLISTENER_H_

#include "simplephoto/core/PhotoFinder.h"

#include <wx/stopwatch.h>

namespace simplephoto {

class BitmapCache;
class CrawlerDialog;

class CrawlerListener : public PhotoFinderListener {
public:
	CrawlerListener(BitmapCache& cache, CrawlerDialog& dialog);
  virtual ~CrawlerListener();

  void OnCrawlFinished();

private:
	virtual void OnDirChange(const wxString& dir);
	virtual void OnPhotoFound(Photo& photo);

	BitmapCache& m_cache;
	CrawlerDialog& m_dialog;
  wxStopWatch m_new_photo;
  wxStopWatch m_new_dir;
  int m_total_photos;
};

}

#endif /* CRAWLERLISTENER_H_ */

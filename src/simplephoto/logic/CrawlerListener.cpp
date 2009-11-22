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
 * CrawlerListener.cpp
 *
 *  Created on: Aug 23, 2009
 *      Author: ruibm
 */

#include "simplephoto/logic/CrawlerListener.h"

#include "simplephoto/core/Log.h"
#include "simplephoto/core/BitmapCache.h"
#include "simplephoto/core/Runnable.h"
#include "simplephoto/ui/CrawlerDialog.h"
#include "simplephoto/ui/UiThreadRunner.h"

namespace {
using namespace simplephoto;

const int TIME_BETWEEN_UPDATES_MS = 1000;

class UiUpdater : public Runnable {
private:
  CrawlerDialog& m_dialog;
  BitmapCache& m_cache;

  Photo m_photo;
  int m_total_photos;
  bool m_update_photo;
  wxString m_dir;
  bool m_dir_update;
  bool m_crawl_finished;

public:
  UiUpdater(CrawlerDialog& dialog, BitmapCache& cache)
      : m_dialog(dialog),
        m_cache(cache),
        m_total_photos(0),
        m_update_photo(false),
        m_crawl_finished(false),
        m_dir_update(false) {}

  virtual void Run() {
    if (m_update_photo) {
      Log::d << "A photo has been found: " << m_photo.m_path.GetFullName() << Log::ENDL;
      m_dialog.SetPhoto(m_photo);
      m_dialog.SetDir(m_photo.m_path.GetPath());
      m_dialog.SetTotalPhotos(m_total_photos);
    }
    if (m_dir_update) {
      Log::d << "Current search dir has changed: " << m_dir << Log::ENDL;
      m_dialog.SetDir(m_dir);
    }
    m_dialog.Update();
    if (m_crawl_finished) {
      m_dialog.EndModal(0);
    }
  }

  void SetPhoto(const Photo& photo, int total_photos) {
    m_photo = photo;
    m_total_photos = total_photos;
    m_update_photo = true;
  }

  void SetDir(const wxString& dir) {
    m_dir = dir;
    m_dir_update = true;
  }

  void SetCrawlFinished() {
    m_crawl_finished = true;
  }
};

}  // namespace

namespace simplephoto {

CrawlerListener::CrawlerListener(BitmapCache& cache, CrawlerDialog& dialog)
		: m_cache(cache),
      m_dialog(dialog),
      m_total_photos(0) {
}

CrawlerListener::~CrawlerListener() {
}

void CrawlerListener::OnCrawlFinished() {
  UiUpdater* updater = new UiUpdater(m_dialog, m_cache);
  updater->SetCrawlFinished();
  UiThreadRunner::Run(updater);
}

void CrawlerListener::OnDirChange(const wxString& dir) {
  if (m_new_dir.Time() > TIME_BETWEEN_UPDATES_MS) {
    UiUpdater* updater = new UiUpdater(m_dialog, m_cache);
    updater->SetDir(dir);
    UiThreadRunner::Run(updater);
    Log::d << "CrawlerListener::OnDirChange" << Log::ENDL;
    m_new_dir.Start();
  }
}

void CrawlerListener::OnPhotoFound(Photo& photo) {
  Bitmap* bitmap = Bitmap::Read(photo.m_path.GetFullPath());
  if (bitmap != NULL) {
    photo.m_size = bitmap->GetSize();
    m_cache.Cache(photo.m_path.GetFullPath(), bitmap);
    bitmap = NULL;
  }
  ++m_total_photos;
  if (m_new_photo.Time() > TIME_BETWEEN_UPDATES_MS) {
    UiUpdater* updater = new UiUpdater(m_dialog, m_cache);
    updater->SetPhoto(photo, m_total_photos);
    UiThreadRunner::Run(updater);
    Log::d << "CrawlerListener::OnPhotoFound" << Log::ENDL;
    m_new_photo.Start();
    m_new_dir.Start();
	}
}
}  // namespace simplephoto

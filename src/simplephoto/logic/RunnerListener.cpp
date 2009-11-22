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
 * RunnerListener.cpp
 *
 *  Created on: Sep 19, 2009
 *      Author: ruibm
 */

#include "simplephoto/logic/RunnerListener.h"

#include "simplephoto/core/BitmapCache.h"
#include "simplephoto/core/Photo.h"
#include "simplephoto/core/Runnable.h"
#include "simplephoto/ui/RunDialog.h"
#include "simplephoto/ui/UiResources.h"
#include "simplephoto/ui/UiThreadRunner.h"

namespace {

using namespace simplephoto;

const long TIME_BETWEEN_UPDATES_MS = 1000;

class RunDialogRunnable : public Runnable {
public:
  RunDialogRunnable(RunDialog& dialog, BitmapCache& cache)
      : m_dialog(dialog),
        m_cache(cache) {
  }

  virtual void Run() {
    m_dialog.SetOriginal(m_original);
    m_dialog.SetDestination(m_destination);
    float photos_per_sec = static_cast<float>(m_converted_photos) / m_total_photos;
    int estimated_ms = m_elapsed_time_ms +
                       ((m_total_photos - m_converted_photos) * 1000) / (photos_per_sec);
    m_dialog.SetStats(photos_per_sec, m_bytes_delta, m_elapsed_time_ms, estimated_ms);
    m_dialog.SetProgress(m_converted_photos, m_total_photos);
    m_dialog.Update();
  }

  RunDialog& m_dialog;
  BitmapCache& m_cache;
  Photo m_original;
  Photo m_destination;
  int m_converted_photos;
  int m_total_photos;
  int m_bytes_delta;
  int m_elapsed_time_ms;
};
}  // namespace

namespace simplephoto {

RunnerListener::RunnerListener(RunDialog& dialog, BitmapCache& cache, int total_photos)
    : m_dialog(dialog),
      m_cache(cache),
      m_total_photos(total_photos),
      m_converted_photos(0),
      m_failed_photos(0),
      m_bytes_delta(0) {
  m_run_start.Start();
  m_last_update.Start();
}

RunnerListener::~RunnerListener() {
}

void RunnerListener::OnConvertSuccess(const Photo& original, const Photo& destination) {
  ++m_converted_photos;
  m_bytes_delta += (destination.m_size_bytes - original.m_size_bytes);
  if (m_last_update.Time() > TIME_BETWEEN_UPDATES_MS ||
      m_converted_photos + m_failed_photos == m_total_photos) {
    RunDialogRunnable* runnable = new RunDialogRunnable(m_dialog, m_cache);
    runnable->m_bytes_delta = m_bytes_delta;
    runnable->m_total_photos = m_total_photos;
    runnable->m_converted_photos = m_converted_photos + m_failed_photos;
    runnable->m_elapsed_time_ms = static_cast<int>(m_run_start.Time());
    runnable->m_original = original;
    runnable->m_destination = destination;
    UiThreadRunner::Run(runnable);
    m_last_update.Start();
  }
}

void RunnerListener::OnConvertFail(const Photo& original) {
  ++m_failed_photos;
}

}  // namespace simplephoto

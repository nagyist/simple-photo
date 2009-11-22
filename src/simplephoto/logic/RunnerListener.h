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
 * RunnerListener.h
 *
 *  Created on: Sep 19, 2009
 *      Author: ruibm
 */

#ifndef RUNNERLISTENER_H
#define RUNNERLISTENER_H

#include "simplephoto/core/Converter.h"

#include <wx/stopwatch.h>

namespace simplephoto {

class BitmapCache;
class RunDialog;

class RunnerListener : public ConverterListener {
public:
  RunnerListener(RunDialog& dialog, BitmapCache& cache, int total_photos);
  virtual ~RunnerListener();

  virtual void OnConvertSuccess(const Photo& original, const Photo& destination);
  virtual void OnConvertFail(const Photo& original);

private:
  RunDialog& m_dialog;
  BitmapCache& m_cache;
  const int m_total_photos;
  int m_converted_photos;
  int m_failed_photos;
  int m_bytes_delta;
  wxStopWatch m_run_start;
  wxStopWatch m_last_update;
};

}  // namespace

#endif // RUNNERLISTENER_H

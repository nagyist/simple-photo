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
 * TextUtil.cpp
 *
 *  Created on: Sep 27, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/TextUtil.h"

#include "simplephoto/core/Macros.h"

namespace {

const wxChar* BYTE_UNITS[] = {
    wxT("Bytes"),
    wxT("KB"),
    wxT("MB"),
    wxT("GB"),
    wxT("TB")
};

const int BYTE_DIVISOR = 1024;

const wxString TIME_FORMATS[] = {
  wxT("%02s"),
  wxT("%02m%02s"),
  wxT("%02dh%02m%02s"),
  wxT("%dd%02dh%02m%02s"),
};

const int SECS_PER_MINUTE = 60;
const int MINS_PER_HOUR = 60;
const int SECS_PER_HOUR = SECS_PER_MINUTE * MINS_PER_HOUR;
const int SECS_PER_DAY = SECS_PER_HOUR * 24;

unsigned int RSHash(const char* str, unsigned int size) {
  unsigned int b = 378551;
  unsigned int a = 63689;
  unsigned int hash = 0;
  for(unsigned int i = 0; i < size; ++i) {
    hash = hash * a + str[i];
    a = a * b;
  }
  return hash;
}

}  // namespace

namespace simplephoto {

wxString TextUtil::BytesToString(int bytes) {
  int unit = 0;
  const int sign = bytes < 0 ? -1 : 1;
  float value = sign * bytes;
  while (value >= BYTE_DIVISOR) {
    value /= BYTE_DIVISOR;
    ++unit;
  }
  value *= sign;
  assert(unit < ARRAY_SIZE(BYTE_UNITS));
  return wxString::Format(wxT("%.1f %s"), value, BYTE_UNITS[unit]);
}

wxString TextUtil::SecondsToString(int seconds) {
  int format = 0;
  if (seconds < SECS_PER_MINUTE) {
    return wxString::Format(wxT("%02ds"), seconds);
  } else if (seconds < SECS_PER_HOUR) {
    return wxString::Format(wxT("%02dm%02ds"),
                            seconds / SECS_PER_MINUTE,
                            seconds % SECS_PER_MINUTE);
  } else if (seconds < SECS_PER_DAY) {    
    return wxString::Format(wxT("%02dh%02dm%02ds"),
                            seconds / SECS_PER_HOUR,
                            (seconds % SECS_PER_HOUR) / SECS_PER_MINUTE,
                            seconds % SECS_PER_MINUTE);
  } else {
    return wxString::Format(wxT("%dd%02dh%02dm%02ds"),
                            seconds / SECS_PER_DAY,
                            (seconds % SECS_PER_DAY) / SECS_PER_HOUR,
                            (seconds % SECS_PER_HOUR) / SECS_PER_MINUTE,
                            seconds % SECS_PER_MINUTE);
  }
}

unsigned int TextUtil::Hash(const wxString& text) {
  const char* data = C_STR(text);
  size_t size = strlen(data);
  return RSHash(data, size);
}

}  // namespace simplephoto

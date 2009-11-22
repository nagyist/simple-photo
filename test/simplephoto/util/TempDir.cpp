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
 * TempDir.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: ruibm
 */

#include "simplephoto/util/TempDir.h"

#include "wx/dir.h"
#include "wx/filename.h"
#include "wx/stdpaths.h"

#include "simplephoto/core/FsUtil.h"

namespace simplephoto {

TempDir::TempDir() {
  m_path = wxFileName(wxStandardPaths::Get().GetTempDir(), wxEmptyString);
  m_path.AppendDir(wxT("SimplePhotoConverterTests"));
  if (m_path.DirExists()) {
    FsUtil::RmDir(m_path.GetFullPath());
	}
  wxFileName::Mkdir(m_path.GetFullPath());
}

TempDir::~TempDir() {
}

}

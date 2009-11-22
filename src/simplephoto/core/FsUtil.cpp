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
 * FsUtil.cpp
 *
 *  Created on: Jul 19, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/FsUtil.h"

#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <vector>

#include "simplephoto/core/Log.h"

namespace {

using namespace simplephoto;

class Traverser : public wxDirTraverser {
public:
	virtual wxDirTraverseResult OnDir(const wxString& name) {
		m_dirs.push_back(name);
		return wxDIR_CONTINUE;
	}

	virtual wxDirTraverseResult OnFile(const wxString& name) {
		m_files.push_back(name);
		return wxDIR_CONTINUE;
	}

	virtual wxDirTraverseResult OnOpenError(const wxString& name) {
		return wxDIR_CONTINUE;
	}

	std::vector<wxString> m_dirs;
	std::vector<wxString> m_files;
};
}  // namespace

namespace simplephoto {

bool FsUtil::RmDir(const wxString& path) {
	if (!wxDir::Exists(path)) {
		return false;
	}
	wxFileName file_name(path);
	wxDir dir(file_name.GetFullPath());
	Traverser traverser;
	dir.Traverse(traverser);
	for (unsigned int i = 0; i < traverser.m_files.size(); ++i) {
		::wxRemoveFile(traverser.m_files[i]);
	}
	for (unsigned int i = 0; i < traverser.m_dirs.size(); ++i) {
		::wxRmdir(traverser.m_dirs[traverser.m_dirs.size() - i - 1]);
	}
	::wxRmdir(path);
	return !wxDir::Exists(path);
}

}

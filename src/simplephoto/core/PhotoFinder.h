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
 * PhotoFinder.h
 *
 *  Created on: May 21, 2009
 *      Author: ruibm
 */

#ifndef PHOTOFINDER_H_
#define PHOTOFINDER_H_

#include <wx/dir.h>
#include <wx/filename.h>
#include <vector>

namespace simplephoto {

class Photo;
class PhotoGroup;

class PhotoFinderListener {
public:
	virtual ~PhotoFinderListener() {}
	virtual void OnDirChange(const wxString& dir) = 0;
	virtual void OnPhotoFound(Photo& photo) = 0;
};

class PhotoFinder : public wxDirTraverser {
public:
	explicit PhotoFinder(const wxFileName& path);
	virtual ~PhotoFinder();

	void Find(PhotoGroup& group);
	void SetListener(PhotoFinderListener* listener) { m_listener = listener; }
  void Cancel() { m_cancel = true; }

private:
  virtual wxDirTraverseResult OnDir(const wxString& path);
  virtual wxDirTraverseResult OnFile(const wxString& path);
  virtual wxDirTraverseResult OnOpenError(const wxString& path);

	wxFileName m_root;
	PhotoGroup* m_group;
	wxString m_current_dir;
	PhotoFinderListener* m_listener;
  volatile bool m_cancel;
};

}

#endif /* PHOTOFINDER_H_ */

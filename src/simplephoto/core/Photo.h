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
 * Photo.h
 *
 *  Created on: Apr 27, 2009
 *      Author: ruibm
 */

#ifndef PHOTO_H_
#define PHOTO_H_

#include <wx/datetime.h>
#include <wx/filename.h>
#include <wx/gdicmn.h>
#include <wx/bitmap.h>

namespace simplephoto {

class Photo {
public:
	Photo();
	explicit Photo(const wxString& path);
	virtual ~Photo();

  bool IsSizeSet() const;

	static bool IsValidPhoto(const wxString& path);

	bool operator==(const Photo& photo) const;
	bool operator!=(const Photo& photo) const;

	wxFileName m_path;
  wxDateTime m_created;
  wxDateTime m_modified;
  wxDateTime m_accessed;
  unsigned int m_size_bytes;
  wxSize m_size;

private:
	void LoadData();
  void Init();
};

}

#endif /* PHOTO_H_ */

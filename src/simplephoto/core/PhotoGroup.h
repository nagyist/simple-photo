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
 * PhotoGroup.h
 *
 *  Created on: May 11, 2009
 *      Author: ruibm
 */

#ifndef PHOTOGROUP_H_
#define PHOTOGROUP_H_

#include <wx/string.h>
#include <vector>

namespace simplephoto {

class Photo;

class PhotoGroup {
public:
	explicit PhotoGroup(const wxString& name);
	virtual ~PhotoGroup();

	void AddPhoto(Photo* photo);
	void SortByCreationDate(bool ascending);
	void SortByName(bool ascending);
	void ClearAndDeletePhotos();
	void Clear();

	const wxString m_name;
	std::vector<Photo*> m_photos;
};

}

#endif /* PHOTOGROUP_H_ */

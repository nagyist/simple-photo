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
 * Project.h
 *
 *  Created on: Jun 27, 2009
 *      Author: ruibm
 */

#ifndef PROJECT_H_
#define PROJECT_H_

#include <map>
#include <vector>
#include <wx/wx.h>

#include "simplephoto/core/Extension.h"
#include "simplephoto/core/Grouper.h"
#include "simplephoto/core/Macros.h"
#include "simplephoto/core/Photo.h"
#include "simplephoto/core/PhotoGroup.h"
#include "simplephoto/core/Resizer.h"

namespace simplephoto {

class Project {
public:
	Project();
	virtual ~Project();

	wxString GetOutputDir() const;
	void SetOutputDir(const wxString& output_dir);

	const Resizer& GetResizer() const;
	void SetResizer(const Resizer& resizer);

	Extension GetFormat() const;
	void SetFormat(Extension format);

	Grouper& GetGrouper() const;
	void SetGrouper(Grouper* grouper);
	void UpdateGroups();

	int GetGroupCount() const;
	const PhotoGroup& GetGroup(int index) const;

  wxRect GetPhotoCrop(const Photo& photo) const;
  void SetPhotoCrop(const Photo& photo, const wxRect& crop);
	void UpdatePhotoCrop();
  bool HasPhotoCrop(const Photo& photo) const;

	// Takes ownership.
	bool AddPhoto(Photo* photo);
	int GetPhotoCount() const;
	bool ContainsPhoto(const Photo& photo) const;
	// void RemovePhoto(const Photo& photo);

private:
	void DeletePhotos();
	void DeleteGroups();
	static wxString GetDefaultOutputDir();

	wxString m_output_dir;
	Resizer m_resizer;
	Extension m_format;
	scoped_ptr<Grouper> m_grouper;

	std::vector<Photo*> m_photos;
  std::map<wxString, bool> m_photos_map;
	std::vector<PhotoGroup*> m_groups;
  std::map<wxString, wxRect> m_crops;

	DISABLE_MAGIC_METHODS(Project);
};

}

#endif /* PROJECT_H_ */

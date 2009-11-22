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
 * UiListener.h
 *
 *  Created on: Jul 18, 2009
 *      Author: ruibm
 */

#ifndef UILISTENER_H_
#define UILISTENER_H_

namespace simplephoto {

class SmartCache;

class UiListener {
public:
	UiListener() {}
	virtual ~UiListener() {}

	virtual void OnAddPhoto(const wxArrayString& paths) = 0;
  virtual void OnCancelAddPhoto() = 0;
	virtual void OnGroupSelected(const wxString& selection) = 0;
	virtual void OnSizeSelected(const wxString& selection) = 0;
	virtual void OnExtensionSelected(const wxString& selection) = 0;
	virtual void OnOutputDirChanged(const wxString& path) = 0;
	virtual void OnRun() = 0;
  virtual void OnCancelRun() = 0;
  virtual void OnNewProject() = 0;
  virtual SmartCache& GetSmartCache() = 0;
};

}

#endif /* UILISTENER_H_ */

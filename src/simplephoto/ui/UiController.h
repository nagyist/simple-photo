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
 * UiInterface.h
 *
 *  Created on: Jul 18, 2009
 *      Author: ruibm
 */

#ifndef UIINTERFACE_H_
#define UIINTERFACE_H_

#include <wx/wx.h>
#include <vector>

#include "simplephoto/ui/UiListener.h"

namespace simplephoto {

class CrawlerDialog;
class PhotoGroup;
class Project;
class RunDialog;
class SmartCache;

class UiController {
public:
	UiController() {}
	virtual ~UiController() {}

	virtual void SetListener(UiListener* listener) = 0;
	virtual UiListener* GetListener() = 0;
	virtual void SetSizes(const wxArrayString& sizes, unsigned int default_index) = 0;
	virtual void SetExtensions(const wxArrayString& extensions, unsigned int default_index) = 0;
	virtual void SetGroupers(const wxArrayString& groups, unsigned int default_index) = 0;
	virtual void Update(Project& project) = 0;
  virtual void SetCache(SmartCache& cache) = 0;
	virtual CrawlerDialog& GetCrawlerDialog() = 0;
	virtual RunDialog& GetRunDialog() = 0;
  virtual void SetRunEnabled(bool enabled) = 0;
};

}

#endif /* UIINTERFACE_H_ */

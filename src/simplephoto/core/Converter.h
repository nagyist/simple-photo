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
 * Converter.h
 *
 *  Created on: Jun 22, 2009
 *      Author: ruibm
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "simplephoto/core/Macros.h"

#include "wx/wx.h"
#include "wx/filename.h"

namespace simplephoto {

class Photo;
class Project;

class ConverterListener {
public:
  virtual ~ConverterListener() {}
  virtual void OnConvertSuccess(const Photo& original, const Photo& destination) = 0;
  virtual void OnConvertFail(const Photo& original) = 0;
};

class Converter {
public:
  Converter(const Project& project, ConverterListener& listener);
  ~Converter();

  void Convert();
  void Cancel();

private:
  void ConvertPhoto(Photo& photo, const wxString& root,
                    const wxString& group_name, const wxString& extension);
  bool MakeSureDirExists(wxFileName& path);
  wxString GetUnexistentRootPath(const wxString& original_root) const;

  const Project& m_project;
  ConverterListener& m_listener;
  volatile bool m_cancel;

	DISABLE_MAGIC_METHODS(Converter);
};

}

#endif /* CONVERTER_H_ */

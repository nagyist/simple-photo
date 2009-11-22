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
 * Converter.cpp
 *
 *  Created on: Jun 22, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/Converter.h"

#include "simplephoto/core/Bitmap.h"
#include "simplephoto/core/Log.h"
#include "simplephoto/core/Project.h"
#include "simplephoto/core/FsUtil.h"
#include "simplephoto/logic/ConversionOptions.h"

namespace simplephoto {

Converter::Converter(const Project& project, ConverterListener& listener)
    : m_project(project),
      m_listener(listener),
      m_cancel(false) {
}

Converter::~Converter() {
}

void Converter::Convert() {
  if (INVALID == m_project.GetFormat()) {
    return;
  }
  wxString extension = ConversionOptions::GetExtension(m_project.GetFormat());
  wxString root = GetUnexistentRootPath(m_project.GetOutputDir());
  for (int i = 0; !m_cancel && i < m_project.GetGroupCount(); ++i) {
    const PhotoGroup& group = m_project.GetGroup(i);
    wxString group_name = group.m_name;
    for (int j = 0; !m_cancel && j < group.m_photos.size(); ++j) {
      Photo& photo = *(group.m_photos[j]);      
      ConvertPhoto(photo, root, group_name, extension);
    }
  }

  if (m_cancel) {
    FsUtil::RmDir(root);
  }
}

wxString Converter::GetUnexistentRootPath(const wxString& original_root) const {
  wxFileName path(original_root, wxEmptyString);
  wxString prefix(wxT("SimplePhotoOutput"));
  path.AppendDir(prefix);
  int counter = 1;
  while(path.DirExists()) {
    path.RemoveLastDir();
    path.AppendDir(wxString::Format(wxT("%s%d"), prefix.c_str(), counter++));
    Log::d << "GetUnexistentRootPath Trying root " << path.GetFullPath() << Log::ENDL;
    assert(counter < 42);
  }
  return path.GetFullPath();
}

bool Converter::MakeSureDirExists(wxFileName& path) {
  wxFileName parent(path);
  parent.RemoveLastDir();
  if (parent.GetDirCount() > 0 && !parent.DirExists()) {
    if (!MakeSureDirExists(parent)) {
      return false;
    }
  }
  if (!path.DirExists()) {
    return path.Mkdir();
  }
  return true;
}

void Converter::ConvertPhoto(Photo& photo, const wxString& root,
                             const wxString& group_name, const wxString& extension) {  
  boost::scoped_ptr<Bitmap> bitmap(Bitmap::Read(photo.m_path.GetFullPath()));

  wxFileName output_path(root, photo.m_path.GetName());
  output_path.MakeAbsolute();
  output_path.AppendDir(group_name);
  output_path.SetExt(extension);
  if (!MakeSureDirExists(output_path)) {
      m_listener.OnConvertFail(photo);
      return;
  }

  if (bitmap.get() == NULL) {
    m_listener.OnConvertFail(photo);
    return;
  }
  if (!photo.IsSizeSet()) {
    photo.m_size = bitmap->GetSize();
  }
//  wxRect rect = m_project.HasPhotoCrop(photo) ?
//                m_project.GetPhotoCrop(photo) :
//                wxRect(wxPoint(-1, -1), m_project.GetResizer().GetSize(photo.m_size));
//  if (wxPoint(-1, -1) == rect.GetPosition()) {
//    bitmap->Scale(rect.GetSize());
//  } else {
//    bitmap->Crop(rect);
//  }

  const Resizer& resizer = m_project.GetResizer();
  if (resizer.NeedsCrop(photo.m_size)) {
    wxRect crop = m_project.HasPhotoCrop(photo) ?
                m_project.GetPhotoCrop(photo) :
                wxRect(wxPoint(0, 0), resizer.GetCropSize(photo.m_size));
    bitmap->Crop(crop);
  }

  if (resizer.NeedsRescale(photo.m_size)) {
    bitmap->Scale(resizer.GetScaleSize(photo.m_size));
  }

  if (!bitmap->Write(output_path.GetFullPath())) {    
    m_listener.OnConvertFail(photo);
    return;
  }
  Photo dest(output_path.GetFullPath());
  dest.m_size = bitmap->GetSize();
  m_listener.OnConvertSuccess(photo, dest);
  // Log::d << "ConvertPhoto to [" << output_path.GetFullPath() << "]." << Log::ENDL;
}

void Converter::Cancel() {
  m_cancel = true;
}

}

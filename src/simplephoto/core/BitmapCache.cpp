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
 * BitmapCache.cpp
 *
 *  Created on: Jul 19, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/BitmapCache.h"

#include <wx/wx.h>
#include <wx/file.h>
#include <map>

#include "simplephoto/core/Bitmap.h"
#include "simplephoto/core/FsUtil.h"
#include "simplephoto/core/Log.h"
#include "simplephoto/core/Resizer.h"
#include "simplephoto/core/TextUtil.h"

namespace {

wxSize GetSizeMaintainingRatio(const wxSize& original, const wxSize& desired) {
	const int ratio_diff = (original.x * desired.y) - (desired.x * original.y);
	if (ratio_diff == 0) {
		return desired;
	} else if (ratio_diff > 0) {
		return wxSize(desired.x * original.y / original.x, desired.y);
	} else {
		return wxSize(desired.x, desired.y * original.x / original.y);
	}
}

}  // namespace

namespace simplephoto {

const wxSize BitmapCache::CACHED_SIZE(210, 210);

BitmapCache::BitmapCache(const wxString& path, const wxString& name) {
	wxFileName root(path, wxEmptyString);
	root.AppendDir(name);
	if (wxFile::Exists(root.GetFullName())) {
		int count = 0;
		while (true) {
			root.RemoveLastDir();
			wxString new_name(name);
			new_name << count;
			root.AppendDir(new_name);
			if (!wxFile::Exists(root.GetFullName())) {
				break;
			}
		}
	}
	wxFileName::Mkdir(root.GetFullPath(), 0777, wxPATH_MKDIR_FULL);
	m_path = root;
  // Log::d << "BitmapCache in located at [" << m_path  << "]" << Log::ENDL;
}

BitmapCache::~BitmapCache() {
	FsUtil::RmDir(m_path.GetFullPath());
}

Bitmap* BitmapCache::GetBitmap(const wxString& file_path, const wxSize& size) {
	const wxString cache_file = GetCacheFilePath(file_path);
	if (!wxFile::Exists(cache_file)) {
		Cache(file_path, NULL);
	}
	Bitmap* bitmap = Bitmap::Read(cache_file);
	if (bitmap == NULL) {
    Log::d << "Could not read bitmap [" << cache_file << "]." << Log::ENDL;
		return NULL;
	}
	wxSize scaled_size = GetSizeMaintainingRatio(bitmap->GetSize(), size);
	if (scaled_size == bitmap->GetSize()) {
		return bitmap;
	}
	bitmap->Scale(scaled_size);
	return bitmap;
}

wxString BitmapCache::GetCacheFilePath(const wxString& path) {
  unsigned int hash_value = TextUtil::Hash(path);
	wxFileName file_path = m_path;
	file_path.SetName(wxString::Format(wxT("%u.png"), hash_value));
	return file_path.GetFullPath();
}

void BitmapCache::Clear() {
	FsUtil::RmDir(m_path.GetFullPath());
}

void BitmapCache::Cache(const wxString& file_path, Bitmap* original_bitmap) {
  scoped_ptr<Bitmap> bitmap(original_bitmap);
	if (bitmap.get() == NULL) {
		bitmap.reset(Bitmap::Read(file_path));
		if (bitmap.get() == NULL) {
			return;
		}
  }
	wxSize scaled_size = GetSizeMaintainingRatio(bitmap->GetSize(), CACHED_SIZE);
	bitmap->Scale(scaled_size);
	wxString cache_file = GetCacheFilePath(file_path);
	bitmap->Write(cache_file);
}

}

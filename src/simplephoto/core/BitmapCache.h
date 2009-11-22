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
 * BitmapCache.h
 *
 *  Created on: Jul 19, 2009
 *      Author: ruibm
 */

#ifndef BITMAPCACHE_H_
#define BITMAPCACHE_H_

#include <wx/wx.h>
#include <wx/filename.h>

#include "simplephoto/core/Bitmap.h"
#include "simplephoto/core/Photo.h"

namespace simplephoto {

class BitmapCache {
public:
	BitmapCache(const wxString& path, const wxString& name);
	virtual ~BitmapCache();

	// Takes ownership.
	void Cache(const wxString& file_path, Bitmap* bitmap);
	Bitmap* GetBitmap(const wxString& file_path, const wxSize& size);
	void Clear();

	const static wxSize CACHED_SIZE;

private:
	wxString GetCacheFilePath(const wxString& path);

	wxFileName m_path;
};

}

#endif /* BITMAPCACHE_H_ */

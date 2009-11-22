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
 * SmartCache.h
 *
 *  Created on: Oct 11, 2009
 *      Author: ruibm
 */

#ifndef SMARTCACHE_H
#define SMARTCACHE_H

#include "simplephoto/core/BitmapCache.h"
#include "simplephoto/core/LruCache.h"

#include <wx/wx.h>

namespace simplephoto {

class SmartCache {
public:
  explicit SmartCache(int max_in_memory_photos, const wxSize& cached_thumbnail_size);

  wxBitmap* Get(const wxString& path);
  BitmapCache& GetBitmapCache() { return *m_bitmap_cache.get(); }

private:
  LruCache<unsigned int, wxBitmap> m_lru_cache;
  boost::scoped_ptr<BitmapCache> m_bitmap_cache;
  const wxSize m_cached_thumbnail_size;
};

}  // namespace simplephoto

#endif // SMARTCACHE_H

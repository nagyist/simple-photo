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
 * SmartCache.cpp
 *
 *  Created on: Oct 11, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/BitmapCache.h"
#include "simplephoto/core/SmartCache.h"
#include "simplephoto/core/TextUtil.h"

#include <wx/stdpaths.h>

namespace simplephoto {

SmartCache::SmartCache(int max_in_memory_photos, const wxSize& cached_thumbnail_size)
    : m_lru_cache(max_in_memory_photos),
      m_cached_thumbnail_size(cached_thumbnail_size) {
  wxString cache_path = wxStandardPaths::Get().GetTempDir();
  m_bitmap_cache.reset(new BitmapCache(cache_path, wxT("SimplePhotoCache")));
}

wxBitmap* SmartCache::Get(const wxString& path) {
  assert(!path.IsEmpty());
  unsigned int h = TextUtil::Hash(path);
  wxBitmap* bitmap = m_lru_cache.Get(h);
  if (bitmap != NULL) {
    return bitmap;
  }
  boost::scoped_ptr<Bitmap> tmp_bmp(
      m_bitmap_cache->GetBitmap(path, m_cached_thumbnail_size));
  if (tmp_bmp.get() == NULL) {
    return NULL;
  }
  bitmap = tmp_bmp->CreateWxBitmap();
  m_lru_cache.Put(h, bitmap);
  return bitmap;
}

}  // namespace simplephoto

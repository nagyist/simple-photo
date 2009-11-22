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
 * Bitmap.h
 *
 *  Created on: Apr 30, 2009
 *      Author: ruibm
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include "simplephoto/core/Macros.h"

namespace Magick {
class Image;
}
class wxBitmap;
class wxColour;
class wxRect;
class wxSize;
class wxString;

namespace simplephoto {

class Bitmap {
public:
	virtual ~Bitmap();

	wxRect GetLargestGradient(const wxSize& ratio) const;
	wxSize GetSize() const;
	wxBitmap* CreateWxBitmap();
	void Crop(const wxRect& crop);
	void Scale(const wxSize& size);
	bool Write(const wxString& path);
  wxColour GetPixel(int x, int y) const;

	static Bitmap* Read(const wxString& path);

private:
	Bitmap(Magick::Image* image);

	scoped_ptr<Magick::Image> m_image;
};

}

#endif /* BITMAP_H_ */

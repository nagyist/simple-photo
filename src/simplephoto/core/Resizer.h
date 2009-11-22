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
 * Resizer.h
 *
 *  Created on: Jun 28, 2009
 *      Author: ruibm
 */

#ifndef RESIZER_H_
#define RESIZER_H_

#include "simplephoto/core/Macros.h"

#include <wx/wx.h>

namespace simplephoto {

// Crop should always be applied to the original image. Scaling comes second.
class Resizer {
public:
	enum Type {
		NONE,   // Causes no changes to the original size.
		RATIO,  // Makes sure the image is cropped to ratio but uses the maximum possible size.
		PIXELS  // Makes sure the image is rescaled and cropped in order to match the exact pixel size.
	};

	Resizer();
  Resizer(Type type, const wxSize& desired_size);
	virtual ~Resizer();

	bool NeedsCrop(const wxSize& size) const;
	bool NeedsRescale(const wxSize& size) const;
  wxSize GetCropSize(const wxSize& size) const;
  wxSize GetScaleSize(const wxSize& size) const;
  wxString ToString() const;

private:
	Type m_type;
	wxSize m_size;
};

}

#endif /* RESIZER_H_ */

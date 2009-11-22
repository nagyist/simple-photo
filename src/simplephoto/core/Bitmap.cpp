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
 * Bitmap.cpp
 *
 *  Created on: Apr 30, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/Bitmap.h"

#include <Magick++.h>
#include <wx/wx.h>
#include <iostream>
#include <wx/colour.h>
#include <wx/filename.h>

#include "simplephoto/core/GradientCalculator.h"
#include "simplephoto/core/Log.h"

namespace {
const int MAX_BYTE  = 0x000000ff;
const int MAX_WORD  = 0x000000ff;
}

namespace simplephoto {

Bitmap::Bitmap(Magick::Image* image) : m_image(image) {
	assert(image != NULL);
}

Bitmap::~Bitmap() {
}

wxSize Bitmap::GetSize() const {
	assert(m_image != NULL);
	return wxSize(m_image->columns(), m_image->rows());
}

wxBitmap* Bitmap::CreateWxBitmap() {
  assert(m_image.get() != NULL);
  wxImage tmpImage(m_image->columns(), m_image->rows());
  const Magick::PixelPacket* packet = m_image->getConstPixels(0, 0,
      m_image->columns(), m_image->rows());
  unsigned char* pixels = tmpImage.GetData();
  tmpImage.InitAlpha();
  unsigned char* alpha = tmpImage.GetAlpha();
  for (int x = 0; x < tmpImage.GetWidth(); ++x) {
    for (int y = 0; y < tmpImage.GetHeight(); ++y) {
      // packet->red == short
      // pixels == byte
      *(pixels++) = static_cast<unsigned char>(packet->red * MAX_BYTE / MAX_WORD);
      *(pixels++) = static_cast<unsigned char>(packet->green * MAX_BYTE / MAX_WORD);
      *(pixels++) = static_cast<unsigned char>(packet->blue * MAX_BYTE / MAX_WORD);
      *(alpha++) = static_cast<unsigned char>(MAX_BYTE - packet->opacity * MAX_BYTE / MAX_WORD);
      // *(alpha - 1) = 100;
      ++packet;
    }
  }
  return new wxBitmap(tmpImage);
}

Bitmap* Bitmap::Read(const wxString& path) {
  if (!wxFileName::FileExists(path)) {	  
    // Log::d << "Could not find image " << path.mb_str() << Log::ENDL;
    return NULL;
  }
	auto_ptr<Magick::Image> bitmap(new Magick::Image());
  try {
    // Log::d << "About to read and image " << path.mb_str() << Log::ENDL;
    bitmap->read(C_STR(path));
  } catch (Magick::Exception & error) {
    Log::d << "Exception reading image "  << path.mb_str() << " what=" << error.what() << Log::ENDL;
		return NULL;
  }
  // Log::d << "Image read successfully." << Log::ENDL;
  return new Bitmap(bitmap.release());
}

void Bitmap::Scale(const wxSize& size) {
	assert(m_image.get() != NULL);
	if (size.x <= 0 || size.y <= 0) {
		return;
	}
	Magick::Geometry geometry(size.x, size.y);
	geometry.aspect(true);
	geometry.percent(false);
	geometry.greater(false);
	geometry.less(false);
	m_image->scale(geometry);
}

bool Bitmap::Write(const wxString& path) {
  try {
    m_image->write(C_STR(path));
		return true;
	} catch (...) {
		return false;
	}
}

void Bitmap::Crop(const wxRect& crop) {
	assert(m_image.get() != NULL);
	wxSize size = GetSize();
	wxRect real_crop = crop.Intersect(wxRect(0, 0, size.x, size.y));
	if (real_crop.IsEmpty()) {
		return;
	}
	Magick::Geometry geo(real_crop.width, real_crop.height,
			real_crop.x, real_crop.y);
  m_image->crop(geo);
}

wxRect Bitmap::GetLargestGradient(const wxSize& ratio) const {
	GradientCalculator calculator(*m_image);
	return calculator.GetLargestGradient(ratio);
}

wxColour Bitmap::GetPixel(int x, int y) const {
  assert(m_image.get() != NULL);
  Magick::Color color = m_image->pixelColor(x, y);
  return wxColour(
      color.redQuantum(),
      color.greenQuantum(),
      color.blueQuantum(),
      255 - color.alphaQuantum());
}

} // namespace simplephoto

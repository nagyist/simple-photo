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
 * GradientCalculator.h
 *
 *  Created on: May 18, 2009
 *      Author: ruibm
 */

#ifndef GRADIENTCALCULATOR_H_
#define GRADIENTCALCULATOR_H_

#include <Magick++.h>
#include <wx/wx.h>

namespace simplephoto {

class GradientCalculator {
public:
	GradientCalculator(Magick::Image& image);

	wxRect GetLargestGradient(const wxSize& ratio) const;

private:
	int GetGradient(const Magick::PixelPacket& p1, const Magick::PixelPacket& p2) const;
	const Magick::PixelPacket* GetPixel(int x, int y) const;
	int GetPixelGradient(int x, int y) const;
	int GetColumnGradient(int column) const;
	int GetRowGradient(int row) const;
	wxSize GetMaxSize(const wxSize& ratio) const;
	wxRect GetCroppedWidth(const wxSize new_size) const;
	wxRect GetCroppedHeight(const wxSize new_size) const;

	const Magick::PixelPacket* m_pixels;
	wxSize m_size;
};

}

#endif /* GRADIENTCALCULATOR_H_ */

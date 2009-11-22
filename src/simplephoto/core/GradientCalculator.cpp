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
 * GradientCalculator.cpp
 *
 *  Created on: May 18, 2009
 *      Author: ruibm
 */

#include "simplephoto/core/GradientCalculator.h"

#include <cmath>

using Magick::PixelPacket;

namespace simplephoto {

GradientCalculator::GradientCalculator(Magick::Image& image) {
	m_pixels = image.getConstPixels(0, 0, image.columns(), image.rows());
	m_size.Set(image.columns(), image.rows());
}

wxRect GradientCalculator::GetLargestGradient(const wxSize& ratio) const {
	assert(ratio.x > 0);
	assert(ratio.y > 0);
	if (ratio.x * m_size.y > m_size.x * ratio.y) {
		return GetCroppedHeight(wxSize(m_size.x, m_size.x * ratio.y / ratio.x));
	} else {
		return GetCroppedWidth(wxSize(m_size.y * ratio.x / ratio.y, m_size.y));
	}
}

wxRect GradientCalculator::GetCroppedWidth(const wxSize new_size) const {
	int left = 0;
	int right = m_size.x - 1;
	int left_gradient = -1;
	int right_gradient = -1;
	for (int columns_to_crop = m_size.x - new_size.x; columns_to_crop > 0; --columns_to_crop) {
		if (left_gradient == -1) {
			left_gradient = GetColumnGradient(left);
		}
		if (right_gradient == -1) {
			right_gradient = GetColumnGradient(right);
		}
		if (right_gradient > left_gradient) {
			++left;
			left_gradient = -1;
		} else {
			--right;
			right_gradient = -1;
		}
	}
	return wxRect(left, 0, new_size.x, new_size.y);
}

wxRect GradientCalculator::GetCroppedHeight(const wxSize new_size) const {
	int bottom = 0;
	int top = m_size.y - 1;
	int bottom_gradient = -1;
	int top_gradient = -1;
	for (int rows_to_crop = m_size.y - new_size.y; rows_to_crop > 0; --rows_to_crop) {
		if (bottom_gradient == -1) {
			bottom_gradient = GetRowGradient(bottom);
		}
		if (top_gradient == -1) {
			top_gradient = GetRowGradient(top);
		}
		if (top_gradient > bottom_gradient) {
			++bottom;
			bottom_gradient = -1;
		} else {
			--top;
			top_gradient = -1;
		}
	}
	return wxRect(0, bottom, new_size.x, new_size.y);
}

int GradientCalculator::GetGradient(const PixelPacket& p1, const PixelPacket& p2) const {
	return
			std::abs(p2.red - p1.red) +
			std::abs(p2.green - p1.green) +
			std::abs(p2.blue - p1.blue) +
			std::abs(p2.opacity - p1.opacity);
}

const PixelPacket* GradientCalculator::GetPixel(int x, int y) const {
	if (x < 0 || y < 0 || x >= m_size.GetWidth() || y >= m_size.GetHeight()) {
		return NULL;
	}
	return &m_pixels[x + (y * m_size.GetWidth())];
}

int GradientCalculator::GetPixelGradient(int x, int y) const {
	int gradient = 0;
	const PixelPacket* p1 = GetPixel(x, y);
	assert(p1 != NULL);
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			const PixelPacket* p2 = GetPixel(x + i, y + j);
			if (p2 != NULL) {
				gradient += GetGradient(*p1, *p2);
			}
		}
	}
	return gradient;
}

int GradientCalculator::GetColumnGradient(int column) const {
	int gradient = 0;
	for (int i = 0; i < m_size.y; ++i) {
		gradient += GetPixelGradient(column, i);
	}
	return gradient;
}

int GradientCalculator::GetRowGradient(int row) const {
	int gradient = 0;
	for (int i = 0; i < m_size.x; ++i) {
		gradient += GetPixelGradient(i, row);
	}
	return gradient;
}

wxSize GradientCalculator::GetMaxSize(const wxSize& ratio) const {
	wxSize size = m_size;
	float desired_ratio = static_cast<float>(ratio.x) / ratio.y;
	float current_ratio = static_cast<float>(size.x) / size.y;
	if (current_ratio > desired_ratio) {
		size.x = size.y * desired_ratio;
	} else {
		size.y = size.x / desired_ratio;
	}
	return size;
}

}

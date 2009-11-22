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
 * ConversionOptions.cpp
 *
 *  Created on: Jul 26, 2009
 *      Author: ruibm
 */

#include "simplephoto/logic/ConversionOptions.h"

#include "simplephoto/core/Extension.h"
#include "simplephoto/core/Resizer.h"
#include "simplephoto/core/SimpleGrouper.h"

namespace {

using namespace simplephoto;

struct ResizerOption {
	wxString name;
	Resizer resizer;
};

const ResizerOption RESIZERS[] = {
    { wxString(wxT("None")), Resizer(Resizer::NONE, wxSize()) },
    { wxString(wxT("1600x1200")), Resizer(Resizer::PIXELS, wxSize(1600, 1200)) },
    { wxString(wxT("1024x768")), Resizer(Resizer::PIXELS, wxSize(1024, 768)) },
    { wxString(wxT("800x600")), Resizer(Resizer::PIXELS, wxSize(800, 600)) },
    { wxString(wxT("640x480")), Resizer(Resizer::PIXELS, wxSize(640, 480)) },
    { wxString(wxT("320x240")), Resizer(Resizer::PIXELS, wxSize(320, 240)) },
    { wxString(wxT("160x120")), Resizer(Resizer::PIXELS, wxSize(160, 120)) },
		{ wxString(wxT("16:9")), Resizer(Resizer::RATIO, wxSize(16, 9)) },
		{ wxString(wxT("4:3")), Resizer(Resizer::RATIO, wxSize(4, 3)) },
};

struct ExtensionOption {
	wxString name;
	Extension extension;
};

const ExtensionOption EXTENSIONS[] = {
    { wxString(wxT("png")), PNG },
    { wxString(wxT("tiff")), TIFF },
    { wxString(wxT("gif")), GIF },
    { wxString(wxT("jpg")), JPG },
    { wxString(wxT("bmp")), BMP },
};

struct GrouperOption {
	wxString name;
	Grouper* grouper;
};

// TODO(ruibm): This heap memory is never released.
const GrouperOption GROUPERS[] = {
		{ wxString(wxT("None")), new SimpleGrouper(SimpleGrouper::NONE) },
		{ wxString(wxT("Directory")), new SimpleGrouper(SimpleGrouper::DIR) },
		{ wxString(wxT("Day")), new SimpleGrouper(SimpleGrouper::DAY) },
};

}  // namespace


namespace simplephoto {

void ConversionOptions::GetResizers(wxArrayString& out) {
	out.Clear();
	for (unsigned int i = 0; i < ARRAY_SIZE(RESIZERS); ++i) {
		out.push_back(RESIZERS[i].name);
	}
}

const Resizer* ConversionOptions::GetResizer(const wxString& in) {
	for (unsigned int i = 0; i < ARRAY_SIZE(RESIZERS); ++i) {
		const ResizerOption& option = RESIZERS[i];
		if (option.name == in) {
			return &option.resizer;
		}
	}
	return NULL;
}

void ConversionOptions::GetExtensions(wxArrayString& out) {
	out.Clear();
	for (unsigned int i = 0; i < ARRAY_SIZE(EXTENSIONS); ++i) {
		out.push_back(EXTENSIONS[i].name);
	}
}

Extension ConversionOptions::GetExtension(const wxString& in) {
	for (unsigned int i = 0; i < ARRAY_SIZE(EXTENSIONS); ++i) {
		const ExtensionOption& option = EXTENSIONS[i];
		if (option.name == in) {
			return option.extension;
		}
	}
	return INVALID;
}

wxString ConversionOptions::GetExtension(Extension extension) {
  for (unsigned int i = 0; i < ARRAY_SIZE(EXTENSIONS); ++i) {
    const ExtensionOption& option = EXTENSIONS[i];
    if (option.extension == extension) {
      return option.name;
    }
  }
  return wxString();
}

void ConversionOptions::GetGroupers(wxArrayString& out) {
	out.Clear();
	for (unsigned int i = 0; i < ARRAY_SIZE(GROUPERS); ++i) {
		out.push_back(GROUPERS[i].name);
	}
}

const Grouper* ConversionOptions::GetGrouper(const wxString& in) {
	for (unsigned int i = 0; i < ARRAY_SIZE(GROUPERS); ++i) {
		const GrouperOption& option = GROUPERS[i];
		if (option.name == in) {
			return option.grouper;
		}
	}
	return NULL;
}

}

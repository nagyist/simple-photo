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
 * FsUtil.h
 *
 *  Created on: Jul 19, 2009
 *      Author: ruibm
 */

#ifndef FSUTIL_H_
#define FSUTIL_H_

#include <wx/wx.h>

namespace simplephoto {

class FsUtil {
public:
	virtual ~FsUtil() {}

	static bool RmDir(const wxString& path);

private:
	FsUtil() {}
};

}

#endif /* FSUTIL_H_ */

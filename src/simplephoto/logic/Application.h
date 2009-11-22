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
 * Application.h
 *
 *  Created on: Jul 10, 2009
 *      Author: ruibm
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <wx/wx.h>
#include <wx/app.h>

#include "simplephoto/core/Macros.h"
#include "simplephoto/core/SmartCache.h"

namespace simplephoto {

class Frame;
class LogicCore;
class UiThreadRunner;

class Application : public wxApp {
public:
	Application();
	virtual ~Application();

	virtual bool OnInit();
	virtual int OnExit();

private:
	Frame* m_frame;
  SmartCache m_cache;
  boost::scoped_ptr<UiThreadRunner> m_runner;
  boost::scoped_ptr<LogicCore> m_core;

	DISABLE_MAGIC_METHODS(Application);
};

}

#endif /* APPLICATION_H_ */

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
 * Log.h
 *
 *  Created on: Jul 15, 2009
 *      Author: ruibm
 */

#ifndef LOG_H_
#define LOG_H_

#include <wx/wx.h>
#include <map>

class wxFileName;

namespace simplephoto {

class Log {
public:
	class Type {
	public:
		Type() {}
	};

	class Out {
	public:
		virtual ~Out() {}
		virtual void Write(const wxString& message);
	};

	virtual ~Log();

	void SetOut(Out* out);
	Log& operator<<(const wxString& message);
	Log& operator<<(const int& message);
	Log& operator<<(const char* message);
	Log& operator<<(const Type& message);
	Log& operator<<(const wxWindow* message);
	Log& operator<<(const wxFileName& message);
	Log& operator<<(const wxPoint& message);
	Log& operator<<(const wxRect& message);

	static Log d;
	static Out std_out;
	const static Type ENDL;

private:
	Log();

	void Append(const wxString& text);
	wxString& text();

	std::map<int, wxString> m_text;
	wxMutex m_mutex;
	Out* m_out;
};

}

#endif /* LOG_H_ */

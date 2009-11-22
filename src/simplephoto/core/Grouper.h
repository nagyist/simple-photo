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
 * Grouper.h
 *
 *  Created on: Jun 9, 2009
 *      Author: ruibm
 */

#ifndef GROUPER_H_
#define GROUPER_H_

#include <vector>

namespace simplephoto {

class Photo;
class PhotoGroup;

class Grouper {
public:
	virtual ~Grouper() {}

	virtual void Group(std::vector<Photo*>& in, std::vector<PhotoGroup*>& out) = 0;
  virtual Grouper* Clone() const = 0;
};

}

#endif /* GROUPER_H_ */

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
 * SimpleGrouper.h
 *
 *  Created on: Jun 9, 2009
 *      Author: ruibm
 */

#ifndef SIMPLEGROUPER_H_
#define SIMPLEGROUPER_H_

#include "simplephoto/core/Grouper.h"

namespace simplephoto {

class SimpleGrouper : public Grouper {
public:
	enum Type {
		NONE,
		DIR,
		DAY
	};

	explicit SimpleGrouper(Type type);
	virtual ~SimpleGrouper() {}

	virtual void Group(std::vector<Photo*>& in, std::vector<PhotoGroup*>& out);
  virtual Grouper* Clone() const;

private:
	Type m_type;
};

}

#endif /* SIMPLEGROUPER_H_ */

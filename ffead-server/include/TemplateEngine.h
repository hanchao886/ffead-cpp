/*
	Copyright 2009-2012, Sumeet Chhetri 
  
    Licensed under the Apache License, Version 2.0 (the "License"); 
    you may not use this file except in compliance with the License. 
    You may obtain a copy of the License at 
  
        http://www.apache.org/licenses/LICENSE-2.0 
  
    Unless required by applicable law or agreed to in writing, software 
    distributed under the License is distributed on an "AS IS" BASIS, 
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
    See the License for the specific language governing permissions and 
    limitations under the License.  
*/
/*
 * TemplateEngine.h
 *
 *  Created on: Sep 5, 2009
 *      Author: sumeet
 */

#ifndef TEMPLATEENGINE_H_
#define TEMPLATEENGINE_H_
#include "string"
#include "map"
#include "StringUtil.h"
#include "Object.h"
#include <fstream>
#include <iostream>
using namespace std;

typedef map<string,Object> Context;
typedef map<string,string> StringContext;
class TemplateEngine {
public:
	TemplateEngine();
	virtual ~TemplateEngine();
	string evaluate(string,StringContext);
	//string evaluateTemplate(string,Context);
};

#endif /* TEMPLATEENGINE_H_ */
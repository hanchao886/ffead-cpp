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
 * TestPage.cpp
 *
 *  Created on: Jul 13, 2011
 *      Author: sumeet
 */

#include "TestPage.h"

TestPage::TestPage() {
	// TODO Auto-generated constructor stub

}

TestPage::~TestPage() {
	// TODO Auto-generated destructor stub
}

std::string TestPage::textonclick(int a,std::string b,std::string c)
{
	return "Test Successfull" + b + c;
}

int TestPage::linkonclick()
{
	return 12345;
}


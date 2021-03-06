/*
Dmscanlib is a software library and standalone application that scans 
and decodes libdmtx compatible test-tubes. It is currently designed 
to decode 12x8 pallets that use 2D data-matrix laser etched test-tubes.
Copyright (C) 2010 Canadian Biosample Repository

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "utils/DmTime.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
//#include <sys/timeb.h>

namespace dmscanlib {

namespace util {

DmTime::DmTime() {
	time(&timeVal);
}

DmTime::DmTime(DmTime & that) {
	this->timeVal = that.timeVal;
}

std::unique_ptr<DmTime> DmTime::difftime(const DmTime & that) {
	std::unique_ptr<DmTime> result(new DmTime(*this));
	result->timeVal = this->timeVal - that.timeVal;
	return result;
}

double DmTime::getTime() {
	return static_cast<float>(timeVal);
}

} /* namespace */

} /* namespace */

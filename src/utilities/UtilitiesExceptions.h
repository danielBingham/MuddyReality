/***********************************************************************************
 * File: UtilitiesExceptions.h
 * Definition:
 *
 * Contents:
 *
 *
 * Copyright:
 *		Copyright (C) 2009-2011 Daniel Bingham (http://www.theroadgoeson.com)
 *
 * License:
 *
 * This software is licensed under the MIT Open Source License which reads as
 * follows:
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information see here: http://www.opensource.org/licenses/mit-license.php
 *
 ***********************************************************************************/
#ifndef UTILITIESEXCEPTIONS_H_
#define UTILITIESEXCEPTIONS_H_

#include "Datatypes.h"

class LogException {
	public:
		LogException() {
			message = "Uknown error occurred in the Log system.";
		}
		LogException(String m) {
			message = m;
		}
		String message;

};
class LogFileCreationException: public LogException {
	public:
		LogFileCreationException() {
			message = "Failed to create log file.";
		}
		LogFileCreationException(String m) {
			message = m;
		}
};
class LogFileNotFoundException: public LogException {
	public:
		LogFileNotFoundException() {
			message = "Failed to find a log file.";
		}
		LogFileNotFoundException(String m) {
			message = m;
		}
};

#endif /* UTILITIESEXCEPTIONS_H_ */

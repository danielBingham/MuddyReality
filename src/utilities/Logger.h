/***********************************************************************************
 * File: Logger.h
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

#ifndef LOGGER_H_
#define LOGGER_H_

#include <cstdarg>
#include "Datatypes.h"

void initializeLog();
void destroyLog();

class Log {
	public:
		Log(String t);
		~Log();

		void vlog(char *buffer, va_list args);

		String type;

	private:
		void createLog();

		FILE *logFile;
};

class Logger {
	public:
		Logger();
		~Logger();

		String getTime();

		void add(String type);
		void remove(String type);

		void log(String message, ...);
		void tlog(String type, String message, ...);

	private:
		void vlog(String type, String message, va_list args);
		Log *get(String type);
		int getLogNum(String type);
		void order();

		Log **logs;
		int numberOfLogs;
};

#ifndef LOGGER_CPP_

extern Logger *log;

#endif // LOGGER_CPP_

#endif /* LOGGER_H_ */

/***********************************************************************************
 * File: logger.cpp
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

#ifndef LOGGER_CPP_
#define LOGGER_CPP_

#include <ctime>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

#include "Datatypes.h"

#include "Logger.h"
#include "Utilities.h"
#include "UtilitiesExceptions.h"

/********************************************************************************
 * Log Functions
 ********************************************************************************/

Logger *log;

String logs[] = {
		"engine",
		"socket"
};
const int numberOfLogs = 2;

/**
 * Initialize the log and handle any exceptions that occurr in the attempt to start it.
 * Any exceptions caught are fatal, so exit on an error.
 */
void initializeLog() {
	try {
		log = new Logger();
		log->log("Logger has been created, it is now being initialized with the configured logs.");
	}
	catch (LogException ex) {
		printf("Fatal exception occurred while attempting to initialize the system log.\n");
		printf("Exception caught was: %s\n", ex.message.c_str());
		Exit(1);
	}

	for(int i = 0; i < numberOfLogs; i++) {
		try {
			log->log("Adding log %s.", logs[i].c_str());
			log->add(logs[i]);
		}
		catch (LogException ex) {
			log->log("Failed to add log %s for the following reason: %s.", ex.message.c_str());
		}
	}
}

/**
 * Destroy the log.
 */
void destroyLog() {
	log->log("Destroying the logger.");
	if (log)
		delete log;
}

/********************************************************************************
 * Log
 ********************************************************************************/

Log::Log(String t) {
	type = t;
	createLog();
}

Log::~Log() {
	fclose(logFile);
	logFile = 0;
}

void Log::vlog(char *buffer, va_list args) {
	vfprintf(logFile, buffer, args);
	fflush(logFile);
}

void Log::createLog() {
	char filename[256];
	const char *t = type.c_str();

	if (!t) {
		String message = "Unable to create a log file for a non-existant type.";
		throw LogFileCreationException(message);
	}

	snprintf(filename, 256, "log/%s.log", t);

	if (!(logFile = fopen(filename, "a"))) {
		String message = "Unable to create log file for " + type + ".";
		throw LogFileCreationException(message);
	}
}

/********************************************************************************
 * Logger
 ********************************************************************************/

// Initialize the logger and add the system log Syslog.
Logger::Logger() {
	logs = 0;
	numberOfLogs = 0;
	add("syslog");
}

// Destroy the logger and all contained logs.
Logger::~Logger() {
	for (int i = 0; i < numberOfLogs; i++)
		if (logs[i])
			delete logs[i];
	if (logs != 0)
		delete[] logs;
}

// Add a new log to the logger with identifier and name 'type'.
// This works fine if there are no logs in the logger yet.
void Logger::add(String type) {
	if (numberOfLogs == 0) {
		logs = new Log *[1];
		logs[0] = new Log(type);
		numberOfLogs = 1;
		return;
	}

	if (numberOfLogs == 1) {
		Log *tmp = *logs;
		delete logs;

		logs = new Log *[numberOfLogs + 1];
		logs[0] = tmp;

	}

	if (numberOfLogs > 1) {
		Log **tmp = new Log *[numberOfLogs];

		for (int index = 0; index < numberOfLogs; index++) {
			tmp[index] = logs[index];
		}

		delete[] logs;
		logs = new Log *[numberOfLogs + 1];

		for (int index = 0; index < numberOfLogs; index++) {
			logs[index] = tmp[index];
		}
		delete[] tmp;

	}

	try {
		logs[numberOfLogs] = new Log(type);
	}
	catch (...) {
		throw ;
	}

	numberOfLogs++;

	order();
}

// Remove a log from the logger.
void Logger::remove(String type) {
	if (numberOfLogs <= 0)
		throw LogException("No more logs left!");
	else if (type == "syslog")
		throw LogException("Removal of syslog is forbidden.");

	int logNum = getLogNum(type);
	delete logs[logNum];
	numberOfLogs--;

	if (numberOfLogs == 0) {
		delete[] logs;
		logs = 0;
	}
	else {
		Log **tmp = new Log *[numberOfLogs];

		for (int index = 0; index < numberOfLogs; index++) {
			if (index < logNum)
				tmp[index] = logs[index];
			else
				tmp[index] = logs[index + 1];
		}

		delete[] logs;
		logs = new Log *[numberOfLogs];

		for (int index = 0; index < numberOfLogs; index++)
			logs[index] = tmp[index];

		delete[] tmp;
	}

}

// Log a message - just logs it to syslog.
void Logger::log(String message, ...) {
	va_list args;

	va_start(args, message);

	vlog("syslog", message, args);

	va_end(args);
}

// Log a message to the log given in type.
void Logger::tlog(String type, String message, ...) {
	va_list args;

	va_start(args, message);

	vlog("syslog", message, args);
	vlog(type, message, args);

	va_end(args);
}

// Log the message to the log of the given type with the given arguments.
void Logger::vlog(String type, String message, va_list args) {
	String time = getTime();

	String output = time + ":: " + message;
	char *buffer = new char[output.length() + 2];

	snprintf(buffer, output.length() + 2, "%s\n", output.c_str());

	if (type == "syslog")
		vprintf(buffer, args);

	get(type)->vlog(buffer, args);

	delete[] buffer;
}

// Get a time stamp.
String Logger::getTime() {
	char buffer[256];

	time_t secs;
	time(&secs);

	snprintf(buffer, sizeof(buffer), "%s", ctime(&secs));

	String t = String(buffer);

	while (t.find("\n") != String::npos) {
		t.erase(t.find("\n"), 1);
	}

	return t;
}

// Get a log given the type.
int Logger::getLogNum(String type) {
	int bottom, middle, top;

	bottom = 0;
	top = numberOfLogs;

	while (true) {
		if (bottom > top)
			throw LogFileNotFoundException("Log file, " + type + ", was not found.");

		middle = (bottom + top) / 2;

		if (logs[middle]->type == type)
			return middle;
		else if (type < logs[middle]->type)
			top = middle - 1;
		else
			bottom = middle + 1;
	}
}

// Get a log in the logger given the type.
Log *Logger::get(String type) {
	try {
		return logs[getLogNum(type)];
	}
	catch (...) {
		throw ;
	}

}

// Organize the logs in the logger by type.
void Logger::order() {
	int inner, outer;
	Log *tmp = 0;

	for (outer = 1; outer < numberOfLogs; outer++) {
		inner = outer;
		tmp = logs[inner];
		while (inner > 0 && tmp->type < logs[inner - 1]->type) {
			logs[inner] = logs[inner - 1];
			inner--;
		}
		logs[inner] = tmp;
	}
}

#endif // LOGGER_CPP_

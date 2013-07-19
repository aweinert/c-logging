/* Copyright 2013 Alexander Weinert, Markus Joppich */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License or under the
 * terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * and the GNU Lesser General Public License along with this program. 
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
 * der GNU General Public License oder unter den Bedingungen der GNU Lesser
 * General Public License, wie von der Free Software Foundation, Version 3
 * der Lizenz oder (nach Ihrer Option) jeder späteren veröffentlichten
 * Version, weiterverbreiten und/oder modifizieren.
 *
 * Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
 * OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 * Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 * Siehe die GNU General Public License für weitere Details.
 *
 * Sie sollten eine Kopie der GNU General Public License und der GNU Lesser
 * General Public License  zusammen mit diesem Programm erhalten haben.
 * Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 */

/**
 * \file   logging.c
 * \date   June, 2013
 * \brief  Time measurement and logging
 * \author Alexander Weinert, Markus Joppich
 */
#include "logging.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

/** The time at which logging_reset_timer was last called.
 * This way we get a fixed time as a base for all timestamps */
static time_t tStartTime;

// ////////////
// PUBLIC FUNCTION DECLARATION
// ////////////

static const char * get_log_level_name(log_level level);

// ////////////
// PUBLIC FUNCTION DEFINITION
// ////////////

/** \brief Resets the timestamp to 0.0s.
 *    All future log messages will have the difference from this time as timestamp */
void logging_reset_timer(void) {
	/* The current time is returned by time(...) as well as written into the
	 * object given as an argument. We simply use the return value here. */
	tStartTime = time(NULL);
}

/**
* \brief Prints the given message to the appropriate log-sink
* \param pFile The name of the file from which the message originates
* \param iLine The line in the given file from which the message originates
* \param level The warning level of the given message. Can be used to highlight more important messages (not yet implemented)
* \param pMessage The printf-format string of the message to be logged
* \param ... The parameters for the given printf-format string
*
* The logged message will have the form 
*   [ LEVEL ] [ TIME ] message (at FILE:LINE)
*
* Currently all DEBUG- and STATUS-messages are written to stdout, all other
* messages to stderr. We may expose functions to adjust this in the future,
* log to files and maybe even ignore some levels entirely.  */
void logging_log_message_file_line(const char* pFile, int iLine, log_level level, const char *pMessage, ...) {
	// Get the difference between the current time and the last reset of the timer.
	const time_t tCurrentTime = time(NULL);
	const double dNow = difftime(tCurrentTime, tStartTime);
	// Get the c-string representation of the given level
	const char *pLevelName = get_log_level_name(level);

	// Get the appropriate output sink
	FILE *pOutput = NULL;
	if(level <= WARNING) {
		pOutput = stdout;
	}
	else {
		pOutput = stderr;
	}

	// Get the arguments for the printf-format string
	va_list arguments;
	va_start(arguments, pMessage);

	// Print log level and timestamp
	fprintf(pOutput, "[ %s ] [ %.5f ] ", pLevelName, dNow);
	// Print the actual message
	vfprintf(pOutput, pMessage, arguments);
	// Print the location where the message originated
	fprintf(pOutput, " (at %s:%u)\n", pFile, iLine);

	// Clean up
	va_end(arguments);
}

/** \brief Print a naked timestamp, without logging level and point of origin
 *
 * Is currently only used at the end of the program to print the complete
 * runtime for easier measurement. */
void logging_print_timestamp(void) {
	const time_t tCurrentTime = time(NULL);
	const double dNow = difftime(tCurrentTime, tStartTime);

	fprintf(stdout, "%.5f\n", dNow);
}

// ////////////
// PRIVATE FUNCTION DEFINITION
// ////////////

/**
* \brief Returns a c-string representation of the given level.
*/
static const char * get_log_level_name(log_level level) {
	// Get a c-string description of the given log-level
	const char *pLevelName = NULL;
	// TODO: Left align the levels, with leading whitespace
	/* TODO: Find a workaround so that we do not have to list all names explicitely.
	 *   Idea: C# has something like level.getName - maybe use some compiler magic for this? */
	switch(level) {
		case DEBUG: {
			pLevelName = " DEBUG ";
			break;
		}
		case STATUS: {
			pLevelName = "STATUS ";
			break;
		}
		case WARNING: {
			pLevelName = "WARNING";
			break;
		}
		case ERROR: {
			pLevelName = " ERROR ";
			break;
		}
		default : {
			pLevelName = "       ";
			break;
		}
	}

	return pLevelName;
}

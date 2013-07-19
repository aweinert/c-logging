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
 * \file   logging.h
 * \date   June, 2013
 * \brief  Time measurement and logging
 * \author Alexander Weinert, Markus Joppich
 */

#ifndef LOGGING_H
#define LOGGING_H

/** \brief Enumerates the possible levels of urgency of a message */
typedef enum log_level {
	DEBUG = 1,
	STATUS,
	WARNING,
	ERROR,
	FINAL_LOG_LEVEL
} log_level;

void logging_reset_timer(void);

/** \brief printf-like wrapper for logging_log_message_file_line
 *
 * Relieves us of having to specify the file and line we call it with every
 * use */
#define logging_log_message(...) logging_log_message_file_line(__FILE__, __LINE__, __VA_ARGS__)
void logging_log_message_file_line(const char *file, int line, log_level level, const char *message, ...);

void logging_print_timestamp(void);

#endif // LOGGING_H

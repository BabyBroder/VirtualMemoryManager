/**
 * @file logger.h
 * @brief Header file for logging utility functions.
 *
 * This file contains the declaration of the log_event function, which is used
 * to log events or messages.
 */


#ifndef LOGGER_H
#define LOGGER_H

 /**
    * @brief Logs an event or message.
    *
    * This function takes a message as input and logs it. The implementation of
    * this function is responsible for determining how and where the message is
    * logged (e.g., to a file, console, etc.).
    *
    * @param message The message to be logged.
*/
void log_event(const char *message);
#endif // LOGGER_H
/**
 * @file logger.h
 * @brief Header file for logging utility functions.
 *
 * This file contains the declaration of the log_event function, which is used
 * to log events or messages.
 */
#ifndef LOGGER_H
#define LOGGER_H

#include "../necessary.h"

/**
 * @brief Logs an event or message to a file.
 *
 * This function logs an event or message to a file.
 *
 * @param fileLog The file to log the event or message to.
 * @param message The message to log.
 */
void log_event(const char *fileLog, const char *message);

#endif // LOGGER_H
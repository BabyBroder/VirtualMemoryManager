#include "../../lib/utils/utils.h"

 /**
    * @brief Logs an event or message.
    *
    * This function takes a message as input and logs it. The implementation of
    * this function is responsible for determining how and where the message is
    * logged (e.g., to a file, console, etc.).
    *
    * @param message The message to be logged.
*/
void log_event(char* fileLog, const char *message) {
    freopen(fileLog, "a", stdout);
    printf("%s\n", message);
}
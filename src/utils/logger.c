#include "../../lib/utils/utils.h"

void log_event(char *fileLog, const char *message)
{
    freopen(fileLog, "a", stdout);
    printf("%s\n", message);
}
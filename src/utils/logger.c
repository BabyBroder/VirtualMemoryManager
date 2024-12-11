#include "logger.h"
#include <stdio.h>

void log_event(const char *message) {
    freopen("../../data/output.log", "a", stdout);
    printf("%s\n", message);
}
// define marco for check null pointer

# define CHECK_NULL_POINTER(pointer) if (pointer == NULL) { \
    fprintf(stderr, "Error: NULL pointer detected in %s\n", __func__); \
    exit(EXIT_FAILURE); \
}


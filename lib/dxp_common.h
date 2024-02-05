#ifndef DXP_COMMON_H
#define DXP_COMMON_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Trim string
 */
char *dxp_strntrim(char *, size_t);

/**
 * Split a key-value pair field
 */
int dxp_split_field_pair(char *, const char * const, char **);

#endif /* DXP_COMMON_H */

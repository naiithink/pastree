#ifndef HEADER_DXP_COMMON_H
#define HEADER_DXP_COMMON_H

/* Do not include the non-standard <sys/errno.h> */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <magic.h>

/**
 * Trim string
 */
char *dxp_strntrim(char *, size_t);

/**
 * Split a key-value pair field
 */
int dxp_split_field_pair(char *, const char * const, char **);

/**
 * Parse date time string
 * If format is null, use RFC3339.
 */
time_t dxp_parse_datetime(char *, char *);

/**
 * Format date time
 * If format is null, use RFC3339.
 * Local time.
 */
size_t dxp_format_datetime(char *, char *, time_t);

#endif /* HEADER_DXP_COMMON_H */

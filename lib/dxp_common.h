#ifndef __DXP_COMMON_H
#define __DXP_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <magic.h>

#include "dxp_chip.h"
#include "dxp_method.h"
#include "dxp_status.h"
#include "dxp_tidbit.h"

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#include <windows.h>
#define MAX_PATH PATH_MAX
#elif defined(__APPLE__) || defined(__MACH__)
#include <sys/syslimits.h>
#elif defined(__linux__)
#include <linux/limits.h>
#endif

/**
 * Trim string
 */
char *dxp_strntrim(char *, size_t);

/**
 * Split a key-value pair field
 */
int dxp_split_field_pair(char *, const char *const, char **);

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

#endif /* __DXP_COMMON_H */

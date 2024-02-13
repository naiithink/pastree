#ifndef __DXP_COMMON_H
#define __DXP_COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * C11      memcpy_s
 */
#if (__STDC_VERSION__ < 201112L)
#error "C Standard version not met"
#elif (__STDC_VERSION__ >= 202311L)
#define __DXP_STDC_2023
#endif

#define __STDC_LIB_EXT1__ 1

#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <magic.h>

#include "dxp_error.h"
#include "dxp_status.h"

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#include <windows.h>
#define PATH_MAX MAX_PATH
#elif defined(__APPLE__) || defined(__MACH__)
#include <sys/syslimits.h>
#elif defined(__linux__)
#include <linux/limits.h>
#endif

/**
 * #define SIZE_MAX          UINTPTR_MAX
 * #define RSIZE_MAX         (SIZE_MAX >> 1)
 */
#define INTSIZE_MAX (UINTPTR_MAX >> 1)

    void *dxp_memcpy(void *, rsize_t, const void *, rsize_t);

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

    void dxp_print_bin(int);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DXP_COMMON_H */

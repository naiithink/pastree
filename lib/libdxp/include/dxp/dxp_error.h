#ifndef __DXP_ERROR_H
#define __DXP_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <assert.h>

/* Do not include the non-standard <sys/errno.h> */
#include <errno.h>

/**
 * Prioritize DXP_DEBUG over NDEBUG
 */
#ifdef DXP_DEBUG
#if (DXP_DEBUG == 0)
#define NDEBUG
#else
#undef NDEBUG
#endif
#elif (defined(NDEBUG))
#define DXP_DEBUG 0
#elif (defined(DEBUG))
#if (DEBUG == 1)
#undef NDEBUG
#else
#define NDEBUG
#endif
#define DXP_DEBUG DEBUG
#else
#define DXP_DEBUG 0
#endif

#define __DXP_DEBUG DXP_DEBUG
#define DEBUG       DXP_DEBUG

#define __DXP_DEBUG_PRINTF(fmt, ...)                                           \
    do                                                                         \
    {                                                                          \
        if (__DXP_DEBUG)                                                       \
            fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__,  \
                    ##__VA_ARGS__);                                            \
    } while (0)

#define __DXP_ASSERT_NULL_ERROR(E)                                             \
    if (E == NULL)                                                             \
    {                                                                          \
        __DXP_DEBUG_PRINTF("NULL expression");                                 \
        abort();                                                               \
    }

#define __DXP_ASSERT_NULL_RET(E, R)                                            \
    if (E == NULL)                                                             \
    {                                                                          \
        __DXP_DEBUG_PRINTF("NULL expression");                                 \
        return (R);                                                            \
    }

#define __DXP_ASSERT_NOT_NULL_ERROR(E)                                         \
    if (E != NULL)                                                             \
    {                                                                          \
        __DXP_DEBUG_PRINTF("Expression not NULL");                             \
        abort();                                                               \
    }

#define __DXP_ASSERT_NOT_NULL_RET(E, R)                                        \
    if (E != NULL)                                                             \
    {                                                                          \
        __DXP_DEBUG_PRINTF("Expression not NULL");                             \
        return (R);                                                            \
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DXP_ERROR_H */

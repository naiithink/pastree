#ifndef __DXP_H
#define __DXP_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#if (__STDC_VERSION__ < 199901L)
#error "C Standard version not met"
#elif (__STDC_VERSION__ >= 202311L)
#define __DXP_STDC_2023
#endif

#include "dxp_common.h"
#include "dxp_method.h"
#include "dxp_status.h"

    typedef struct
    {
        long time;
    } dxp_cookie_table;

    /**
     * Get method number from name
     */
    int dxp_get_method(char *);

    /**
     * Parse request tidbit
     */
    int dxp_parse_request(char *, dxp_tidbit *);

    /**
     * Parse response tidbit
     */
    int dxp_parse_response(char *, dxp_tidbit *);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DXP_H */

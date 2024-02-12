#ifndef __DXP_COOKIE_H
#define __DXP_COOKIE_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    typedef enum
    {
        INACTIVE,
        PENDING,
        ACTIVE
    } dxp_job_status;

    typedef struct
    {
        int            cookie;
        dxp_job_status status;
        char          *path;
    } dxp_hash_table;

    int dxp_cookie_table_init(dxp_hash_table **, int);

    void dxp_cookie_table_close(dxp_hash_table **);

    int dxp_cookie_table_add(int, dxp_job_status, char *);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DXP_COOKIE_H */

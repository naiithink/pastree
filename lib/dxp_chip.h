#ifndef __DXP_CHIP_H
#define __DXP_CHIP_H

typedef enum
{
    INACTIVE,
    PENDING,
    ACTIVE
} dxp_job_status;

typedef struct
{
    int cookie;
    dxp_job_status status;
    char *path;
} dxp_hash_table;

int dxp_cookie_table_init(dxp_hash_table **, int);

void dxp_cookie_table_close(dxp_hash_table **);

int dxp_cookie_table_add(int, dxp_job_status, char *);

#endif /* __DXP_CHIP_H */

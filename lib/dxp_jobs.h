#ifndef HEADER_DXP_JOBS_H
#define HEADER_DXP_JOBS_H

typedef enum
{
    INACTIVE,
    PENDING,
    ACTIVE
} dxp_job_status;

typedef struct
{
    int job_id;
    dxp_job_status status;
    char *path;
} dxp_hash_table;

int dxp_job_table_init(dxp_hash_table **, int);

void dxp_job_table_close(dxp_hash_table **);

int dxp_job_table_add(int, dxp_job_status, char *);

#endif /* HEADER_DXP_JOBS_H */

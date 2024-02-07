#ifndef __DXP_H
#define __DXP_H

#include "dxp_common.h"
#include "dxp_method.h"
#include "dxp_status.h"

union __dxp_tidbit_headline
{
    int request_method;
    int reponse_status;
};

union __dxp_tidbit_node_reference
{
    char *request_pull_path;
    char *request_push_name;
};

/**
 * DXP tidbit
 */
typedef struct
{
    union __dxp_tidbit_headline;
    char *dxp_version;
    time_t date;
    char *from;
    char *to;
    char *cookie;
    char *token;
    union __dxp_tidbit_node_reference;
    char *reponse_digest;
    char *reponse_content_type;
    char *data;
} dxp_tidbit;

typedef struct
{
    long time;
} dxp_job_table;

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

#endif /* __DXP_H */

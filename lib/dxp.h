#ifndef __DXP_H
#define __DXP_H

#include "dxp_common.h"
#include "dxp_methods.h"
#include "dxp_status.h"

/**
 * DXP request
 */
typedef struct
{
    int method;
    char *path;
    char *client_version;
    char *host;
} dxp_request;

/**
 * DXP response
 */
typedef struct
{
    int status;
    char *server_version;
    time_t date;
    char *job_id;
    char *content_type;
    char *data;
} dxp_response;

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
int dxp_parse_request(char *, dxp_request *);

/**
 * Parse response tidbit
 */
int dxp_parse_response(char *, dxp_response *);

#endif /* __DXP_H */

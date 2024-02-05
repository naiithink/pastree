#ifndef HEADER_DXP_H
#define HEADER_DXP_H

#include <magic.h>
#include <sys/time.h>

#include "dxp_methods.h"
#include "dxp_status.h"

#define DXP_LINE_TERMINATOR                                 "\r\n"
#define DXP_FIRST_FIELD_SEPARATOR                           " "
#define DXP_FIELD_SEPARATOR                                 ":"
#define DXP_HEADER_SEPARATOR                                "\r\n"

#define DXP_REQUEST_PROPNAME_CLIENT_VERSION                 "DXP-Client"
#define DXP_REQUEST_PROPNAME_HOST                           "Host"

#define DXP_RESPONSE_PROPNAME_SERVER_VERSION                "DXP-Server"
#define DXP_RESPONSE_PROPNAME_DATE                          "Date"
#define DXP_RESPONSE_PROPNAME_JOB_ID                        "Job-ID"
#define DXP_RESPONSE_PROPNAME_CONTENT_TYPE                  "Content-Type"

/* RFC3339 "2024-02-05T06:00:00+00:00" */
#define DXP_TIDBIT_DATETIME_FORMAT_RFC3339_LEN              25
#define DXP_TIDBIT_DATETIME_FORMAT_RFC3339_BUFLEN           (DXP_TIDBIT_DATETIME_FORMAT_RFC3339_LEN + 1)
#define DXP_TIDBIT_DATETIME_FORMAT_RFC822                   "%FT%T%z"

#define DXP_TIDBIT_REQUEST                                  0
#define DXP_TIDBIT_RESPONSE                                 1

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


#endif /* HEADER_DXP_H */

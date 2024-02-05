#include "dxp.h"

#include <string.h>

#include "dxp_common.h"
#include "dxp_common.c"
#include "dxp_methods.h"
#include "dxp_status.h"

int dxp_get_method(char *token)
{
    int res = -1;
    int method_index = 0;
    char *method_head = methods;

    char *method_name = methods[method_index];

    while (*methods[method_index] != '$')
    {
        method_name = methods[method_index];

        if (strncmp(dxp_strntrim(token, DXP_METHOD_MAX_NAME_LEN), method_name, DXP_METHOD_MAX_NAME_LEN) == 0)
        {
            res = method_index;
            break;
        }

        method_index++;
    }

    return res;
}

int dxp_parse_request(char *request_text, dxp_request *request_p)
{
    int ok = 0;

    int line_len = 0;
    int token_len = 0;
    char *line;
    char *token;
    char *request_line_context;
    char *request_field_context;
    char field_pair[2][DXP_MAX_FIELD_LENGTH];

    line = strtok_r(request_text, DXP_LINE_TERMINATOR, &request_line_context);
    token = strtok_r(line, DXP_FIRST_FIELD_SEPARATOR, &request_field_context);
    token_len = strnlen(token, DXP_METHOD_MAX_NAME_LEN);

    request_p->method = dxp_get_method(token);
    request_p->path = strtok_r(NULL, DXP_FIRST_FIELD_SEPARATOR, &request_field_context);

    while ((line = strtok_r(NULL, DXP_LINE_TERMINATOR, &request_line_context)) != NULL)
    {
        token = strtok_r(line, DXP_FIELD_SEPARATOR, &request_field_context);
        token_len = strnlen(token, DXP_METHOD_MAX_NAME_LEN);

        if (strncmp(token, DXP_REQUEST_PROPNAME_CLIENT_VERSION, DXP_MAX_FIELD_LENGTH) == 0)
            request_p->client_version = strtok_r(NULL, DXP_FIELD_SEPARATOR, &request_field_context);
        else if (strncmp(token, DXP_REQUEST_PROPNAME_HOST, DXP_MAX_FIELD_LENGTH) == 0)
            request_p->host = strtok_r(NULL, DXP_FIELD_SEPARATOR, &request_field_context);
        else
            return ok = EBADMSG;
    }

    return ok;
}

int dxp_parse_response(char *reponse_text, dxp_response *response_p)
{
    int ok = 0;

    int line_len = 0;
    int token_len = 0;
    char *line;
    char *token;
    char *request_line_context;
    char *request_field_context;
    char field_pair[2][DXP_MAX_FIELD_LENGTH];

    line = strtok_r(reponse_text, DXP_LINE_TERMINATOR, &request_line_context);
    token = strtok_r(line, DXP_FIRST_FIELD_SEPARATOR, &request_field_context);
    token_len = strnlen(token, DXP_METHOD_MAX_NAME_LEN);

    response_p->status = dxp_get_method(token);

    while ((line = strtok_r(NULL, DXP_LINE_TERMINATOR, &request_line_context)) != NULL)
    {
        token = strtok_r(line, DXP_FIELD_SEPARATOR, &request_field_context);
        token_len = strnlen(token, DXP_METHOD_MAX_NAME_LEN);

        if (strncmp(token, DXP_RESPONSE_PROPNAME_SERVER_VERSION, DXP_MAX_FIELD_LENGTH) == 0)
            response_p->server_version = strtok_r(NULL, DXP_FIELD_SEPARATOR, &request_field_context);
        else if (strncmp(token, DXP_RESPONSE_PROPNAME_DATE, DXP_MAX_FIELD_LENGTH) == 0)
            response_p->date = strtok_r(NULL, DXP_FIELD_SEPARATOR, &request_field_context);
        else if (strncmp(token, DXP_RESPONSE_PROPNAME_JOB_ID, DXP_MAX_FIELD_LENGTH) == 0)
            response_p->job_id = strtok_r(NULL, DXP_FIELD_SEPARATOR, &request_field_context);
        else if (strncmp(token, DXP_RESPONSE_PROPNAME_CONTENT_TYPE, DXP_MAX_FIELD_LENGTH) == 0)
            response_p->content_type = strtok_r(NULL, DXP_FIELD_SEPARATOR, &request_field_context);
        else
            return ok = EBADMSG;
    }

    return ok;
}

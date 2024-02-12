#include "../include/dxp.h"

#include "../include/dxp_common.h"

int dxp_get_method(char *token)
{
    int   res          = 0;
    int   method_index = 0;
    char *method_name  = methods[method_index];

    while (*methods[method_index] != '$')
    {
        method_name = methods[method_index];

        dxp_strntrim(token, DXP_METHOD_MAX_NAME_LEN);

        if (strncmp(dxp_strntrim(token, DXP_METHOD_MAX_NAME_LEN), method_name,
                    DXP_METHOD_MAX_NAME_LEN) == 0)
        {
            res = method_index;
            break;
        }

        method_index++;
    }

    return res;
}

// int dxp_parse_request(char *request_text, dxp_tidbit *request_p)
// {
//     int ok = __DXP_STATUS_SUCCESS;

//     SHA256_CTX ctx;

//     unsigned char digest[64];
//     char          message[] = "hello, world";

//     int   line_len  = 0;
//     int   token_len = 0;
//     char *line;
//     char *token;
//     char *request_line_context;
//     char *request_field_context;
//     char  field_pair[2][DXP_MAX_FIELD_LENGTH];

//     line  = strtok_r(request_text, DXP_LINE_TERMINATOR, &request_line_context);
//     token = strtok_r(line, DXP_FIRST_FIELD_SEPARATOR, &request_field_context);
//     token_len = strnlen(token, DXP_METHOD_MAX_NAME_LEN);

//     SHA256_Init(&ctx);
//     SHA256_Update(&ctx, message, strnlen(message, 30));
//     SHA256_Final(digest, &ctx);

//     // request_p->headline.request_method = dxp_get_method(token);
//     // request_p->request_path = strtok_r(NULL, DXP_FIRST_FIELD_SEPARATOR,
//     // &request_field_context);

//     // while ((line = strtok_r(NULL, DXP_LINE_TERMINATOR,
//     // &request_line_context)) != NULL)
//     // {
//     //     token = strtok_r(line, DXP_FIELD_SEPARATOR, &request_field_context);
//     //     token_len = strnlen(token, DXP_METHOD_MAX_NAME_LEN);

//     //     if (strncmp(token, DXP_REQUEST_PROPNAME_CLIENT_VERSION,
//     //     DXP_MAX_FIELD_LENGTH) == 0)
//     //         request_p->client_version = strtok_r(NULL, DXP_FIELD_SEPARATOR,
//     //         &request_field_context);
//     //     else if (strncmp(token, DXP_REQUEST_PROPNAME_HOST,
//     //     DXP_MAX_FIELD_LENGTH) == 0)
//     //         request_p->request_host = strtok_r(NULL, DXP_FIELD_SEPARATOR,
//     //         &request_field_context);
//     //     else
//     //         return ok = EBADMSG;
//     // }

//     return ok;
// }

// int dxp_parse_response(char *reponse_text, dxp_tidbit *response_p)
// {
//     int ok = __DXP_STATUS_SUCCESS;

//     int   line_len  = 0;
//     int   token_len = 0;
//     char *line;
//     char *token;
//     char *request_line_context;
//     char *request_field_context;
//     char  field_pair[2][DXP_MAX_FIELD_LENGTH];

//     line  = strtok_r(reponse_text, DXP_LINE_TERMINATOR, &request_line_context);
//     token = strtok_r(line, DXP_FIRST_FIELD_SEPARATOR, &request_field_context);
//     token_len = strnlen(token, DXP_METHOD_MAX_NAME_LEN);

//     // response_p->reponse_status = dxp_get_method(token);

//     // while ((line = strtok_r(NULL, DXP_LINE_TERMINATOR,
//     // &request_line_context)) != NULL)
//     // {
//     //     token = strtok_r(line, DXP_FIELD_SEPARATOR, &request_field_context);
//     //     token_len = strnlen(token, DXP_METHOD_MAX_NAME_LEN);

//     //     if (strncmp(token, DXP_RESPONSE_PROPNAME_SERVER_VERSION,
//     //     DXP_MAX_FIELD_LENGTH) == 0)
//     //         response_p->server_version = strtok_r(NULL, DXP_FIELD_SEPARATOR,
//     //         &request_field_context);
//     //     else if (strncmp(token, DXP_RESPONSE_PROPNAME_DATE,
//     //     DXP_MAX_FIELD_LENGTH) == 0)
//     //         response_p->date = dxp_parse_datetime(strtok_r(NULL,
//     //         DXP_FIELD_SEPARATOR, &request_field_context), NULL);
//     //     else if (strncmp(token, DXP_RESPONSE_PROPNAME_cookie,
//     //     DXP_MAX_FIELD_LENGTH) == 0)
//     //         response_p->cookie = strtok_r(NULL, DXP_FIELD_SEPARATOR,
//     //         &request_field_context);
//     //     else if (strncmp(token, DXP_RESPONSE_PROPNAME_CONTENT_TYPE,
//     //     DXP_MAX_FIELD_LENGTH) == 0)
//     //         response_p->reponse_content_type = strtok_r(NULL,
//     //         DXP_FIELD_SEPARATOR, &request_field_context);
//     //     else
//     //         return ok = EBADMSG;
//     // }

//     return ok;
// }

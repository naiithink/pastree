#include "../include/dxp/dxp_common.h"
#include "../include/dxp/dxp_method.h"

#include "../include/dxp/dxp.h"

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

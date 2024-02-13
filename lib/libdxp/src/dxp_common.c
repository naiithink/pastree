#include "../include/dxp/dxp_common.h"

#include "../include/dxp/dxp_method.h"
#include "../include/dxp/dxp_tidbit.h"

void *dxp_memcpy(void *dst, rsize_t dst_size, const void *src, rsize_t count)
{
    if (count > dst_size || dst_size > INTSIZE_MAX)
    {
        __DXP_DEBUG_PRINTF("Invalid destination size");
        return NULL;
    }

    return memcpy(dst, src, count);
}

char *dxp_strntrim(char *str, size_t lim)
{
    char *res  = NULL;
    char *head = str;

    while (*head == ' ' && lim > 0)
    {
        head++;
        lim--;
    }

    res = head;

    while (*head != '\0' && *head != ' ' && lim > 0)
    {
        head++;
        lim--;
    }

    *head = '\0';

    return res;
}

int dxp_split_field_pair(char *token, const char *const field_sep,
                         char **field_pair)
{
    if (token == NULL)
        return __DXP_STATUS_FAILURE;

    char *field_split_context;

    field_pair[0] = dxp_strntrim(
        strtok_r(token, field_sep, &field_split_context), DXP_MAX_FIELD_LEN);
    field_pair[1] = dxp_strntrim(
        strtok_r(NULL, field_sep, &field_split_context), DXP_MAX_FIELD_LEN);

    return __DXP_STATUS_SUCCESS;
}

time_t dxp_parse_datetime(char *buf, char *format)
{
    struct tm tm_struct;

    if (format == NULL)
    {
        int len      = strnlen(buf, DXP_TIDBIT_DATETIME_FORMAT_RFC3339_LEN);
        buf[len - 3] = buf[len - 2];
        buf[len - 2] = buf[len - 1];
        buf[len - 1] = '\0';

        strptime(buf, DXP_TIDBIT_DATETIME_FORMAT_RFC822, &tm_struct);
    }
    else
        strptime(buf, format, &tm_struct);

    return mktime(&tm_struct);
}

size_t dxp_format_datetime(char *buf, char *format, time_t time)
{
    struct tm *tm_struct;

    if (format != NULL)
        return strftime(buf, sizeof buf, format, tm_struct);

    /* RFC3339 */
    size_t char_count = 0;

    int len   = DXP_TIDBIT_DATETIME_FORMAT_RFC3339_LEN;
    tm_struct = localtime(&time);

    char_count =
        strftime(buf, len, DXP_TIDBIT_DATETIME_FORMAT_RFC822, tm_struct);
    buf[len]     = '\0';
    buf[len - 1] = buf[len - 2];
    buf[len - 2] = buf[len - 3];
    buf[len - 3] = ':';

    return ++char_count;
}

void dxp_print_bin(int num)
{
    if (num == 0)
        return;

    dxp_print_bin(num >> 1);
    printf("%d", num & 1);
}

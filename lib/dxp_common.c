#include "dxp_common.h"

#include "dxp.h"

char *dxp_strntrim(char *str, size_t lim)
{
    char *res = NULL;
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

int dxp_split_field_pair(char *token, const char *const field_sep, char **field_pair)
{
    if (token == NULL)
        return 1;

    char *field_split_context;

    field_pair[0] = dxp_strntrim(strtok_r(token, field_sep, &field_split_context), DXP_MAX_FIELD_LENGTH);
    field_pair[1] = dxp_strntrim(strtok_r(NULL, field_sep, &field_split_context), DXP_MAX_FIELD_LENGTH);

    return 0;
}

time_t dxp_parse_datetime(char *buf, char *format)
{
    struct tm tm_struct;

    if (format == NULL)
    {
        int len = strnlen(buf, DXP_TIDBIT_DATETIME_FORMAT_RFC3339_LEN);
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

    int len = DXP_TIDBIT_DATETIME_FORMAT_RFC3339_LEN;
    tm_struct = localtime(&time);

    char_count = strftime(buf, len, DXP_TIDBIT_DATETIME_FORMAT_RFC822, tm_struct);
    buf[len] = '\0';
    buf[len - 1] = buf[len - 2];
    buf[len - 2] = buf[len - 3];
    buf[len - 3] = ':';

    return ++char_count;
}

int main(void)
{
    char s[] = "  jel  ";
    printf("%s", dxp_strntrim(s, 10));
    return 0;
}

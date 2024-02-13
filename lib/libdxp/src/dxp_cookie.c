#include "../include/dxp/dxp_common.h"

#include "../include/dxp/dxp_cookie.h"

static unsigned long __seed = 0;

/**
 * TODO: Check codomain
 *
 * If the static hashing seed hasn't been initialized,
 * then initialize it to the current unix timestamp since epoch
 */
int __dxp_cookie_table_hash_seed_init(void)
{
    if (__seed != 0)
        return __DXP_STATUS_FAILURE;

    int res = (unsigned long) time(NULL);

    if (res < 0)
        return __DXP_STATUS_FAILURE;

    if ((res % 2) == 0)
        res++;

    __seed = res;

    return __DXP_STATUS_SUCCESS;
}

/**
 * TODO: Check codomain
 */
unsigned long __dxp_cookie_table_hash(char *s, int len, unsigned long max,
                                      dxp_hash_table **table_buf)
{
    unsigned long res = 1;
    /* unsigned long local_seed = __seed + !((__seed % 2) ^ (max % 2)) * 1; */

    for (int i = 0; i < len; i++)
        res *= (s[i] + __seed * i);

    res %= max;

    for (int i = 1;; i++)
    {
        if ((*table_buf)[res].status == INACTIVE)
            break;

        res = (res * i + 1) % max;
    }

    return res;
}

int dxp_cookie_table_init(dxp_hash_table **table_buf, int table_size)
{
    /* Do not overwrite initialized table */
    if (*table_buf != NULL || table_size < 0)
        return __DXP_STATUS_FAILURE;

    if (__seed == 0 && __dxp_cookie_table_hash_seed_init() == 1)
        return __DXP_STATUS_FAILURE;

    *table_buf = calloc(table_size, sizeof(dxp_hash_table));

    if (*table_buf == NULL)
        return __DXP_STATUS_FAILURE;

    return __DXP_STATUS_SUCCESS;
}

void dxp_cookie_table_close(dxp_hash_table **table_buf)
{
    free(*table_buf);
    table_buf = NULL;
}

int dxp_cookie_table_add(int cookie, dxp_job_status status, char *resource_path)
{
    return __DXP_STATUS_FAILURE;
}

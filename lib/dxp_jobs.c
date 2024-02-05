#include "dxp_jobs.h"

#include "dxp_common.h"

static unsigned long __seed = 0;

/**
 * TODO: Check codomain
 * 
 * If the static hashing seed hasn't been initialized,
 * then initialize it to the current unix timestamp since epoch
 */
int __dxp_job_table_hash_seed_init(void)
{
    if (__seed != 0)
        return 1;

    int res = (unsigned long) time(NULL);

    if ((res % 2) == 0)
        res++;

    if (res < 0)
        return 1;

    __seed = res;

    return 0;
}

/**
 * TODO: Check codomain
 */
unsigned long __dxp_job_table_hash(char *s, int len, unsigned long max, dxp_hash_table **table_buf)
{
    unsigned long res = 1;
    // unsigned long local_seed = __seed + !((__seed % 2) ^ (max % 2)) * 1;

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

int dxp_job_table_init(dxp_hash_table **table_buf, int table_size)
{
    /* Do not overwrite initialized table */
    if (*table_buf != NULL || table_size < 0)
        return 1;

    if (__seed == 0)
        __dxp_job_table_hash_seed_init();

    *table_buf = calloc(table_size, sizeof(dxp_hash_table));

    if (*table_buf == NULL)
        return 1;

    return 0;
}

void dxp_job_table_close(dxp_hash_table **table_buf)
{
    free(*table_buf);
    table_buf = NULL;
}

int dxp_job_table_add(int job_id, dxp_job_status status, char *resource_path)
{
    return -1;
}

int main(void)
{
    const long num = 12;
    dxp_hash_table job_table[num];

    dxp_job_table_init((dxp_hash_table **)&job_table, num);

    printf("> %lu\n", __dxp_job_table_hash("eiei", 4, num, (dxp_hash_table **)&job_table));
    printf("  %lu\n", __dxp_job_table_hash("aa", 2, num, (dxp_hash_table **)&job_table));
    printf("  %lu\n", __dxp_job_table_hash("bb", 2, num, (dxp_hash_table **)&job_table));
    printf("  %lu\n", __dxp_job_table_hash("ab", 2, num, (dxp_hash_table **)&job_table));
    printf("  %lu\n", __dxp_job_table_hash("ba", 2, num, (dxp_hash_table **)&job_table));
    printf("> %lu\n", __dxp_job_table_hash("eiei", 4, num, (dxp_hash_table **)&job_table));

    dxp_job_table_close((dxp_hash_table **)&job_table);

    return 0;
}

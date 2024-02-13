#include <stdio.h>
#include <stdlib.h>

#include "../include/dxp/dxp_cookie.h"

int main(int argc, char **argv)
{
    const long     num = 12;
    dxp_hash_table cookie_table[num];

    dxp_cookie_table_init((dxp_hash_table **) &cookie_table, num);

    printf("> %lu\n", __dxp_cookie_table_hash(
                          "eiei", 4, num, (dxp_hash_table **) &cookie_table));
    printf("  %lu\n", __dxp_cookie_table_hash(
                          "aa", 2, num, (dxp_hash_table **) &cookie_table));
    printf("  %lu\n", __dxp_cookie_table_hash(
                          "bb", 2, num, (dxp_hash_table **) &cookie_table));
    printf("  %lu\n", __dxp_cookie_table_hash(
                          "ab", 2, num, (dxp_hash_table **) &cookie_table));
    printf("  %lu\n", __dxp_cookie_table_hash(
                          "ba", 2, num, (dxp_hash_table **) &cookie_table));
    printf("> %lu\n", __dxp_cookie_table_hash(
                          "eiei", 4, num, (dxp_hash_table **) &cookie_table));

    dxp_cookie_table_close((dxp_hash_table **) &cookie_table);

    return EXIT_SUCCESS;
}

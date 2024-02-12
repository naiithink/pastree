#include <stdio.h>

#include "../../include/dxp_tidbit.h"

int main(int argc, char **argv)
{
    unsigned char *buff = calloc(1, sizeof(dxp_tidbit_header));

    dxp_tidbit_header *header = dxp_tidbit_header_new(
        1, 0, 0, 0b11110000, 1707768454, 0, 0b10010001, 0b10101010, 2000, 0, 0);

    dxp_tidbit_serialize(header, NULL, 0, &buff, sizeof(dxp_tidbit_header));

    // printf("|%s|\n", buff);
    printf("%x", header->node_type);
    printf("%x\n", header->method);
    // printf("%x\n", 0b10010001 & 0b11110001);

    dxp_tidbit_header_clean(&header);
    return EXIT_SUCCESS;
}

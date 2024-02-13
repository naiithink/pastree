#include <stdio.h>

#include "../include/dxp/dxp_common.h"
#include "../include/dxp/dxp_crypto.h"
#include "../include/dxp/dxp_tidbit.h"

int main(int argc, char **argv)
{
    unsigned char *buff = calloc(1, sizeof(dxp_tidbit_header));

    dxp_tidbit_header *header = dxp_tidbit_header_new(
        1, 0, 0, 0b11110000, 1707768454, 0, 0b10011001, 0b10101010, 2000, 0, 0);

    dxp_tidbit_serialize(header, NULL, 0, buff, sizeof(dxp_tidbit_header));

    unsigned char *byte = buff;

    for (int i = 0; i < sizeof(dxp_tidbit_header); i++)
    {
        printf("%d\t", i);
        dxp_print_bin(buff[i]);
        printf("\n");
    }

    dxp_tidbit_header *new_header =
        dxp_tidbit_header_new(DXP_TIDBIT_HEADER_NULLARY);
    dxp_tidbit_body *new_body = calloc(4, DXP_TIDBIT_BODY_LINE_SIZE);

    dxp_tidbit_deserialize(new_header, new_body, buff,
                           (sizeof *new_body) / DXP_TIDBIT_BODY_LINE_SIZE);

    for (int i = 0; i < sizeof(dxp_tidbit_header); i++)
    {
        printf("%d\t", i);
        dxp_print_bin(((unsigned char *) new_header)[i]);
        printf("\n");
    }

    free(new_body);
    dxp_tidbit_header_clean(header);
    dxp_tidbit_header_clean(new_header);
    return EXIT_SUCCESS;
}

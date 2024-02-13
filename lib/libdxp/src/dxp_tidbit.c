#include "../include/dxp/dxp_common.h"

#include "../include/dxp/dxp_tidbit.h"

dxp_tidbit_header *
dxp_tidbit_header_new(uint8_t version_major, uint8_t version_minor,
                      uint8_t version_patch, uint8_t flags, uint32_t unix_time,
                      uint32_t reserved0, uint8_t node_type_n_method,
                      uint8_t ctrl_inst, uint16_t status,
                      uint16_t digest_line_p, uint16_t data_line_p)

{
    dxp_tidbit_header *header = calloc(1, sizeof(dxp_tidbit_header));

    header->version_major = version_major;
    header->version_minor = version_minor;
    header->version_patch = version_patch;
    header->flags         = flags;
    header->unix_time     = unix_time;
    header->reserved0     = reserved0;
#ifdef LITTLE_ENDIAN
    header->node_type = node_type_n_method >> 4;
    header->method    = node_type_n_method;
#else
    header->method    = node_type_n_method >> 4;
    header->node_type = node_type_n_method;
#endif
    header->ctrl_inst     = ctrl_inst;
    header->status        = status;
    header->digest_line_p = digest_line_p;
    header->data_line_p   = data_line_p;

    return header;
}

void dxp_tidbit_header_clean(dxp_tidbit_header *header) { free(header); }

size_t dxp_tidbit_total_sizeof(unsigned body_line_count)
{
    return sizeof(dxp_tidbit_header) +
           sizeof(dxp_tidbit_body) * body_line_count;
}

void dxp_tidbit_serialize(dxp_tidbit_header *header, dxp_tidbit_body *body,
                          size_t body_line_count, unsigned char *buff,
                          size_t buff_size)
{
    unsigned char *head = buff;

    const size_t EXPECTED_SIZE = dxp_tidbit_total_sizeof(body_line_count);

    if (buff_size < EXPECTED_SIZE)
    {
        __DXP_DEBUG_PRINTF("Invalid buffer size");
        return;
    }

    if (dxp_memcpy(head, buff_size, header, DXP_TIDBIT_HEADER_SIZE) == NULL)
    {
        __DXP_DEBUG_PRINTF("Failed to serialize tidbit header");
        return;
    }

    if (body == NULL)
        return;

    head += DXP_TIDBIT_HEADER_SIZE;

    for (int i = 0; i < body_line_count; i++)
    {
        if (dxp_memcpy(head, buff_size - DXP_TIDBIT_HEADER_SIZE, body,
                       body_line_count))
        {
            __DXP_DEBUG_PRINTF("Failed to serialize tidbit body");
            return;
        }
        head += DXP_TIDBIT_BODY_LINE_SIZE;
    }
}

void dxp_tidbit_deserialize(dxp_tidbit_header *header, dxp_tidbit_body *body,
                            unsigned char *buff, size_t buff_size)
{
    dxp_memcpy(header, sizeof *header, buff, DXP_TIDBIT_HEADER_SIZE);

    if (body == NULL)
        return;

    dxp_memcpy(body, sizeof *body, buff + DXP_TIDBIT_HEADER_SIZE,
               buff_size - DXP_TIDBIT_HEADER_SIZE);
}

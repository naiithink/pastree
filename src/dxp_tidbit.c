#include "../include/dxp_tidbit.h"

#include "../include/dxp_common.h"

dxp_tidbit_header *
dxp_tidbit_header_new(uint8_t version_major, uint8_t version_minor,
                      uint8_t version_patch, uint8_t flags, uint32_t unix_time,
                      uint32_t reserved0, uint8_t node_type_n_method,
                      uint8_t ctrl_inst, uint16_t status, uint8_t digest_line_p,
                      uint8_t data_line_p)

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
    header->method    = node_type_n_method | header->node_type;
#else
    header->method    = node_type_n_method >> 4;
    header->node_type = node_type_n_method | header->method;
#endif
    header->ctrl_inst     = ctrl_inst;
    header->status        = status;
    header->digest_line_p = digest_line_p;
    header->data_line_p   = data_line_p;

    return header;
}

void dxp_tidbit_header_clean(dxp_tidbit_header **header) { free(*header); }

void dxp_tidbit_serialize(dxp_tidbit_header *header, dxp_tidbit_body *body,
                          size_t body_size, unsigned char **buff,
                          size_t buff_size)
{
    unsigned char *head = *buff;

    memcpy(head, header, sizeof(dxp_tidbit_header));

    if (body == NULL)
        return;

    memcpy(head + sizeof(dxp_tidbit_header), body, body_size);
}

void dxp_tidbit_deserialize(dxp_tidbit_header *header, dxp_tidbit_body *body,
                            unsigned char *buff, size_t body_size,
                            size_t buff_size)
{
    memcpy(header, buff, sizeof(dxp_tidbit_header));

    if (body == NULL)
        return;

    memcpy(body, buff + sizeof(dxp_tidbit_header), sizeof(dxp_tidbit_header));
}

#include "../include/dxp_tidbit.h"

#include "../include/dxp_common.h"

int parse_raw(dxp_tidbit_raw *tidbit_raw, dxp_tidbit **tidbit)
{
    int ok = __DXP_STATUS_FAILURE;

    if (tidbit_raw == NULL || tidbit == NULL)
        return __DXP_STATUS_FAILURE;

    uint8_t  version_major  = 0;
    uint8_t  version_minor  = 0;
    uint8_t  version_patch  = 0;
    uint8_t  flags          = 0;
    time_t   unix_timestamp = 0;
    uint32_t reserved1      = 0;
    uint8_t  dxp_method     = 0;

    flags         = tidbit_raw->headline >> 0x8;
    version_major = tidbit_raw->headline >> 0x8;
    version_minor = tidbit_raw->headline >> 0x8;
    version_patch = tidbit_raw->headline >> 0x8;

    (*tidbit)->date         = tidbit_raw->timestamp;
    (*tidbit)->reserved0    = tidbit_raw->reserved0;
    (*tidbit)->method       = tidbit_raw->method_n_nodetype >> 4;
    (*tidbit)->node_type    = tidbit_raw->method_n_nodetype >> 4;
    (*tidbit)->control_inst = tidbit_raw->control_inst;
    (*tidbit)->status       = tidbit_raw->status;

    return ok;
}

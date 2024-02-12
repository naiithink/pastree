#ifndef __DXP_TIDBIT_H
#define __DXP_TIDBIT_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "dxp_common.h"

#define DXP_LINE_TERMINATOR                    "\r\n"
#define DXP_FIRST_FIELD_SEPARATOR              " "
#define DXP_FIELD_SEPARATOR                    ":"
#define DXP_HEADER_SEPARATOR                   "\r\n"

#define DXP_REQUEST_PROPNAME_DXP_VERSION       "DXP-Version"
#define DXP_RESPONSE_PROPNAME_DATE             "Date"
#define DXP_RESPONSE_PROPNAME_FROM             "From"
#define DXP_RESPONSE_PROPNAME_TO               "To"
#define DXP_RESPONSE_PROPNAME_COOKIE           "Cookie"
#define DXP_RESPONSE_PROPNAME_TOKEN            "Token"
#define DXP_RESPONSE_PROPNAME_PUSH_NAME        "Push-Name"
#define DXP_RESPONSE_PROPNAME_PULL_PATH        "Pull-Path"
#define DXP_RESPONSE_PROPNAME_DIGEST           "Digest"
#define DXP_RESPONSE_PROPNAME_CONTENT_TYPE     "Content-Type"

/* RFC3339 "2024-02-05T06:00:00+00:00" */
#define DXP_TIDBIT_DATETIME_FORMAT_RFC3339_LEN 25
#define DXP_TIDBIT_DATETIME_FORMAT_RFC3339_BUFLEN                              \
    (DXP_TIDBIT_DATETIME_FORMAT_RFC3339_LEN + 1)
#define DXP_TIDBIT_DATETIME_FORMAT_RFC822 "%FT%T%z"

#define DXP_TIDBIT_REQUEST                0
#define DXP_TIDBIT_RESPONSE               1

#define DXP_METHOD_PUSH                   0b0001
#define DXP_METHOD_PULL                   0b0010
#define DXP_METHOD_POLL                   0b0100
#define DXP_METHOD_PICK                   0b1000

#define DXP_NODE_TYPE_S_IFCHR             0b0001 /* character special */
#define DXP_NODE_TYPE_S_IFDIR             0b0010 /* directory */
#define DXP_NODE_TYPE_S_IFBLK             0b0011 /* block special */
#define DXP_NODE_TYPE_S_IFREG             0b0100 /* regular */
#define DXP_NODE_TYPE_S_IFLNK             0b0101 /* symbolic link */
#define DXP_NODE_TYPE_S_IFSOCK            0b0110 /* socket */
#define DXP_NODE_TYPE_S_IFWHT             0b0111 /* whiteout */

    struct __dxp_tidbit_headline_request
    {
        int method;
        union
        {
            char *pull_path;
            char *push_name;
        };
    };

    union __dxp_tidbit_headline
    {
        int                                  status;
        struct __dxp_tidbit_headline_request request;
    };

    /**
     * DXP tidbit
     */
    typedef struct
    {
        uint8_t *dxp_version_major;
        uint8_t *dxp_version_minor;
        uint8_t *dxp_version_patch;
        time_t   date;
        uint32_t reserved0;
        uint16_t status;
        uint8_t  method;
        uint8_t  node_type;
        uint8_t  control_inst;
        uint8_t  flags;
        char    *cookie;
        time_t  *cookie_expire_at;
        char    *checksum;
        char    *content_type;
        char    *data;
    } dxp_tidbit;

    /**
     * Raw DXP tidbit
     */
    typedef struct
    {
        uint32_t headline;
        uint8_t  flags;
        uint32_t timestamp;
        uint32_t reserved0;
        uint8_t  method_n_nodetype;
        uint8_t  control_inst;
        uint16_t status;
        char    *data;
    } dxp_tidbit_raw;

    int parse_raw(dxp_tidbit_raw *, dxp_tidbit **);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DXP_TIDBIT_H */

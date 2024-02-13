#ifndef __DXP_TIDBIT_H
#define __DXP_TIDBIT_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <stdint.h>
#include <stdio.h>

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

/**
 * Tidbit header
 */
#pragma pack(push)
    typedef struct
    {
        uint8_t  version_major;
        uint8_t  version_minor;
        uint8_t  version_patch;
        uint8_t  flags;
        uint32_t unix_time;
        uint32_t reserved0;
#ifdef LITTLE_ENDIAN
        uint8_t node_type : 4, method : 4;
#else
    uint8_t method : 4, node_type : 4;
#endif
        uint8_t  ctrl_inst;
        uint16_t status;
        uint16_t digest_line_p;
        uint16_t data_line_p;
    } dxp_tidbit_header;
#pragma pack(pop)

    /**
     * Tidbit body
     * 2-D array of 32-bit data lines
     */
    typedef uint32_t dxp_tidbit_body;

    static const size_t DXP_TIDBIT_HEADER_SIZE    = sizeof(dxp_tidbit_header);
    static const size_t DXP_TIDBIT_BODY_LINE_SIZE = sizeof(dxp_tidbit_body);

#define DXP_TIDBIT_HEADER_NULLARY 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

    dxp_tidbit_header *dxp_tidbit_header_new(uint8_t, uint8_t, uint8_t, uint8_t,
                                             uint32_t, uint32_t, uint8_t,
                                             uint8_t, uint16_t, uint16_t,
                                             uint16_t);

    void dxp_tidbit_header_clean(dxp_tidbit_header *);

    size_t dxp_tidbit_total_sizeof(unsigned);

    void dxp_tidbit_serialize(dxp_tidbit_header *, dxp_tidbit_body *, size_t,
                              unsigned char *, size_t);

    void dxp_tidbit_deserialize(dxp_tidbit_header *, dxp_tidbit_body *,
                                unsigned char *, size_t);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DXP_TIDBIT_H */

#ifndef __DXP_TIDBIT_H
#define __DXP_TIDBIT_H

#define DXP_LINE_TERMINATOR                                 "\r\n"
#define DXP_FIRST_FIELD_SEPARATOR                           " "
#define DXP_FIELD_SEPARATOR                                 ":"
#define DXP_HEADER_SEPARATOR                                "\r\n"

#define DXP_REQUEST_PROPNAME_DXP_VERSION                    "DXP-Version"
#define DXP_RESPONSE_PROPNAME_DATE                          "Date"
#define DXP_RESPONSE_PROPNAME_FROM                          "From"
#define DXP_RESPONSE_PROPNAME_TO                            "To"
#define DXP_RESPONSE_PROPNAME_COOKIE                        "Cookie"
#define DXP_RESPONSE_PROPNAME_TOKEN                         "Token"
#define DXP_RESPONSE_PROPNAME_PUSH_NAME                     "Push-Name"
#define DXP_RESPONSE_PROPNAME_PULL_PATH                     "Pull-Path"
#define DXP_RESPONSE_PROPNAME_DIGEST                        "Digest"
#define DXP_RESPONSE_PROPNAME_CONTENT_TYPE                  "Content-Type"

/* RFC3339 "2024-02-05T06:00:00+00:00" */
#define DXP_TIDBIT_DATETIME_FORMAT_RFC3339_LEN              25
#define DXP_TIDBIT_DATETIME_FORMAT_RFC3339_BUFLEN           (DXP_TIDBIT_DATETIME_FORMAT_RFC3339_LEN + 1)
#define DXP_TIDBIT_DATETIME_FORMAT_RFC822                   "%FT%T%z"

#define DXP_TIDBIT_REQUEST                                  0
#define DXP_TIDBIT_RESPONSE                                 1

#endif /* __DXP_TIDBIT_H */

#ifndef __DXP_STATUS_H
#define __DXP_STATUS_H

/* Do not include the non-standard <sys/errno.h> */
#include <errno.h>

/* Internal function status */
#define __DXP_STATUS_UNKNOWN            -1
#define __DXP_STATUS_SUCCESS            0
#define __DXP_STATUS_FAILURE            1

/* Operational errors */
#define DXP_STATUS_OK                   0

/* Request-response */
#define DXP_STATUS_READY                1000
#define DXP_STATUS_DECLINED             1001

/* Information exchange */
#define DXP_STATUS_DONE                 2000
#define DXP_STATUS_MORE                 2001

#endif /* __DXP_STATUS_H */

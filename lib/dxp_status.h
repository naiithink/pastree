#ifndef __DXP_STATUS_H
#define __DXP_STATUS_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Internal function status */
#define __DXP_STATUS_SUCCESS 1
#define __DXP_STATUS_FAILURE -1

/* Operational errors */
#define DXP_STATUS_OK        0

/* Request-response */
#define DXP_STATUS_READY     1000
#define DXP_STATUS_DECLINED  1001

/* Information exchange */
#define DXP_STATUS_DONE      2000
#define DXP_STATUS_MORE      2001

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DXP_STATUS_H */

#ifndef __DXP_METHOD_H
#define __DXP_METHOD_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define DXP_METHOD_MAX_NAME_LEN   9
#define DXP_MAX_FIELD_PAIR_LENGTH 80
#define DXP_MAX_FIELD_LENGTH      (DXP_MAX_FIELD_PAIR_LENGTH / 2)
#define DXP_METHOD_NAME_LIST_TERM '$'

#define DXP_METHODS                                                            \
    X("EDEFN")                                                                 \
    X("PLUCK")                                                                 \
    X("PICK")                                                                  \
    X("PACK")

    char *methods[] = {
#define X(s) s,
        DXP_METHODS
#undef X
        "$"};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DXP_METHOD_H */

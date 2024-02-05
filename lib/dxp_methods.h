#ifndef HEADER_DXP_METHODS_H
#define HEADER_DXP_METHODS_H

#define DXP_METHOD_MAX_NAME_LEN         9
#define DXP_MAX_FIELD_PAIR_LENGTH       80
#define DXP_MAX_FIELD_LENGTH            (DXP_MAX_FIELD_PAIR_LENGTH / 2)
#define DXP_METHOD_NAME_LIST_TERM       '$'

#define DXP_METHODS                     \
    X("EDEFN")                          \
    X("PLUCK")                          \
    X("PICK")                           \
    X("PACK")

#define DXP_METHOD_EDEFN                (int) 0
#define DXP_METHOD_PLUCK                (int) 1
#define DXP_METHOD_PICK                 (int) 2
#define DXP_METHOD_PACK                 (int) 3

char *methods[] = {
#define X(s) s,
    DXP_METHODS
#undef X
"$"
};

#endif /* HEADER_DXP_METHODS_H */

#ifndef __ERR_DEFINES_H__

#define __ERR_DEFINES_H__

#include "macrologger.h"

#define ERROR(name, code) \
{ \
    LOG_ERROR("%s", name); \
    return code; \
}

#define EXIT_CODE(name, code) \
{ \
    LOG_ERROR("%s", name); \
    exit_code = code; \
}

#define FREEP_ERROR(name, code) \
{ \
    free_array(players); \
    LOG_ERROR("%s", name); \
    return code; \
}

#define FREEPN_ERROR(err_name, code) \
{ \
    free_array(players); \
    free(current.name); \
    LOG_ERROR("%s", err_name); \
    return code; \
}

#define FREELIST_ERROR(err_name, code) \
{ \
    free_list(head); \
    LOG_ERROR("%s", err_name); \
    return code; \
}

#endif

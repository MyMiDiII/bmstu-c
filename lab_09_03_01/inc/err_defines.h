#ifndef __ERR_DEFINES_H__

#define __ERR_DEFINES_H__

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
    free_array(products); \
    LOG_ERROR("%s", name); \
    return code; \
}

#define FREEPN_ERROR(err_name, code) \
{ \
    free_array(products); \
    free(current.name); \
    LOG_ERROR("%s", err_name); \
    return code; \
}

#endif

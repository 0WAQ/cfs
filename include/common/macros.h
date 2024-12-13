/**
 * 
 * 通用模块
 * 
 */
#ifndef COMMON_H
#define COMMON_H

#include "types.h"

#define offset_of(container_type, member_name) \
        ((uint64_t)&((container_type*)0)->member_name)

#define container_of(member_val, container_type, member_name) \
    ( (container_type*)( (uint64_t)member_val - offset_of(container_type, member_name) ) )

#define entry_of(member_val, container_type, member_name) \
    ((container_type*)(member_val ? container_of(member_val, container_type, member_name) : 0))


#endif // COMMON_H 
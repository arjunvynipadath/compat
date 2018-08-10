#ifndef __COMPAT_LINUX_BLK_TYPES_H
#define __COMPAT_LINUX_BLK_TYPES_H

#include "../../compat/config.h"

#include_next <linux/blk_types.h>

#ifndef HAVE_BLK_MQ_REQ_FLAGS_T
typedef __u32 __bitwise blk_mq_req_flags_t;
#endif

#endif /* __COMPAT_LINUX_BLK_TYPES_H */

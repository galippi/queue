#ifndef _QUEUE_CONF_H_
#define _QUEUE_CONF_H_

#include <stdint.h>

#define INLINE static inline

typedef uint8_t tQueueIdx;
typedef uint8_t tQueueData;

typedef struct sQueue tQueue; /* forward declaration */

void queueEmptyErrorHandler(const tQueue *q);
#define QUEUE_EMPTY_ERROR_HANDLER(q) queueEmptyErrorHandler(q)

#define QUEUE_CONFIG_ERROR_HANDLER(q) /* do nothing */

#endif /* _QUEUE_CONF_H_ */

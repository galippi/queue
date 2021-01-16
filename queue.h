#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdint.h>

#include "queue_conf.h"

typedef uint8_t tQueueIdx;

typedef struct
{
  tQueueIdx in;
  tQueueIdx out;
}tQueueIdxData;

typedef struct sQueue
{
  tQueueData *dataPtr;
  tQueueIdxData *idxPtr;
  tQueueIdx size;
}tQueue;

#define QUEUE_CREATE(q, size) \
    tQueueData q##_data[size]; \
    tQueueIdxData q##_idx; \
    const tQueue q = {q##_data, &q##_idx, size};
int8_t queueInit(const tQueue *q);
int8_t queueIsEmpty(const tQueue *q);
tQueueIdx queueGetNum(const tQueue *q);
int8_t queueIsFull(const tQueue *q);
int8_t queuePut(const tQueue *q, tQueueData data);
tQueueIdx queueWrite(const tQueue *q, const tQueueData *data, tQueueIdx num);
int8_t queueGet(const tQueue *q, tQueueData *data);
tQueueData queueGetData(const tQueue *q);
tQueueIdx queueRead(const tQueue *q, tQueueData *data, tQueueIdx num);

/* functions for unit testing */
INLINE tQueueIdx queueGetIn(const tQueue *q)
{
    return q->idxPtr->in;
}

INLINE tQueueIdx queueGetOut(const tQueue *q)
{
    return q->idxPtr->out;
}

#endif /* _QUEUE_H_ */

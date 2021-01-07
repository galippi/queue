#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdint.h>

typedef uint8_t tQueueIdx;
typedef uint8_t tQueueData;

typedef struct
{
  tQueueIdx in;
  tQueueIdx out;
  tQueueData *dataPtr;
  tQueueIdx size;
}tQueue;

int8_t queueInit(tQueue *q, tQueueData *dataPtr, tQueueIdx size);
int8_t queueIsEmpty(const tQueue *q);
tQueueIdx queueGetNum(const tQueue *q);
int8_t queueIsFull(const tQueue *q);
int8_t queuePut(tQueue *q, tQueueData data);
int8_t queueGet(tQueue *q, tQueueData *data);
tQueueData queueGetData(tQueue *q);

void queueEmptyErrorHandler(const tQueue *q);
#define QUEUE_EMPTY_ERROR_HANDLER(q) queueEmptyErrorHandler(q)

#endif /* _QUEUE_H_ */

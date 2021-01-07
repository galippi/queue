#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdint.h>

#include "queue_conf.h"

typedef struct sQueue
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
tQueueIdx queueWrite(tQueue *q, const tQueueData *data, tQueueIdx num);
int8_t queueGet(tQueue *q, tQueueData *data);
tQueueData queueGetData(tQueue *q);
tQueueIdx queueRead(tQueue *q, tQueueData *data, tQueueIdx num);

#endif /* _QUEUE_H_ */

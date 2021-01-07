
#include "queue.h"

int8_t queueInit(tQueue *q, tQueueData *dataPtr, tQueueIdx size)
{
  q->in = 0;
  q->out = 0;
  q->dataPtr = dataPtr;
  q->size = size;
  return 0;
}

int8_t queueIsEmpty(const tQueue *q)
{
  return (q->in == q->out);
}

tQueueIdx queueGetNum(const tQueue *q)
{
  tQueueIdx num = q->out - q->in;
  if (q->out >= q->in)
  {
      if (num > q->size)
          num -= q->size;
  }else
  { /*   if (num > q->size) */
    num = num + q->size;
    if (num == 0)
      num = q->size;
  }
  return num;
}

int8_t queueIsFull(const tQueue *q)
{
  tQueueIdx num = queueGetNum(q);
  return (num == q->size);
}

int8_t queuePut(tQueue *q, tQueueData data)
{
  if (queueIsFull(q))
    return 1;
  tQueueIdx newIdx = q->in + 1;
  if (newIdx == (q->size * 2))
    newIdx = 0;
  q->dataPtr[q->in % q->size] = data;
  q->in = newIdx;
  return 0;
}

int8_t queueGet(tQueue *q, tQueueData *data)
{
  if (queueIsEmpty(q))
    return 1;
  tQueueIdx newIdx = q->out + 1;
  if (newIdx == (q->size * 2))
    newIdx = 0;
  *data = q->dataPtr[q->out % q->size];
  q->out = newIdx;
  return 0;
}

tQueueData queueGetData(tQueue *q)
{
  tQueueData data;
  if (queueGet(q, &data))
  {
    QUEUE_EMPTY_ERROR_HANDLER(q);
    return 0;
  }
  return data;
}

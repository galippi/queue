
#include "queue.h"

INLINE tQueueIdx queueNextIdx(const tQueue *q, tQueueIdx idx)
{
    tQueueIdx newIdx = idx + 1;
    if (newIdx == q->size)
        newIdx = 0;
    return newIdx;
}

INLINE tQueueIdx queueArrayIdx(const tQueue *q, tQueueIdx idx)
{
    (void)q;
    return idx;
}

int8_t queueInit(const tQueue *q)
{
  q->idxPtr->in = 0;
  q->idxPtr->out = 0;
  return 0;
}

int8_t queueIsEmpty(const tQueue *q)
{
  return (q->idxPtr->in == q->idxPtr->out);
}

tQueueIdx queueGetNum(const tQueue *q)
{
  tQueueIdx in = q->idxPtr->in, out = q->idxPtr->out;
  tQueueIdx num;
  if (in >= out)
  {
      num = in - out;
  }else
  { /*   if (num > q->size) */
    num = q->size - out + in;
  }
  return num;
}

int8_t queueIsFull(const tQueue *q)
{
  return (q->idxPtr->out == queueNextIdx(q, q->idxPtr->in));
}

int8_t queuePut(const tQueue *q, tQueueData data)
{
  if (queueIsFull(q))
    return 1;
  q->dataPtr[queueArrayIdx(q, q->idxPtr->in)] = data;
  q->idxPtr->in = queueNextIdx(q, q->idxPtr->in);
  return 0;
}

tQueueIdx queueWrite(const tQueue *q, const tQueueData *data, tQueueIdx num)
{
    tQueueIdx written = 0;
    while (num != 0)
    {
        if (queuePut(q, *data) != 0)
            break;
        data++;
        written++;
        num--;
    }
    return written;
}

int8_t queueGet(const tQueue *q, tQueueData *data)
{
  if (queueIsEmpty(q))
    return 1;
  *data = q->dataPtr[queueArrayIdx(q, q->idxPtr->out)];
  q->idxPtr->out = queueNextIdx(q, q->idxPtr->out);
  return 0;
}

tQueueData queueGetData(const tQueue *q)
{
  tQueueData data;
  if (queueGet(q, &data))
  {
    QUEUE_EMPTY_ERROR_HANDLER(q);
    return 0;
  }
  return data;
}

tQueueIdx queueRead(const tQueue *q, tQueueData *data, tQueueIdx num)
{
    tQueueIdx readNum = 0;
    while (num != 0)
    {
        if (queueGet(q, data) != 0)
            break;
        data++;
        readNum++;
        num--;
    }
    return readNum;
}

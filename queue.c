
#include "queue.h"

INLINE tQueueIdx queueNextIdx(const tQueue *q, tQueueIdx idx)
{
    (void)q;
    tQueueIdx newIdx = idx + 1;
    return newIdx;
}

INLINE tQueueIdx queueArrayIdx(const tQueue *q, tQueueIdx idx)
{
    (void)q;
    return ((idx < 128) ? idx : (idx - 128));
}

int8_t queueInit(const tQueue *q)
{
  q->idxPtr->in = 0;
  q->idxPtr->out = 0;
  if (q->size != 128)
  {
      QUEUE_CONFIG_ERROR_HANDLER(q);
      return 1; /* the bit size of tQueueIdx is not enough to store the data */
  }
  return 0;
}

int8_t queueIsEmpty(const tQueue *q)
{
  return (q->idxPtr->in == q->idxPtr->out);
}

tQueueIdx queueGetNum(const tQueue *q)
{
  tQueueIdx num = q->idxPtr->in - q->idxPtr->out;
  return num;
}

int8_t queueIsFull(const tQueue *q)
{
  tQueueIdx num = queueGetNum(q);
  return (num == 128);
}

tQueueIdx queuePutIdx(const tQueue *q)
{
  if (queueIsFull(q))
    return 255;
  tQueueIdx idx = queueArrayIdx(q, q->idxPtr->in);
  q->idxPtr->in = queueNextIdx(q, q->idxPtr->in);;
  return idx;
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

tQueueIdx queueGetIdx(const tQueue *q)
{
  if (queueIsEmpty(q))
    return 255;
  tQueueIdx idx = queueArrayIdx(q, q->idxPtr->out);
  q->idxPtr->out = queueNextIdx(q, q->idxPtr->out);
  return idx;
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

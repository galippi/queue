
#include "queue.h"

INLINE tQueueIdx queueNextIdx(const tQueue *q, tQueueIdx idx)
{
    tQueueIdx newIdx = idx + 1;
    if (newIdx == (q->size * 2))
        newIdx = 0;
    return newIdx;
}

INLINE tQueueIdx queueArrayIdx(const tQueue *q, tQueueIdx idx)
{
    return ((idx < q->size) ? idx : (idx - q->size));
}

int8_t queueInit(tQueue *q, tQueueData *dataPtr, tQueueIdx size)
{
  q->in = 0;
  q->out = 0;
  q->dataPtr = dataPtr;
  q->size = size;
  if (size >= (1 << (sizeof(tQueueIdx) * 7)))
  {
      QUEUE_CONFIG_ERROR_HANDLER(q);
      return 1; /* the bit size of tQueueIdx is not enough to store the data */
  }
  return 0;
}

int8_t queueIsEmpty(const tQueue *q)
{
  return (q->in == q->out);
}

tQueueIdx queueGetNum(const tQueue *q)
{
  tQueueIdx num = q->in - q->out;
  if (q->in >= q->out)
  {
      if (num > q->size)
          num -= q->size;
  }else
  { /*   if (num > q->size) */
    num = num + q->size;
    if (num == 0)
      num = q->size;
    else if (num > q->size)
        num = num + q->size;
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
  q->dataPtr[queueArrayIdx(q, q->in)] = data;
  q->in = queueNextIdx(q, q->in);;
  return 0;
}

tQueueIdx queueWrite(tQueue *q, const tQueueData *data, tQueueIdx num)
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

int8_t queueGet(tQueue *q, tQueueData *data)
{
  if (queueIsEmpty(q))
    return 1;
  *data = q->dataPtr[queueArrayIdx(q, q->out)];
  q->out = queueNextIdx(q, q->out);
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

tQueueIdx queueRead(tQueue *q, tQueueData *data, tQueueIdx num)
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

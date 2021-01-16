
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

int8_t queueInit(tQueue *q, tQueueData *dataPtr, tQueueIdx size)
{
  q->in = 0;
  q->out = 0;
  q->dataPtr = dataPtr;
  if (size != 128)
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
      if (num > 128)
          num -= 128;
  }else
  { /*   if (num > q->size) */
    num = num + 128;
    if (num == 0)
      num = 128;
    else if (num > 128)
        num = num + 128;
  }
  return num;
}

int8_t queueIsFull(const tQueue *q)
{
  tQueueIdx num = queueGetNum(q);
  return (num == 128);
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

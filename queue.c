
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
    tQueueIdx arrayIdx = idx;
    if (arrayIdx >= q->sizeData)
        arrayIdx -= (q->sizeData);
    return arrayIdx;
}

int8_t queueInit(const tQueue *q)
{
  q->idxPtr->in = 0;
  q->idxPtr->inData = 0;
  q->idxPtr->out = 0;
  q->idxPtr->outData = 0;
  return 0;
}

int8_t queueIsEmpty(const tQueue *q)
{
  return (q->idxPtr->in == q->idxPtr->out);
}

tQueueIdx queueGetNum(const tQueue *q)
{
  uint32_t num = q->idxPtr->in - q->idxPtr->out;
  if (num > q->size)
  {
      num = num + q->size;
  }
  return (tQueueIdx)num;
}

int8_t queueIsFull(const tQueue *q)
{
  return (q->idxPtr->out == queueNextIdx(q, q->idxPtr->in));
}

tQueueIdx queuePutIdx(const tQueue *q)
{
  if (queueIsFull(q))
    return 255;
  tQueueIdx idx = q->idxPtr->inData;
  q->idxPtr->inData = queueArrayIdx(q, q->idxPtr->inData + 1);
  q->idxPtr->in = queueNextIdx(q, q->idxPtr->in);
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
  tQueueIdx idx = q->idxPtr->outData;
  q->idxPtr->outData = queueArrayIdx(q, q->idxPtr->outData + 1);
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

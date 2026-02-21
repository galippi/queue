#include "queue.h"

INLINE tQueueIdx minIdx(tQueueIdx left, tQueueIdx right)
{
    if (left <= right)
        return left;
    else
        return right;
}

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

int8_t queueInit(const tQueue *q)
{
  q->idxPtr->in = 0;
  q->idxPtr->out = 0;
  if (q->size > (1 << (sizeof(tQueueIdx) * 7)))
  {
      QUEUE_CONFIG_ERROR_HANDLER(q);
      return 1; /* the bit size of tQueueIdx is not enough to store the data */
  }
  return 0;
}

tQueueIdx queueGetNum(const tQueue *q)
{
  tQueueIdx in = q->idxPtr->in, out = q->idxPtr->out;
  tQueueIdx num = in - out;
  if (in >= out)
  {
      if (num > q->size)
          num -= q->size;
  }else
  { /*   if (num > q->size) */
    num = num + q->size;
    if (num == 0)
      num = q->size;
    else /* if (num > q->size) */
        num = num + q->size;
  }
  return num;
}

int8_t queueIsFull(const tQueue *q)
{
  tQueueIdx num = queueGetNum(q);
  return (num == q->size);
}

int8_t queuePut(const tQueue *q, tQueueData data)
{
  if (queueIsFull(q))
    return 1;
  q->dataPtr[queueArrayIdx(q, q->idxPtr->in)] = data;
  q->idxPtr->in = queueNextIdx(q, q->idxPtr->in);;
  return 0;
}

static tQueueData *queueGetInDataPtr(const tQueue *q, tQueueIdx *num)
{
    tQueueData *result;
    tQueueIdx avail;
    if (q->idxPtr->in < q->size) {
        result = &q->dataPtr[q->idxPtr->in];
            avail = q->size - q->idxPtr->in;
    }else{ /* (q->idxPtr->in >= q->size) */
        tQueueIdx buffIdx = q->idxPtr->in - q->size;
        result = &q->dataPtr[buffIdx];
        tQueueIdx rest = (2 * q->size) - q->idxPtr->in;
        if (q->idxPtr->out == q->idxPtr->in)
            avail = rest;
        else
            avail = minIdx(q->idxPtr->out - buffIdx, rest);
    }
    if (avail < *num)
        *num = avail;
    if (avail == 0)
        result = NULL;
    return result;
}

static tQueueIdx queueUpdateInDataPtr(const tQueue *q, tQueueIdx num)
{
    do {
        tQueueIdx avail;
        avail = q->idxPtr->out - q->idxPtr->in;
        if (avail == 0)
            avail = q->size;
        else
        if (avail > q->size)
            avail = (2 * q->size) - q->idxPtr->in;
        if (avail > num)
            avail = num;
        if (avail == 0)
            break;
        q->idxPtr->in += avail;
        if (q->idxPtr->in == (2 * q->size))
            q->idxPtr->in = 0;
        num -= avail;
    }while(num != 0);
    return num;
}

tQueueIdx queueWrite(const tQueue *q, const tQueueData *data, tQueueIdx num)
{
    tQueueIdx written = 0;
    do {
        tQueueIdx available = num;
        tQueueData *dataPtr = queueGetInDataPtr(q, &available);
        if (available == 0)
            break;
        memcpy(dataPtr, data, available * sizeof(tQueueData));
        tQueueIdx remain = queueUpdateInDataPtr(q, available);
        assert_lw(ASSERT_UT, remain == 0);
        (void)remain;
        written += available;
        data += available;
        num -= available;
    } while (num > 0);
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

/**
 * queueGetDataBuffer
 * Get a direct access to the data pointer of the queue
 * @param q - pointer to queue object
 * @param num - pointer to number of items, which can be accessed in linear way,
 *              if it's 0, then all available data will be available
 *              it will give back the number of data, which can be read from the buffer
 * @return pointer to the data buffer
 */
tQueueData *queueGetDataBuffer(const tQueue *q, tQueueIdx *num)
{
    tQueueIdx avail;
    if (q->idxPtr->out <= q->idxPtr->in) {
        if (q->idxPtr->out < q->size)
            avail = minIdx(q->size - q->idxPtr->out, q->idxPtr->in - q->idxPtr->out);
        else
            avail = minIdx((2 * q->size) - q->idxPtr->out, q->idxPtr->in - q->idxPtr->out);
    }else{
        avail = (2 * q->size) - q->idxPtr->out;
    }
    tQueueData *ret;
    if (avail == 0)
        ret = NULL;
    else {
        if (q->idxPtr->out < q->size)
            ret = &q->dataPtr[q->idxPtr->out];
        else
            ret = &q->dataPtr[q->idxPtr->out - q->size];
    }
    if ((*num != 0) && (avail > *num))
        avail = *num;
    *num = avail;
    return ret;
}

int8_t queueRemoveData(const tQueue *q, tQueueIdx num)
{
    //if ((q->idxPtr->out != q->idxPtr->in)
    tQueueIdx avail = queueGetNum(q);
    if (avail < num) {
        QUEUE_EMPTY_ERROR_HANDLER(q);
        return 1;
    }else{
        if (q->idxPtr->out < q->size) {
            q->idxPtr->out = q->idxPtr->out + num;
        }else{
            avail = (2 * q->size) - q->idxPtr->out;
            if (avail > num)
                q->idxPtr->out = q->idxPtr->out + num;
            else
                q->idxPtr->out = num - avail;
        }
        return 0;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "queue.h"

uint32_t testCaseCnt = 0;
uint32_t testCaseFailed = 0;

static char testCaseInfo[1024];
static const char *print(const char *pszFormat, ...)
{
    va_list argptr;
    va_start(argptr, pszFormat);
    vsnprintf(testCaseInfo, sizeof(testCaseInfo), pszFormat, argptr);
    va_end(argptr);
    return testCaseInfo;
}

#define TestCaseAssertTrue(cond, description)\
        testCaseCnt++; \
        if (cond) \
        { /* do nothing */\
        }else \
        { \
            testCaseFailed++; \
            printf("The test case is failed in line %d (%s)!\n", __LINE__, description); \
        }

#define TestCaseAssertFalse(cond) TestCaseAssertTrue(!(cond))

#define TestCaseAssertEq(valLeft, valRight) \
        TestCaseAssertTrue((valLeft) == (valRight), print("valLeft=%d != valRight=%d", valLeft,valRight))

#define TestCaseAssertNeq(valLeft, valRight) \
        TestCaseAssertTrue((valLeft) != (valRight), print("valLeft=%d == valRight=%d", valLeft,valRight))

#define TestSuiteExecute(name) \
{ \
    fprintf(stdout, "Executing test suite %s!\n", #name); \
    name(); \
}

#define NUM_OF(array) (sizeof(array)/sizeof(array[0]))

void queueEmptyErrorHandler(const tQueue *q)
{
    (void)q;
    printf("queueEmptyErrorHandler!\n");
    exit(1);
}

static void testSuite0(void)
{
    QUEUE_CREATE(q, 2)
    tQueueData data;
    TestCaseAssertEq(queueInit(&q), 0);
    TestCaseAssertEq(queueGetNum(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGet(&q, &data), 1);

    TestCaseAssertEq(queuePut(&q, 1), 0);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGetIn(&q), 1);
    TestCaseAssertEq(queueGetOut(&q), 0);

    TestCaseAssertEq(queueGet(&q, &data), 0);
    TestCaseAssertEq(data, 1);
    TestCaseAssertEq(queueGetNum(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGetIn(&q), 1);
    TestCaseAssertEq(queueGetOut(&q), 1);
    TestCaseAssertEq(queueGet(&q, &data), 1);

    TestCaseAssertEq(queuePut(&q, 5), 0);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGetIn(&q), 2);
    TestCaseAssertEq(queueGetOut(&q), 1);

    TestCaseAssertEq(queuePut(&q, 10), 0);
    TestCaseAssertEq(queueGetNum(&q), 2);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);
    TestCaseAssertEq(queueGetIn(&q), 3);
    TestCaseAssertEq(queueGetOut(&q), 1);

    TestCaseAssertEq(queuePut(&q, 12), 1);
    TestCaseAssertEq(queueGetNum(&q), 2);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);

    TestCaseAssertEq(queueGetData(&q), 5);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGetIn(&q), 3);
    TestCaseAssertEq(queueGetOut(&q), 2);

    TestCaseAssertEq(queueGetData(&q), 10);
    TestCaseAssertEq(queueGetNum(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGetIn(&q), 3);
    TestCaseAssertEq(queueGetOut(&q), 3);

    TestCaseAssertEq(queuePut(&q, 15), 0);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGetIn(&q), 0);
    TestCaseAssertEq(queueGetOut(&q), 3);

    TestCaseAssertEq(queuePut(&q, 20), 0);
    TestCaseAssertEq(queueGetNum(&q), 2);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);
    TestCaseAssertEq(queueGetIn(&q), 1);
    TestCaseAssertEq(queueGetOut(&q), 3);

    TestCaseAssertEq(queuePut(&q, 12), 1);
    TestCaseAssertEq(queueGetNum(&q), 2);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);

    TestCaseAssertEq(queueGetData(&q), 15);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGetIn(&q), 1);
    TestCaseAssertEq(queueGetOut(&q), 0);

    TestCaseAssertEq(queuePut(&q, 25), 0);
    TestCaseAssertEq(queueGetNum(&q), 2);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);
    TestCaseAssertEq(queueGetIn(&q), 2);
    TestCaseAssertEq(queueGetOut(&q), 0);

    TestCaseAssertEq(queueGetData(&q), 20);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGetIn(&q), 2);
    TestCaseAssertEq(queueGetOut(&q), 1);

    TestCaseAssertEq(queueGetData(&q), 25);
    TestCaseAssertEq(queueGetNum(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGetIn(&q), 2);
    TestCaseAssertEq(queueGetOut(&q), 2);
}

static void testSuite1(void)
{
    const unsigned dataArrayNum = 128;
    QUEUE_CREATE(q, dataArrayNum)
    tQueueData data;
    TestCaseAssertEq(queueInit(&q), 0);
    TestCaseAssertEq(queueGetNum(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGet(&q, &data), 1);

    for (tQueueData idx = 0; idx < dataArrayNum; idx++)
    {
        //printf("testSuite1 put idx=%u\n", (unsigned)idx);
        TestCaseAssertEq(queueGetNum(&q), idx);
        TestCaseAssertEq(queuePut(&q, idx), 0);
        TestCaseAssertEq(queueGetNum(&q), idx + 1);
        TestCaseAssertEq(queueIsEmpty(&q), 0);
        if (idx < (dataArrayNum - 1))
        {
            TestCaseAssertEq(queueIsFull(&q), 0);
        }
        TestCaseAssertEq(queueGetIn(&q), idx + 1);
        TestCaseAssertEq(queueGetOut(&q), 0);
    }
    TestCaseAssertEq(queueIsFull(&q), 1);
    TestCaseAssertEq(queuePut(&q, 0), 1);

    for (tQueueData idx = 0; idx < dataArrayNum; idx++)
    {
        //printf("testSuite1 get idx=%u\n", (unsigned)idx);
        TestCaseAssertEq(queueGetData(&q), idx);
        TestCaseAssertEq(queueGetNum(&q), dataArrayNum - idx - 1);
        if (idx < (dataArrayNum - 1))
        {
            TestCaseAssertEq(queueIsEmpty(&q), 0);
        }
        TestCaseAssertEq(queueIsFull(&q), 0);
        TestCaseAssertEq(queueGetIn(&q), dataArrayNum);
        TestCaseAssertEq(queueGetOut(&q), idx + 1);
    }
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    //TestCaseAssertEq(queuePut(&q, 0), 1);

    for (tQueueData idx = 0; idx < dataArrayNum; idx++)
    {
        //printf("testSuite1 put idx=%u\n", (unsigned)idx);
        TestCaseAssertEq(queueGetNum(&q), idx);
        TestCaseAssertEq(queuePut(&q, idx), 0);
        TestCaseAssertEq(queueGetNum(&q), idx + 1);
        TestCaseAssertEq(queueIsEmpty(&q), 0);
        if (idx < (dataArrayNum - 1))
        {
            TestCaseAssertEq(queueIsFull(&q), 0);
            TestCaseAssertEq(queueGetIn(&q), dataArrayNum + idx + 1);
        }
        TestCaseAssertEq(queueGetOut(&q), dataArrayNum);
    }
    TestCaseAssertEq(queueIsFull(&q), 1);
    TestCaseAssertEq(queueGetIn(&q), 0);

    for (tQueueData idx = 0; idx < dataArrayNum; idx++)
    {
        //printf("testSuite1 get idx=%u\n", (unsigned)idx);
        TestCaseAssertEq(queueGetData(&q), idx);
        TestCaseAssertEq(queueGetNum(&q), dataArrayNum - idx - 1);
        if (idx < (dataArrayNum - 1))
        {
            TestCaseAssertEq(queueIsEmpty(&q), 0);
            TestCaseAssertEq(queueGetOut(&q), dataArrayNum + idx + 1);
        }
        TestCaseAssertEq(queueIsFull(&q), 0);
        TestCaseAssertEq(queueGetIn(&q), 0);
    }
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueGetOut(&q), 0);

    /* testing shifted access */
    TestCaseAssertEq(queuePut(&q, 0), 0);
    TestCaseAssertEq(queuePut(&q, 0), 0);
    TestCaseAssertEq(queuePut(&q, 0), 0);
    TestCaseAssertEq(queueGetNum(&q), 3);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueGetIn(&q), 3);
    TestCaseAssertEq(queueGetOut(&q), 0);
    TestCaseAssertEq(queueGetData(&q), 0);
    TestCaseAssertEq(queueGetData(&q), 0);
    TestCaseAssertEq(queueGetData(&q), 0);
    TestCaseAssertEq(queueGetNum(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueGetIn(&q), 3);
    TestCaseAssertEq(queueGetOut(&q), 3);

    for (tQueueData idx = 0; idx < dataArrayNum; idx++)
    {
        //printf("testSuite1 put idx=%u\n", (unsigned)idx);
        TestCaseAssertEq(queueGetNum(&q), idx);
        TestCaseAssertEq(queuePut(&q, idx), 0);
        TestCaseAssertEq(queueGetNum(&q), idx + 1);
        TestCaseAssertEq(queueIsEmpty(&q), 0);
        if (idx < (dataArrayNum - 1))
        {
            TestCaseAssertEq(queueIsFull(&q), 0);
        }
    }
    TestCaseAssertEq(queueIsFull(&q), 1);
    TestCaseAssertEq(queueGetIn(&q), 3 + dataArrayNum);
    TestCaseAssertEq(queueGetOut(&q), 3);

    for (tQueueData idx = 0; idx < dataArrayNum; idx++)
    {
        //printf("testSuite1 get idx=%u\n", (unsigned)idx);
        TestCaseAssertEq(queueGetData(&q), idx);
        TestCaseAssertEq(queueGetNum(&q), dataArrayNum - idx - 1);
        if (idx < (dataArrayNum - 1))
        {
            TestCaseAssertEq(queueIsEmpty(&q), 0);
        }
        TestCaseAssertEq(queueIsFull(&q), 0);
    }
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueGetIn(&q), 3 + dataArrayNum);
    TestCaseAssertEq(queueGetOut(&q), 3 + dataArrayNum);

    for (tQueueData idx = 0; idx < dataArrayNum; idx++)
    {
        //printf("testSuite1 put idx=%u\n", (unsigned)idx);
        TestCaseAssertEq(queueGetNum(&q), idx);
        TestCaseAssertEq(queuePut(&q, idx), 0);
        TestCaseAssertEq(queueGetNum(&q), idx + 1);
        TestCaseAssertEq(queueIsEmpty(&q), 0);
        if (idx < (dataArrayNum - 1))
        {
            TestCaseAssertEq(queueIsFull(&q), 0);
        }
    }
    TestCaseAssertEq(queueIsFull(&q), 1);
    TestCaseAssertEq(queueGetIn(&q), 3);
    TestCaseAssertEq(queueGetOut(&q), 3 + dataArrayNum);

    for (tQueueData idx = 0; idx < dataArrayNum; idx++)
    {
        //printf("testSuite1 get idx=%u\n", (unsigned)idx);
        TestCaseAssertEq(queueGetData(&q), idx);
        TestCaseAssertEq(queueGetNum(&q), dataArrayNum - idx - 1);
        if (idx < (dataArrayNum - 1))
        {
            TestCaseAssertEq(queueIsEmpty(&q), 0);
        }
        TestCaseAssertEq(queueIsFull(&q), 0);
    }
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueGetIn(&q), 3);
    TestCaseAssertEq(queueGetOut(&q), 3);

}

static void testSuite2(void)
{
    QUEUE_CREATE(q0, 127)
    TestCaseAssertEq(queueInit(&q0), 0);

    QUEUE_CREATE(q1, 128)
    TestCaseAssertEq(queueInit(&q1), 0);

    QUEUE_CREATE(q2, 129)
    TestCaseAssertEq(queueInit(&q2), 1);
}

static void testSuite3(void)
{
    const unsigned dataArrayNum = 127;
    QUEUE_CREATE(q, dataArrayNum)
    TestCaseAssertEq(queueInit(&q), 0);
    tQueueData data[16];
    TestCaseAssertEq(queueRead(&q, data, NUM_OF(data)), 0);
    TestCaseAssertEq(queuePut(&q, 0), 0);
    TestCaseAssertEq(queueRead(&q, data, NUM_OF(data)), 1);
    TestCaseAssertEq(data[0], 0);
    TestCaseAssertEq(queuePut(&q, 2), 0);
    TestCaseAssertEq(queuePut(&q, 4), 0);
    TestCaseAssertEq(queueRead(&q, data, NUM_OF(data)), 2);
    TestCaseAssertEq(data[0], 2);
    TestCaseAssertEq(data[1], 4);
    data[0] = 3; data[1] = 6; data[2] = 9; data[3] = 12;
    TestCaseAssertEq(queueWrite(&q, data, 4), 4);
    memset(data, 0, sizeof(data));
    TestCaseAssertEq(queueRead(&q, data, NUM_OF(data)), 4);
    TestCaseAssertEq(data[0], 3);
    TestCaseAssertEq(data[1], 6);
    TestCaseAssertEq(data[2], 9);
    TestCaseAssertEq(data[3], 12);
    TestCaseAssertEq(queueWrite(&q, data, NUM_OF(data)), NUM_OF(data));
    TestCaseAssertEq(queueRead(&q, data, NUM_OF(data)), NUM_OF(data));
    TestCaseAssertEq(queueGetNum(&q), 0);
    for (tQueueData idx = 0; idx < dataArrayNum/NUM_OF(data); idx++)
    {
        TestCaseAssertEq(queueWrite(&q, data, NUM_OF(data)), NUM_OF(data));
    }
    TestCaseAssertEq(queueWrite(&q, data, NUM_OF(data)), dataArrayNum % NUM_OF(data));
    TestCaseAssertEq(queueGetNum(&q), dataArrayNum);
    for (tQueueData idx = 0; idx < dataArrayNum/NUM_OF(data); idx++)
    {
        TestCaseAssertEq(queueRead(&q, data, NUM_OF(data)), NUM_OF(data));
    }
    TestCaseAssertEq(queueRead(&q, data, NUM_OF(data)), dataArrayNum % NUM_OF(data));
    TestCaseAssertEq(queueGetNum(&q), 0);
}

#define MEMCPY(dst, ...) \
do { \
    tQueueData __data[] = {__VA_ARGS__}; \
    memcpy(dst, __data, sizeof(__data)); \
}while(0)

static void testSuite4(void)
{
    const unsigned dataArrayNum = 5;
    QUEUE_CREATE(q, dataArrayNum)
    TestCaseAssertEq(queueInit(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);

    tQueueData dataW[16];
    //tQueueData dataR[16];
    MEMCPY(dataW, 1, 2, 3);
    TestCaseAssertEq(queueWrite(&q, dataW, 3), 3);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    tQueueIdx num = 5;
    tQueueData *drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 3);
    TestCaseAssertEq(memcmp(dataW, drPtr, 3), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);

    tQueueData dataW1[16];
    MEMCPY(dataW1, 6, 5);
    TestCaseAssertEq(queueWrite(&q, dataW1, 2), 2);
    TestCaseAssertEq(queueIsFull(&q), 1);
    num = 5;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 5);
    TestCaseAssertEq(memcmp(dataW, drPtr, 3), 0);
    TestCaseAssertEq(memcmp(dataW1, drPtr + 3, 2), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);

    TestCaseAssertEq(queueRemoveData(&q, 1), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    num = 5;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 4);
    TestCaseAssertEq(memcmp(dataW + 1, drPtr, 2), 0);
    TestCaseAssertEq(memcmp(dataW1, drPtr + 2, 2), 0);

    // 4 bytes (1..4) in the queue
    TestCaseAssertEq(queuePut(&q, 22), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);
    num = 5;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 4);
    TestCaseAssertEq(memcmp(dataW + 1, drPtr, 2), 0);
    TestCaseAssertEq(memcmp(dataW1, drPtr + 2, 2), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);

    // 5 bytes (1..5) in the queue
    TestCaseAssertEq(queueRemoveData(&q, 1), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 3);
    TestCaseAssertEq(memcmp(dataW + 2, drPtr, 1), 0);
    TestCaseAssertEq(memcmp(dataW1, drPtr + 1, 2), 0);

    // 4 bytes (2..5) in the queue
    TestCaseAssertEq(queueRemoveData(&q, 3), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 1);
    TestCaseAssertEq(*drPtr, 22);
    TestCaseAssertEq(queueGetIn(&q), 6);
    TestCaseAssertEq(queueGetOut(&q), 5);

    // 1 bytes (5..5) in the queue
    MEMCPY(dataW, 11, 12, 13, 14);
    TestCaseAssertEq(queueWrite(&q, dataW, 4), 4);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);
    num = 5;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 5);
    TestCaseAssertEq(*drPtr, 22);
    TestCaseAssertEq(memcmp(dataW, drPtr + 1, 4), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);

    // 5 bytes (5..9) in the queue
    TestCaseAssertEq(queueRemoveData(&q, 1), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    num = 5;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 4);
    TestCaseAssertEq(memcmp(dataW, drPtr, 4), 0);

    // 4 bytes (6..9) in the queue
    TestCaseAssertEq(queuePut(&q, 33), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);
    num = 5;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 4);
    TestCaseAssertEq(memcmp(dataW, drPtr, 4), 0);

    // 5 bytes (6..9 and 0..0) in the queue
    TestCaseAssertEq(queueRemoveData(&q, 2), 0);
    // 1 bytes (0..0) in the queue
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    num = 5;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 2);
    TestCaseAssertEq(memcmp(dataW + 2, drPtr, 2), 0);

    // 3 bytes (8..9 and 0..0) in the queue
    TestCaseAssertEq(queueRemoveData(&q, 2), 0);
    // 1 bytes (0..0) in the queue
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    num = 5;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 1);
    TestCaseAssertEq(drPtr[0], 33);

    // 1 bytes (0..0) in the queue
    MEMCPY(dataW, 11, 12, 13, 14);
    TestCaseAssertEq(queueWrite(&q, dataW, 4), 4);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);
    num = 6;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 5);
    TestCaseAssertEq(drPtr[0], 33);
    TestCaseAssertEq(memcmp(dataW , drPtr + 1, 4), 0);

    // 5 bytes (0..4) in the queue
    TestCaseAssertEq(queueRemoveData(&q, 2), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    num = 6;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 3);
    TestCaseAssertEq(memcmp(dataW + 1, drPtr, 3), 0);

    // 3 bytes (2..4) in the queue
    TestCaseAssertEq(queueRemoveData(&q, 3), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    num = 6;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertEq(drPtr, NULL);
    TestCaseAssertEq(num, 0);

    // 0 bytes (q pos 5) in the queue
    MEMCPY(dataW, 11, 12, 13, 14);
    TestCaseAssertEq(queueWrite(&q, dataW, 4), 4);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    num = 6;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 4);
    TestCaseAssertEq(memcmp(dataW , drPtr, 4), 0);

    // 4 bytes (5..8) in the queue
    TestCaseAssertEq(queueRemoveData(&q, 3), 0);
    // 1 bytes (8..8) in the queue
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    num = 6;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 1);

    // 1 bytes (8..8) in the queue
    MEMCPY(dataW, 11, 12, 13, 14);
    // 5 bytes (8..9 and 0..2) in the queue
    TestCaseAssertEq(queueWrite(&q, dataW, 4), 4);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);
    num = 6;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 2);
    TestCaseAssertEq(memcmp(dataW , drPtr + 1, 1), 0);

    // 5 bytes (8..9 and 0..2) in the queue
    TestCaseAssertEq(queueRemoveData(&q, 3), 0);
    // 2 bytes (1..2) in the queue
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    num = 6;
    drPtr = queueGetDataBuffer(&q, &num);
    TestCaseAssertNeq(drPtr, NULL);
    TestCaseAssertEq(num, 2);
    TestCaseAssertEq(memcmp(dataW + 2, drPtr, 2), 0);

    //TestCaseAssertEq(queueGetIn(&q), 1);
    //TestCaseAssertEq(queueGetOut(&q), 0);
}

int main(int argc, const char **argv)
{
  (void)argc;
  (void)argv;

  TestSuiteExecute(testSuite0);
  TestSuiteExecute(testSuite1);
  TestSuiteExecute(testSuite2);
  TestSuiteExecute(testSuite3);
  TestSuiteExecute(testSuite4);

  printf("All tests are done!\n");
  printf("Executed test cases: %5d\n", testCaseCnt);
  printf("Failed test cases:   %5d\n", testCaseFailed);
  return 0;
}

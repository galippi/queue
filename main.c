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
        TestCaseAssertTrue((valLeft) == (valRight), print("valLeft=%d == valRight=%d", valLeft,valRight))

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
    tQueue q;
    tQueueData dataArray[128];
    tQueueData data;
    TestCaseAssertEq(queueInit(&q, dataArray, NUM_OF(dataArray)), 0);
    TestCaseAssertEq(queueGetNum(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGet(&q, &data), 1);

    TestCaseAssertEq(queuePut(&q, 1), 0);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 1);
    TestCaseAssertEq(q.out, 0);

    TestCaseAssertEq(queueGet(&q, &data), 0);
    TestCaseAssertEq(data, 1);
    TestCaseAssertEq(queueGetNum(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 1);
    TestCaseAssertEq(q.out, 1);
    TestCaseAssertEq(queueGet(&q, &data), 1);

    TestCaseAssertEq(queuePut(&q, 5), 0);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 2);
    TestCaseAssertEq(q.out, 1);

    TestCaseAssertEq(queuePut(&q, 10), 0);
    TestCaseAssertEq(queueGetNum(&q), 2);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 3);
    TestCaseAssertEq(q.out, 1);

    TestCaseAssertEq(queueGetData(&q), 5);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 3);
    TestCaseAssertEq(q.out, 2);

    TestCaseAssertEq(queueGetData(&q), 10);
    TestCaseAssertEq(queueGetNum(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 3);
    TestCaseAssertEq(q.out, 3);

    TestCaseAssertEq(queuePut(&q, 15), 0);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 4);
    TestCaseAssertEq(q.out, 3);

    TestCaseAssertEq(queuePut(&q, 20), 0);
    TestCaseAssertEq(queueGetNum(&q), 2);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 5);
    TestCaseAssertEq(q.out, 3);

    TestCaseAssertEq(queueGetData(&q), 15);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 5);
    TestCaseAssertEq(q.out, 4);

    TestCaseAssertEq(queuePut(&q, 25), 0);
    TestCaseAssertEq(queueGetNum(&q), 2);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 6);
    TestCaseAssertEq(q.out, 4);

    TestCaseAssertEq(queueGetData(&q), 20);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 6);
    TestCaseAssertEq(q.out, 5);

    TestCaseAssertEq(queueGetData(&q), 25);
    TestCaseAssertEq(queueGetNum(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 6);
    TestCaseAssertEq(q.out, 6);
}

static void testSuite1(void)
{
    tQueue q;
    tQueueData dataArray[128];
    tQueueData data;
    TestCaseAssertEq(queueInit(&q, dataArray, NUM_OF(dataArray)), 0);
    TestCaseAssertEq(queueGetNum(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(queueGet(&q, &data), 1);

    for (tQueueData idx = 0; idx < NUM_OF(dataArray); idx++)
    {
        //printf("testSuite1 put idx=%u\n", (unsigned)idx);
        TestCaseAssertEq(queuePut(&q, idx), 0);
        TestCaseAssertEq(queueGetNum(&q), idx + 1);
        TestCaseAssertEq(queueIsEmpty(&q), 0);
        if (idx < (NUM_OF(dataArray) - 1))
        {
            TestCaseAssertEq(queueIsFull(&q), 0);
        }
        TestCaseAssertEq(q.in, idx + 1);
        TestCaseAssertEq(q.out, 0);
    }
    TestCaseAssertEq(queueIsFull(&q), 1);

    for (tQueueData idx = 0; idx < NUM_OF(dataArray); idx++)
    {
        //printf("testSuite1 get idx=%u\n", (unsigned)idx);
        TestCaseAssertEq(queueGetData(&q), idx);
        TestCaseAssertEq(queueGetNum(&q), NUM_OF(dataArray) - idx - 1);
        if (idx < (NUM_OF(dataArray) - 1))
        {
            TestCaseAssertEq(queueIsEmpty(&q), 0);
        }
        TestCaseAssertEq(queueIsFull(&q), 0);
        TestCaseAssertEq(q.in, NUM_OF(dataArray));
        TestCaseAssertEq(q.out, idx + 1);
    }
    TestCaseAssertEq(queueIsEmpty(&q), 1);

    for (tQueueData idx = 0; idx < NUM_OF(dataArray); idx++)
    {
        //printf("testSuite1 put idx=%u\n", (unsigned)idx);
        TestCaseAssertEq(queuePut(&q, idx), 0);
        TestCaseAssertEq(queueGetNum(&q), idx + 1);
        TestCaseAssertEq(queueIsEmpty(&q), 0);
        if (idx < (NUM_OF(dataArray) - 1))
        {
            TestCaseAssertEq(queueIsFull(&q), 0);
            TestCaseAssertEq(q.in, NUM_OF(dataArray) + idx + 1);
        }
        TestCaseAssertEq(q.out, NUM_OF(dataArray));
    }
    TestCaseAssertEq(queueIsFull(&q), 1);
    TestCaseAssertEq(q.in, 0);

    for (tQueueData idx = 0; idx < NUM_OF(dataArray); idx++)
    {
        //printf("testSuite1 get idx=%u\n", (unsigned)idx);
        TestCaseAssertEq(queueGetData(&q), idx);
        TestCaseAssertEq(queueGetNum(&q), NUM_OF(dataArray) - idx - 1);
        if (idx < (NUM_OF(dataArray) - 1))
        {
            TestCaseAssertEq(queueIsEmpty(&q), 0);
            TestCaseAssertEq(q.out, NUM_OF(dataArray) + idx + 1);
        }
        TestCaseAssertEq(queueIsFull(&q), 0);
        TestCaseAssertEq(q.in, 0);
    }
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(q.out, 0);
}

static void testSuite2(void)
{
    tQueue q;
    tQueueData dataArray0[128];
    TestCaseAssertEq(queueInit(&q, dataArray0, NUM_OF(dataArray0)), 0);

    tQueueData dataArray1[129];
    TestCaseAssertEq(queueInit(&q, dataArray1, NUM_OF(dataArray1)), 1);
}

static void testSuite3(void)
{
    tQueue q;
    tQueueData dataArray[128];
    tQueueData data[16];
    TestCaseAssertEq(queueInit(&q, dataArray, NUM_OF(dataArray)), 0);
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
    for (tQueueData idx = 0; idx < NUM_OF(dataArray)/NUM_OF(data); idx++)
    {
        TestCaseAssertEq(queueWrite(&q, data, NUM_OF(data)), NUM_OF(data));
    }
    TestCaseAssertEq(queueWrite(&q, data, NUM_OF(data)), NUM_OF(dataArray) % NUM_OF(data));
    TestCaseAssertEq(queueGetNum(&q), NUM_OF(dataArray));
    for (tQueueData idx = 0; idx < NUM_OF(dataArray)/NUM_OF(data); idx++)
    {
        TestCaseAssertEq(queueRead(&q, data, NUM_OF(data)), NUM_OF(data));
    }
    TestCaseAssertEq(queueRead(&q, data, NUM_OF(data)), NUM_OF(dataArray) % NUM_OF(data));
    TestCaseAssertEq(queueGetNum(&q), 0);
}

int main(int argc, const char **argv)
{
  (void)argc;
  (void)argv;

  TestSuiteExecute(testSuite0);
  TestSuiteExecute(testSuite1);
  TestSuiteExecute(testSuite2);
  TestSuiteExecute(testSuite3);

  printf("All tests are done!\n");
  printf("Executed test cases: %5d\n", testCaseCnt);
  printf("Failed test cases:   %5d\n", testCaseFailed);
  return 0;
}

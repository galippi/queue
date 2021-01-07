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
    tQueueData dataArray[2];
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
    TestCaseAssertEq(queueIsFull(&q), 1);
    TestCaseAssertEq(q.in, 3);
    TestCaseAssertEq(q.out, 1);

    TestCaseAssertEq(queuePut(&q, 12), 1);
    TestCaseAssertEq(queueGetNum(&q), 2);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);

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
    TestCaseAssertEq(q.in, 0);
    TestCaseAssertEq(q.out, 3);

    TestCaseAssertEq(queuePut(&q, 20), 0);
    TestCaseAssertEq(queueGetNum(&q), 2);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);
    TestCaseAssertEq(q.in, 1);
    TestCaseAssertEq(q.out, 3);

    TestCaseAssertEq(queuePut(&q, 12), 1);
    TestCaseAssertEq(queueGetNum(&q), 2);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);

    TestCaseAssertEq(queueGetData(&q), 15);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 1);
    TestCaseAssertEq(q.out, 0);

    TestCaseAssertEq(queuePut(&q, 25), 0);
    TestCaseAssertEq(queueGetNum(&q), 2);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 1);
    TestCaseAssertEq(q.in, 2);
    TestCaseAssertEq(q.out, 0);

    TestCaseAssertEq(queueGetData(&q), 20);
    TestCaseAssertEq(queueGetNum(&q), 1);
    TestCaseAssertEq(queueIsEmpty(&q), 0);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 2);
    TestCaseAssertEq(q.out, 1);

    TestCaseAssertEq(queueGetData(&q), 25);
    TestCaseAssertEq(queueGetNum(&q), 0);
    TestCaseAssertEq(queueIsEmpty(&q), 1);
    TestCaseAssertEq(queueIsFull(&q), 0);
    TestCaseAssertEq(q.in, 2);
    TestCaseAssertEq(q.out, 2);
}

static void testSuite1(void)
{
    tQueue q;
    tQueueData dataArray[32];
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

int main(int argc, const char **argv)
{
  (void)argc;
  (void)argv;

  testSuite0();
  testSuite1();

  printf("All tests are done!\n");
  printf("Executed test cases: %5d\n", testCaseCnt);
  printf("Failed test cases:   %5d\n", testCaseFailed);
  return 0;
}

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <minwindef.h>
#include <sysinfoapi.h>

#define ARR_SIZE 1000000
#define THREAD_MAX 5

int *wrkArray;

struct taskStruct {
    int tsk_low;
    int tsk_high;
};

void merge(int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int k = low;
    int i, j;

    int *left = malloc(n1 * sizeof(int));
    int *right = malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        left[i] = wrkArray[i + low];

    for (i = 0; i < n2; i++)
        right[i] = wrkArray[i + mid + 1];

    i = j = 0;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            wrkArray[k++] = left[i++];
        else
            wrkArray[k++] = right[j++];
    }

    while (i < n1)
        wrkArray[k++] = left[i++];

    while (j < n2)
        wrkArray[k++] = right[j++];

    free(left);
    free(right);
}

void mergeSort(int low, int high) {
    int mid = low + (high - low) / 2;

    if (low < high) {
        mergeSort(low, mid);
        mergeSort(mid + 1, high);
        merge(low, mid, high);
    }
}

void *mergeSortProc(void *arg) {
    struct taskStruct *tsk = arg;
    int low, high;

    low = tsk->tsk_low;
    high = tsk->tsk_high;

    int mid = low + (high - low) / 2;

    if (low < high) {
        mergeSort(low, mid);
        mergeSort(mid + 1, high);
        merge(low, mid, high);
    }

    return 0;
}

int treadsMerge() {
    int low = 0;
    int len = ARR_SIZE / THREAD_MAX;
    struct taskStruct *task;
    struct taskStruct tasklist[THREAD_MAX];
    pthread_t threads[THREAD_MAX];
    wrkArray = malloc(sizeof(int) * ARR_SIZE);

    for (int i = 0; i < ARR_SIZE; i++)
        wrkArray[i] = rand();

    for (int i = 0; i < THREAD_MAX; i++, low += len) {
        task = &tasklist[i];
        task->tsk_low = low;
        task->tsk_high = low + len - 1;
        if (i == (THREAD_MAX - 1))
            task->tsk_high = ARR_SIZE - 1;
    }

    DWORD dwStart = GetTickCount();
    for (int i = 0; i < THREAD_MAX; i++) {
        task = &tasklist[i];
        pthread_create(&threads[i], NULL, mergeSortProc, task);
    }

    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], NULL);

    struct taskStruct *tskm = &tasklist[0];
    for (int i = 1; i < THREAD_MAX; i++) {
        struct taskStruct *tsk = &tasklist[i];
        merge(tskm->tsk_low, tsk->tsk_low - 1, tsk->tsk_high);
    }

    DWORD dwEnd = GetTickCount();
    DWORD wrkTime = dwEnd - dwStart;
    printf("Array size: %d\n", ARR_SIZE);
    printf("Thread count: %d\n", THREAD_MAX);
    printf("Tick for threads: %ld\n", wrkTime);
    //printf("\n\nSorted array:");
    //for (int i = 0; i < ARR_SIZE; i++)
    //  printf(" %d", wrkArray[i]);
    //printf("\n");

    return 0;
}

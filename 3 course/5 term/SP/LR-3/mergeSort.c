#include <stdio.h>

#define ARR_SIZE_SECOND 1000000

int *wrkArraySecond;
int *b;

void merging(int low, int mid, int high) {
    int l1, l2, i;

    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
        if(wrkArraySecond[l1] <= wrkArraySecond[l2])
            b[i] = wrkArraySecond[l1++];
        else
            b[i] = wrkArraySecond[l2++];
    }

    while(l1 <= mid)
        b[i++] = wrkArraySecond[l1++];

    while(l2 <= high)
        b[i++] = wrkArraySecond[l2++];

    for(i = low; i <= high; i++)
        wrkArraySecond[i] = b[i];
}

void sort(int low, int high) {
    int mid;

    if(low < high) {
        mid = (low + high) / 2;
        sort(low, mid);
        sort(mid+1, high);
        merging(low, mid, high);
    } else {
        return;
    }
}

int mergeSortWithoutThreads() {
    wrkArraySecond = malloc(sizeof(int) * ARR_SIZE_SECOND);
    b = malloc(sizeof(int) * ARR_SIZE_SECOND - 1);
    for (int i = 0; i < ARR_SIZE_SECOND; i++)
        wrkArraySecond[i] = rand();

    DWORD dwStart = GetTickCount();
    sort(0, ARR_SIZE_SECOND);
    DWORD dwEnd = GetTickCount();
    DWORD wrkTime = dwEnd - dwStart;
    printf("Tick for no threads: %ld\n", wrkTime);
}

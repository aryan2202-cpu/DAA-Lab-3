#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long compBinary = 0;
long compTernary = 0;

int binarySearch(int arr[], int n, int key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        compBinary++;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int ternarySearch(int arr[], int n, int key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid1 = lo + (hi - lo) / 3;
        int mid2 = hi - (hi - lo) / 3;

        compTernary++;
        if (arr[mid1] == key) return mid1;

        compTernary++;
        if (arr[mid2] == key) return mid2;

        compTernary++;
        if (key < arr[mid1]) hi = mid1 - 1;
        else {
            compTernary++;
            if (key > arr[mid2]) lo = mid2 + 1;
            else { lo = mid1 + 1; hi = mid2 - 1; }
        }
    }
    return -1;
}

void fillSorted(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}

int main() {
    int sizes[] = {1000, 10000, 100000, 500000, 1000000, 2000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int repeats = 1000;
    volatile int sink = 0;

    printf("%-10s %-12s %-15s %-12s %-15s\n", "n", "Bin comp", "Bin time(s)", "Tern comp", "Tern time(s)");
    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int *arr = malloc(n * sizeof(int));
        fillSorted(arr, n);

        int key = n - 1;

        compBinary = 0;
        clock_t t1 = clock();
        for (int r = 0; r < repeats; r++) sink += binarySearch(arr, n, key);
        clock_t t2 = clock();
        double binTime = (double)(t2 - t1) / CLOCKS_PER_SEC / repeats;
        long avgBinComp = compBinary / repeats;

        compTernary = 0;
        clock_t t3 = clock();
        for (int r = 0; r < repeats; r++) sink += ternarySearch(arr, n, key);
        clock_t t4 = clock();
        double ternTime = (double)(t4 - t3) / CLOCKS_PER_SEC / repeats;
        long avgTernComp = compTernary / repeats;

        printf("%-10d %-12ld %-15.8f %-12ld %-15.8f\n", n, avgBinComp, binTime, avgTernComp, ternTime);

        free(arr);
    }

    return 0;
}
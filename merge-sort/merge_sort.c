
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge (long *arr, int p, int q, int r);

void merge_sort(long *arr, ssize_t len, int p, int r);

void print_arr(long *arr, size_t len);

int main(void)
{
    char *line;
    size_t buff;    /* Buffer size, don't exceed */
    ssize_t len;    /* "Signed size_t" */

    buff = 200;
    line = (char *) malloc (buff + 1);
    
    long arr[100];
    size_t arrLen = sizeof(arr) / sizeof(arr[0]);
    long *ptr = arr;
    
    while ((len = getline(&line, &buff, stdin)) != EOF) {
        char *end;
        size_t counter = 0;
        for (long i = strtol(line, &end, 10);  /* first is string, then end pointer, then numeric base */
                line != end && counter < arrLen;
                i = strtol(line, &end, 10)) {
            arr[counter++] = i;
            line = end;
        }
        merge_sort(ptr, counter, 0, counter - 1);
        print_arr(ptr, counter);
    }
    return 0;
}

void merge(long *arr, int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;
    long L[n1 + 1];
    long R[n2 + 1];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[low + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    L[n1] = LONG_MAX;
    R[n2] = LONG_MAX;
    int i = 0;
    int j = 0;
    int k;
    for (k = low; k <= high; k++) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
    }
}

void merge_sort(long *arr, ssize_t len, int low, int high)
{
    if (low < high) {
        int mid = (low + high) / 2;
        merge_sort(arr, len, low, mid);
        merge_sort(arr, len, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void print_arr(long *arr, size_t len)
{
    for (int i = 0; i < len - 1; i++) {
        printf("%ld ", arr[i]);
    }
    printf("%ld\n", arr[len - 1]);
}

#include <stdio.h>
#include <stdlib.h>

void partition(long *arr, int low, int high, int *left_pivot, int *right_pivot);

void print_arr(long *arr, size_t len);

void swap(long *a, long *b)
{
    long c = *a;
    *a = *b;
    *b = c;
}

void dual_pivot_quicksort(long *arr, int low, int high)
{
    if (low < high) {
        int left_pivot, right_pivot;
        partition(arr, low, high, &left_pivot, &right_pivot);
        dual_pivot_quicksort(arr, low, left_pivot - 1);
        dual_pivot_quicksort(arr, left_pivot + 1, right_pivot - 1);
        dual_pivot_quicksort(arr, right_pivot + 1, high);
    }
}

void partition(long *arr, int low, int high, int *ret_left_pivot, int *ret_right_pivot)
{
    if (arr[low] > arr[high]) {
        swap(&arr[low], &arr[high]);
    }
    int a = low + 1;
    int b = high - 1;
    int left_pivot = arr[low], right_pivot = arr[high];
    for (int k = low + 1; k <= b; k++) {
        if (arr[k] < left_pivot) {
            swap(&arr[k], &arr[a]);
            a++;
        } else if (arr[k] >= right_pivot) {
            for (; arr[b] > right_pivot && k < b; b--);
            swap(&arr[k], &arr[b]);
            b--;
            if (arr[k] < left_pivot) {
                swap(&arr[k], &arr[a]);
                a++;
            }
        }
    }
    a--;
    b++;
    swap(&arr[low], &arr[a]);
    swap(&arr[high], &arr[b]);
    *ret_left_pivot = a;
    *ret_right_pivot = b;
}

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
        // print_string(line, len);
        char *end;
        size_t counter = 0;
        for (long i = strtol(line, &end, 10);  /* first is string, then end pointer, then numeric base */
                line != end && counter < arrLen;
                i = strtol(line, &end, 10)) {
            arr[counter++] = i;
            line = end;
        }
        dual_pivot_quicksort(ptr, 0, counter - 1);
        print_arr(ptr, counter);
    }
    return 0;
}

void print_arr(long *arr, size_t len)
{
    for (int i = 0; i < len - 1; i++) {
        printf("%ld ", arr[i]);
    }
    printf("%ld\n", arr[len - 1]);
}



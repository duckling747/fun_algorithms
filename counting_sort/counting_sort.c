
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


void print_arr(long *arr, ssize_t length);

void counting_sort(long *arr, ssize_t length);

const int maximum_integer = 10000;

void main(void)
{
    char *line = NULL;
    size_t buff = 0;
    ssize_t len;
        
    size_t nArr = 100;
    long arr[nArr];
    
    while ((len = getline(&line, &buff, stdin)) != EOF) {
        char *end = NULL;
        size_t counter = 0;
        for (long i = strtol(line, &end, 10);
                line != end;
                i = strtol(line, &end, 10)) {
            assert(i >= 0);
            arr[counter++] = i;
            line = end;
        }
        counting_sort(arr, counter);
        print_arr(arr, counter);
    }
}

/*
 * Cannot handle negative numbers (without adding some constant in-between)
 */
void counting_sort(long *arr, ssize_t length)
{
    long *counting_sort_arr = calloc(maximum_integer, sizeof(long));
    // count the instances
    for (int i = 0; i < length; i++) {
        counting_sort_arr[arr[i]]++;
    }
    // put the instances to the original array in order
    for (int x = 0, i = 0; x < maximum_integer; x++) {
        for (int j = 1; j <= counting_sort_arr[x]; j++, i++) {
            arr[i] = x;
        }
    }
    free(counting_sort_arr);
}

void print_arr(long *arr, ssize_t length)
{
    for (int i = 0; i < length - 1; i++) {
        printf("%ld, ", arr[i]);
    }
    printf("%ld\n", arr[length - 1]);
}

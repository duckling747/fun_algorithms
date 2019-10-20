
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct {
    long max_left;
    long max_right;
    long left_plus_right;
} triple;

void max_crossing_subarray(long *arr, int low, int mid, int high, triple *indexes);

void print_arr(long *arr, size_t len);

void find_maximum_subarray(long *arr, int low, int high, triple *rets);

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
        triple p;
        triple *max = &p;
        //max_crossing_subarray(ptr, 0, counter / 2, counter - 1, max);
        find_maximum_subarray(ptr, 0, counter - 1, max);
        print_arr(&ptr[max->max_left], max->max_right - max->max_left + 1);
        printf("Sum is: %d\n", max->left_plus_right);
    }
    return 0;
}

void max_crossing_subarray(long *arr, int low, int mid, int high, triple *ret)
{
    ret->max_left = low;
    ret->max_right = high;    
    long left_sum = LONG_MIN;
    int sum = 0;
    for (int i = mid; i >= low; i--) {
        sum += arr[i];
        if (sum > left_sum) {
            left_sum = sum;
            ret->max_left = i;
        }
    }
    long right_sum = LONG_MIN;
    sum = 0;
    for (int i = mid + 1; i <= high; i++) {
        sum += arr[i];
        if (sum > right_sum) {
            right_sum = sum;
            ret->max_right = i;
        }
    }
    ret->left_plus_right = left_sum + right_sum;
}

void find_maximum_subarray(long *arr, int low, int high, triple *ret)
{
    if (high == low) {
        ret->max_left = low;
        ret->max_right = high;
        ret->left_plus_right = arr[low];
        return;
    } else {
        int mid = (low + high) / 2;
        triple first;
        triple *ptrFirst = &first;
        find_maximum_subarray(arr, low, mid, ptrFirst);
        triple second;
        triple *ptrSecond = &second;
        find_maximum_subarray(arr, mid + 1, high, ptrSecond);
        triple third;
        triple *ptrThird = &third;
        max_crossing_subarray(arr, low, mid, high, ptrThird);
        if (ptrFirst->left_plus_right >= ptrSecond->left_plus_right 
            && ptrFirst->left_plus_right >= ptrThird->left_plus_right) {
            ret->max_left = ptrFirst->max_left;
            ret->max_right = ptrFirst->max_right;
            ret->left_plus_right = ptrFirst->left_plus_right;
            return;
        } else if (ptrSecond->left_plus_right >= ptrFirst->left_plus_right
            && ptrSecond->left_plus_right >= ptrThird->left_plus_right) {
            ret->max_left = ptrSecond->max_left;
            ret->max_right = ptrSecond->max_right;
            ret->left_plus_right = ptrSecond->left_plus_right;
            return;
        } else {
            ret->max_left = ptrThird->max_left;
            ret->max_right = ptrThird->max_right;
            ret->left_plus_right = ptrThird->left_plus_right;
            return;
        }
    }
}

void print_arr(long *arr, size_t len)
{
    for (int i = 0; i < len - 1; i++) {
        printf("%ld ", arr[i]);
    }
    printf("%ld\n", arr[len - 1]);
}

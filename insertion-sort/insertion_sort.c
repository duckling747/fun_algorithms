
#include <stdio.h>
#include <stdlib.h>

void insertion_sort(long *arr, ssize_t len);

void print_string(char *arr, ssize_t len);

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
        // print_string(line, len);
        char *end;
        size_t counter = 0;
        for (long i = strtol(line, &end, 10);  /* first is string, then end pointer, then numeric base */
                line != end && counter < arrLen;
                i = strtol(line, &end, 10)) {
            arr[counter++] = i;
            line = end;
        }
        insertion_sort(ptr, counter);
        print_arr(ptr, counter);
    }
    return 0;
}

void insertion_sort(long *arr, ssize_t len)
{
    for (int j = 1; j < len; j++) {
        long key = arr[j];
        int i;
        for (i = j - 1; i >= 0 && arr[i] > key; i--) {
            arr[i + 1] = arr[i];
        }
        arr[i + 1] = key;
    }
}

void print_string(char *arr, ssize_t len)
{
    for (int i = 0; i < len; i ++) {
        printf("%c", arr[i]);
    }
    printf("\n");
}

void print_arr(long *arr, size_t len)
{
    for (int i = 0; i < len - 1; i++) {
        printf("%ld ", arr[i]);
    }
    printf("%ld\n", arr[len - 1]);
}

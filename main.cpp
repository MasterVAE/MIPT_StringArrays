#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "sorting.h"
#include "array.h"



int cmp(const void* a, const void* b) {
    const char* s1 = *(const char**)a;
    const char* s2 = *(const char**)b;
    return str_cmp(s1, s2);
}

int main()
{
    printf("Starting...\n");

    struct timespec start, end;
    char* buffer;
    size_t size;
    char** text;
    size_t count;

    FILE* input_file = fopen("hamlet.txt", "r");
    FILE* middle_file = fopen("middle.txt", "w");

    printf("Upgrading file...\n");
    
    upgrade(input_file, middle_file);
    fclose(input_file);
    fclose(middle_file);

    printf("Initializing...\n");

    initialize_buffer(&buffer, &size);
    count = initialize_text(&text, buffer, size);

    printf("Sorting...\n");

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);  
    sort(text, count);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);  


    printf("Printing...\n");
    FILE* output_file = fopen("output.txt", "w");
    print(text, count, output_file);
    fclose(output_file);
    


    // text = QSort(text, sizeY);
    // qsort(text, sizeY, sizeof(char*), cmp);

    printf("Freeing...\n");
    free(text);
    free(buffer);

    printf("Ended...\n");

    long delta_us = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec)/1000000;
    printf("Sorting time = %ld ms\n", delta_us);

    return 0;
}
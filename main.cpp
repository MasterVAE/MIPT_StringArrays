#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

void initialize(char** matrix, size_t sizeY, size_t sizeX);
void print(char** matrix, size_t sizeY);
void swap(char** matrix, int y1, int y2);
void allfree(char **matrix, size_t sizeY);
void sort(char ** matrix, size_t sizeY);
void my_fgets(char *str, size_t cnt, FILE* file);
void my_fputs(const char *str, FILE* file);
char *my_getline(char **str, size_t n, FILE *file);

/*
Slavic

char** MergeArray(char** array_1, char** array_2, size_t size_1, size_t size_2, char* compare_string);
char** QSort(char* pointers_array[], size_t array_size);
*/

int main()
{
    const size_t sizeX = 100, sizeY = 14000;
    char** text = (char**)calloc(sizeY, sizeof(char *));
    
    printf("Starting...\n");
    initialize(text, sizeY, sizeX);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);  
    
    printf("Sorting...\n");
    sort(text, sizeY);
    /*
    Slavic

    QSort(text, sizeY);
    */

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    printf("Printing...\n");
    print(text, sizeY);

    printf("Freeing...\n");
    allfree(text, sizeY);

    printf("Ended...\n");

    long delta_us = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec)/1000000;
    printf("Sorting time = %ld ms\n", delta_us);

    return 0;
}

void print(char** matrix, size_t sizeY)
{
    FILE* output_file = fopen("output.txt", "w");
    
    assert(matrix != NULL);

    for(size_t y = 0; y < sizeY; y++)
    {
        my_fputs(matrix[y], output_file);
    }
}

void initialize(char** matrix, size_t sizeY, size_t sizeX)
{
    assert(matrix != NULL);

    FILE* input_file = fopen("input.txt", "r");
    for(size_t y = 0; y < sizeY; y++)
    {
        char* b = (char*)calloc(sizeX, sizeof(char));

        assert(b != NULL);
        
        size_t m = sizeX;
        //getline(&b, &m, input_file);
        //my_getline(&b, sizeX, input_file);
        my_fgets(b, sizeX, input_file);

        matrix[y] = b;
    }
    fclose(input_file);
}

void swap(char** matrix, int y1, int y2)
{
    assert(matrix != NULL);

    char* buffer;
    buffer = matrix[y1];
    matrix[y1] = matrix[y2];
    matrix[y2] = buffer;
}

void allfree(char **matrix, size_t sizeY)
{
    assert(matrix != NULL);

    for(size_t i = 0; i < sizeY; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void sort(char** data, size_t size)
{
    assert(data != NULL);

    if(size == 0 || size == 1)
    {
        return;
    }


    char** data_sm = (char**)calloc(size-1, sizeof(char*));
    char** data_bg = (char**)calloc(size-1, sizeof(char*));


    assert(data_sm != NULL);
    assert(data_bg != NULL);

    size_t size_sm = 0;
    size_t size_bg = 0;

    char* middle = data[0];

    for(size_t i = 1; i < size; i++)
    {
        if(strcmp(data[i], middle) < 0)
        {
            data_sm[size_sm++] = data[i];
        }
        else
        {
            data_bg[size_bg++] = data[i];
        }
    }

    sort(data_sm, size_sm);
    sort(data_bg, size_bg);

    size_t global_counter = 0;

    for(size_t i = 0; i < size_sm; i++)
    {
        data[global_counter++] = data_sm[i];
    }
    data[global_counter++] = middle;
    for(size_t i = 0; i < size_bg; i++)
    {
        data[global_counter++] = data_bg[i];
    }

    free(data_sm);
    free(data_bg);
}

void my_fgets(char *str, size_t cnt, FILE* file)
{
    assert(str != NULL);

    size_t i = 0;
    char last_char;
    while((i++) < cnt && (last_char = (char)fgetc(file)) != EOF && last_char != '\n')
    {
        *(str++) = last_char;
    }
    *str = '\0';
}

void my_fputs(const char *str, FILE* file)
{
    if(strlen(str) > 1 && strcmp(str, "А") >= 0)
    {
        while(*str != '\0' && *str != EOF)
        {
            fputc(*(str++), file);
        }
        fputc('\n', file);
    }
}

char* my_getline(char **str, size_t max_n, FILE *file)
{
    assert(str != NULL);
    assert(file != NULL);

    char* str_max = (char*)calloc(max_n, sizeof(char));

    assert(str_max != NULL);

    char last_char;
    int counter = 0;

    while((last_char = (char)fgetc(file)) != EOF && last_char != '\n' && last_char != '\0')
    {
        str_max[counter++] = last_char;
    }
    str_max[counter] = '\0';

    size_t len = strlen(str_max);             

    char* string = (char*)calloc(len+1, sizeof(char));
    strcpy(string, str_max);
    free(str_max);

    str = &string;
    return string;
}


/*
Slavic

char** QSort(char* pointers_array[], size_t array_size)
{
    assert(pointers_array != NULL);

    char** array_less = (char**) calloc(array_size, sizeof(char*));
    char** array_more_or_eq = (char**) calloc(array_size, sizeof(char*));

    size_t size_less = 0, size_more_or_eq = 0;

    char* compare_string = pointers_array[0];

    for (size_t count = 0; count < array_size; count++)
    {
        if (strcmp(pointers_array[count], compare_string) < 0)
        {
            array_less[size_less] = pointers_array[count];
            size_less++;
        }
        else if (pointers_array[count] != compare_string)
        {
            array_more_or_eq[size_more_or_eq] = pointers_array[count];
            size_more_or_eq++;
        }
    }

    if (size_less > 1)
    {
        array_less = QSort(array_less, size_less);
    }

    if (size_more_or_eq > 1)
    {
        array_more_or_eq = QSort(array_more_or_eq, size_more_or_eq);
    }

    free(pointers_array);

    char** sort_result = MergeArray(array_less, array_more_or_eq, size_less, size_more_or_eq, compare_string);

    return sort_result;
}

char** MergeArray(char** array_1, char** array_2, size_t size_1, size_t size_2, char* compare_string)
{
    size_t sum_size = size_1 + size_2 + 1;

    char** merged_array = (char**) calloc(sum_size, sizeof(char*));

    for (size_t index = 0; index < size_1; index++)
    {
        merged_array[index] = array_1[index];
    }

    merged_array[size_1] = compare_string;

    for (size_t index = size_1 + 1; index < sum_size; index++)
    {
        merged_array[index] = array_2[index - size_1 - 1];
    }

    free(array_1);
    free(array_2);

    return merged_array;
}
*/

#include <stdlib.h>
#include <assert.h>

#include "sorting.h"

int str_cmp(const char* str1, const char* str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    size_t i = 0;
    while(1)
    {
        if(str1[i] == '\n' || str2[i] == '\n')
        {
            return str1[1] - str2[i];
        }
        else
        {
            if(str1[i] != str2[i])
            {
                return str1[i] - str2[i];
            }
            else
            {
                i++;
            }
        }
    }
}

int str_rcmp(const char* str1, const char* str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    size_t len1 = 0;
    size_t len2 = 0;

    while(str1[len1] != '\n')
    {
        len1++;
    }

    while(str2[len2] != '\n')
    {
        len2++;
    }

    int i = 0;
    while(1)
    {
        if(i >= len1)
        {
            if(i >= len2)
            {
                return 0;
            }
            return -1;
            
        }
        if(i >= len2)
        {
            return 1;
        }


        if(str1[len1 - 1 - i] != str2[len2 - 1 -i])
        {
            return str1[len1 - 1 - i] - str2[len2 - 1 -i];
        }
        else
        {
            i++;
        }
    }
}

void bubble_sort(char** text, size_t count)
{
    assert(text != NULL);

    for(int iter = 0; iter < count-1; iter++)
    {
        for(int i = 0; i < iter; i++)
        {
            if(str_cmp(text[i], text[i+1]) > 0)
            {
                swap(text, i, i+1);
            }
        }
    }
}

void swap(char** matrix, int y1, int y2)
{
    assert(matrix != NULL);

    char* buffer;
    buffer = matrix[y1];
    matrix[y1] = matrix[y2];
    matrix[y2] = buffer;
}

void sort(char** data, size_t size, int (*compare)(const char*, const char*))
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
        if(compare(data[i], middle) < 0)
        {
            data_sm[size_sm++] = data[i];
        }
        else
        {
            data_bg[size_bg++] = data[i];
        }
    }

    sort(data_sm, size_sm, compare);
    sort(data_bg, size_bg, compare);

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
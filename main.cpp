#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void initialize(char** matrix, size_t sizeY, size_t sizeX);
void print(char** matrix, size_t sizeY);
void swap(char** matrix, int y1, int y2);
void allfree(char **matrix, size_t sizeY);
void sort(char ** matrix, size_t sizeY);
void my_fgets(char *str, int cnt, FILE* file);
void my_fputs(const char *str, FILE* file);

int main()
{
    const size_t sizeX = 100, sizeY = 14000;
    char** text = (char**)calloc(sizeY, sizeof(char *));
    
    printf("Starting...\n");
    initialize(text, sizeY, sizeX);

    printf("Sorting...\n");
    sort(text, sizeY);

    printf("Printing...\n");
    print(text, sizeY);

    printf("Freeing...\n");
    allfree(text, sizeY);

    printf("Ended...\n");

    return 0;
}

void print(char** matrix, size_t sizeY)
{
    FILE* output_file = fopen("output.txt", "w");
    
    assert(matrix != NULL);

    for(int y = 0; y < sizeY; y++)
    {
        my_fputs(matrix[y], output_file);
    }
}

void initialize(char** matrix, size_t sizeY, size_t sizeX)
{
    assert(matrix != NULL);

    int c = 0;
    FILE* input_file = fopen("input.txt", "r");
    for(int y = 0; y < sizeY; y++)
    {
        char* b = (char*)calloc(sizeX, sizeof(char));

        assert(b != NULL);
        
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

    for(int i = 0; i < sizeY; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void sort(char** data, size_t size)
{
    assert(data != NULL);

    if(size == 0)
    {
        return;
    }

    char** data_sm = (char**)calloc(size, sizeof(char**));
    char** data_bg = (char**)calloc(size, sizeof(char**));

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

    data_sm[size_sm] = NULL;
    data_bg[size_bg] = NULL;

    sort(data_sm, size_sm);
    sort(data_bg, size_bg);

    size_t global_counter = 0;
    size_t local_counter = 0;

    while((data[global_counter++] = data_sm[local_counter++]) != NULL);

    global_counter--;
    data[global_counter++] = middle;
    local_counter = 0;

    while((data[global_counter++] = data_bg[local_counter++]) != NULL);

    free(data_sm);
    free(data_bg);
}

void my_fgets(char *str, int cnt, FILE* file)
{
    assert(str != NULL);

    int i = 0;
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

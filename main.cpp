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
    
    initialize(text, sizeY, sizeX);
    sort(text, sizeY);
    print(text, sizeY);

    allfree(text, sizeY);

    return 0;
}

void print(char** matrix, size_t sizeY)
{
    FILE* output_file = fopen("output.txt", "w");
    
    assert(matrix != NULL);

    for(int y = 0; y < sizeY; y++)
    {
        printf("%s\n", matrix[y]);
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

void sort(char **matrix, size_t sizeY)
{
    for(size_t i = 0; i < sizeY-1; i++)
    {
        for(size_t j = 0; j < sizeY-1; j++)
        {
           if(strcmp(matrix[j], matrix[j+1]) > 0)
           {
                swap(matrix, j, j+1);
           } 
        }
    }
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
    while(*str != '\0' && *str != EOF)
    {
        fputc(*(str++), file);
    }
    fputc('\n', file);
}

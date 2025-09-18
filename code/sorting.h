#ifndef SORTING
#define SORTING

#include <stdio.h>

void sort(char ** matrix, size_t size);
void swap(char** matrix, int y1, int y2);
void bubble_sort(char** text, size_t count);
int str_cmp(const char* str1, const char* str2);
int str_rcmp(const char* str1, const char* str2);

#endif
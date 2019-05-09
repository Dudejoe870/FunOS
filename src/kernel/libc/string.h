#pragma once

#include <stdint.h>
#include <stddef.h>

size_t strlen(const char* str);
void* memcpy(void* restrict s1, const void* restrict s2, size_t n);
void* memset(void* s, int c, size_t n);
void* memmove(void* s1, const void* s2, size_t n);
char* strtok(char* s, char* delm);
int strcmp(char* s1, char* s2);
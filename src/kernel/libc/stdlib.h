#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "string.h"

char* itoax(int num, char* str, int base, int pad, bool uppercase);
char* itoa(int num, char* str, int base);
int atoi(const char* str);
void* mallocx(size_t size, int align, uint32_t* phys_addr);
void* malloc(size_t size);
#include "string.h"
#include "stdlib.h"

// Get the length of a String
size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len]) ++len;
	return len;
}

// Copy memory from s2 into s1
void* memcpy(void* restrict s1, const void* restrict s2, size_t n) 
{
	for (uint32_t i = 0; i < n; ++i)
		*(uint8_t*)(s1 + i) = *(uint8_t*)(s2 + i);

	return s1;
}

// Set memory at s to c
void* memset(void* s, int c, size_t n) 
{
	for (uint32_t i = 0; i < n; ++i)
		*(uint8_t*)(s + i) = (uint8_t)c;

	return s;
}

// Copy memory from s2 into s1 valid for overlapping regions
void* memmove(void* s1, const void* s2, size_t n)
{
	uint8_t tmp[n];
	
	for (uint32_t i = 0; i < n; ++i)
		tmp[i] = *(uint8_t*)(s2 + i);
	for (uint32_t i = 0; i < n; ++i)
		*(uint8_t*)(s1 + i) = tmp[i];

	return s1;
}

int strcmp(char* s1, char* s2) 
{
    int i;
    for (i = 0; s1[i] == s2[i]; i++) 
	{
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

char* strtok(char* s, char* delm)
{
	static int currIndex = 0;
	if (!s || !delm || s[currIndex] == '\0')
	{
		currIndex = 0;
		return NULL;
	}
	char* W = (char*)malloc(sizeof(char) * 100);
	int i = currIndex, k = 0, j = 0;

	while (s[i] != '\0')
	{
		j = 0;
		while (delm[j] != '\0')
		{
			if (s[i] != delm[j])
				W[k] = s[i];
			else goto It;
			j++;
		}
		i++;
		k++;
	}
	It:
	W[i] = 0;
	currIndex = i + 1;
	return W;
}
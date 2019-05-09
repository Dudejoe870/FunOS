#include "stdlib.h"

#include <stdint.h>

// Integer to Array Extended
char* itoax(int num, char* str, int base, int pad, bool uppercase)
{
	int i = 0;
	bool isNegative = false;
	
	if (num == 0)
	{
		str[i++] = '0';
		while (i < pad-1)
			str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	if (num < 0)
	{
		isNegative = true;
		if (base == 10) num = -num;
	}

	uint32_t unsignNum = (uint32_t)num;

	while (true)
	{
		if (base != 10)
		{
			if (unsignNum != 0)
			{
				uint32_t rem = unsignNum % base;
				str[i] = (rem > 9) ? (rem - 10) + (uppercase ? 'A' : 'a') : rem + '0';
				unsignNum /= base;
			}
			else if (unsignNum == 0 && pad != 0)
				str[i] = '0';
			else
				break;
		}
		else
		{
			if (num != 0)
			{
				int rem = num % base;
				str[i] = (rem > 9) ? (rem - 10) + (uppercase ? 'A' : 'a') : rem + '0';
				num /= base;
			}
			else if (num == 0 && pad != 0)
				str[i] = '0';
			else
				break;
		}
		
		++i;
		if (pad != 0) --pad;
	}

	if (isNegative && base == 10)
		str[i++] = '-';
	
	str[i] = '\0';

	uint32_t j = 0;
	uint32_t k = strlen(str) - 1;

	char orgStr[k + 1];

	while (str[j])
	{
		orgStr[j] = str[j];
		++j;
	}

	j = 0;

	while (str[j])
		str[j++] = orgStr[k--];

	return str;
}

// Integer to Array
char* itoa(int num, char* str, int base)
{
	return itoax(num, str, base, 0, false);
}

// Array to Integer
int atoi(const char* str)
{
	if (*str == '\0')
		return 0;

	int res = 0, sign = 1;
	uint32_t i = 0;
	
	if (str[0] == '-')
	{
		sign = -1;
		++i;
	}

	for (; str[i]; ++i)
	{
		if (str[i] < '0' || str[i] > '9') return 0;
		res = res * 10 + str[i] - '0';
	}

	return res * sign;	
}

uint32_t free_mem_addr = 0x10000;

// WARNING: this does not work like regular malloc!
void* mallocx(size_t size, int align, uint32_t* phys_addr)
{
    if (align == 1 && (free_mem_addr & 0xFFFFF000)) 
	{
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }

    if (phys_addr) *phys_addr = free_mem_addr;

    void* ret = (void*)free_mem_addr;
    free_mem_addr += size;
	return ret;
}

void* malloc(size_t size)
{
	uint32_t dummy;
	return mallocx(size, 1, &dummy);
}
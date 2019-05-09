#include "stdio.h"

#include "tty.h"

int putchar(int c)
{
	terminal_putchar((const char)c, true);
	return c;
}

int puts(const char* s) 
{
	uint32_t i = 0;
	while (s[i])
	{
		if (s[i] == '\0') break;
		putchar(s[i]);

		++i;
	}
	return 0;
}

int printf(const char* restrict str, ...)
{
	va_list args;
	va_start(args, str);

	uint32_t i = 0;
	while (str[i]) 
	{
		const char c = str[i];
		if (str[i+1])
		{
			if (c == '%')
			{
				uint32_t padding = 0;
				while (true)
				{
					const char formatC = str[++i];
					
					// Formatting Characters
					if (formatC == '0')
					{
						char numC[2];
						numC[0] = str[++i];
						numC[1] = '\0';
						padding = (uint32_t)atoi(numC);
					}
					// Conversion Characters
					else if (formatC == 's')
					{
						const char* arg = va_arg(args, const char*);
						puts(arg);
						break;
					}
					else if (formatC == 'u')
					{
						uint32_t arg = va_arg(args, uint32_t);
						char numStr[11] = "";
						itoax(arg, numStr, 10, padding, false);
						puts(numStr);
						break;
					}
					else if (formatC == 'x')
					{
						uint32_t arg = va_arg(args, uint32_t);
						char numStr[9] = "";
						itoax(arg, numStr, 16, padding, false);
						puts(numStr);
						break;
					} 
					else if (formatC == 'X')
					{
						uint32_t arg = va_arg(args, uint32_t);
						char numStr[9] = "";
						itoax(arg, numStr, 16, padding, true);
						puts(numStr);
						break;
					}
					else if (formatC == 'c')
					{
						uint32_t arg = va_arg(args, uint32_t);
						putchar((const char)arg);
						break;
					}
					// Other
					else if (formatC == '%')
					{
						putchar('%');
						break;
					}
					else
					{
						break;
					}
				}
				++i;
				continue;
			}
		}
		putchar(c);

		++i;
	}
	va_end(args);

	return 0;
}
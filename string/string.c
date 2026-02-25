// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */

	char *ptr = destination; // salvez in pointer adresa de la inceput
	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';

	return ptr;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */

	char *ptr = destination;

	while (*source != '\0' && len > 0)
	{
		*destination = *source;
		destination++;
		source++;
		len--;
	}

	while (len > 0)
	{
		*destination = '\0';
		destination++;
		len--;
	}

	return ptr;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	char *ptr = destination;

	while (*destination != '\0')
	{
		destination++;
	}

	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';

	return ptr;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */

	char *ptr = destination;

	while (*destination != '\0')
	{
		destination++;
	}

	while (*source != '\0' && len > 0)
	{
		*destination = *source;
		destination++;
		source++;
		len--;
	}

	*destination = '\0';

	return ptr;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */

	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
		{
			return *str1 - *str2;
		}
		str1++;
		str2++;
	}

	return *str1 - *str2;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */

	while (*str1 != '\0' && *str2 != '\0' && len > 0)
	{
		if (*str1 != *str2)
		{
			return *str1 - *str2;
		}
		str1++;
		str2++;
		len--;
	}

	if (len == 0)
	{
		return 0;
	}

	return *str1 - *str2;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */

	char character = (char)c;

	while (*str != '\0')
	{
		if (*str == character)
		{
			return str;
		}
		str++;
	}

	if (character == '\0')
	{
		return str;
	}

	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */

	char character = (char)c;

	char *ptr = NULL;

	while (*str != '\0')
	{
		if (*str == character)
		{
			ptr = str;
		}
		str++;
	}

	return (char *)ptr;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */

	while (*haystack != '\0')
	{
		char *ptr1 = haystack;
		char *ptr2 = needle;

		while (*ptr1 == *ptr2)
		{
			if (*ptr2 != '\0')
			{
				ptr1++;
				ptr2++;
			}
		}

		if (*ptr2 == '\0')
		{
			return (char *)haystack;
		}
		haystack++;
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
	char *last = NULL;
	while (*haystack != '\0')
	{
		char *ptr1 = haystack;
		char *ptr2 = needle;
		while (*ptr1 == *ptr2)
		{
			if (*ptr2 != '\0')
			{
				ptr1++;
				ptr2++;
			}
			if (*ptr2 == '\0')
			{
				last = haystack;
			}
		}
		haystack++;
	}
	return (char *)last;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	char *ptr1 = (char *)destination;
	char *ptr2 = (char *)source;
	while (num > 0)
	{
		*ptr1 = *ptr2;
		ptr1++;
		ptr2++;
		num--;
	}
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */

	char *ptr1 = (char *)destination;
	char *ptr2 = (char *)source;

	if (destination <= source)
	{
		while (num)
		{
			*ptr1 = *ptr2;
			ptr1++;
			ptr2++;
			num--;
		}
	}else if (destination > source){
		ptr1 += num - 1;
		ptr2 += num - 1;
		while (num)
		{
			*ptr1 = *ptr2;
			ptr1--;
			ptr2--;
			num--;
		}
	}
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */

	char *p1 = (char *)ptr1;
	char *p2 = (char *)ptr2;

	while (num > 0)
	{
		if (*p1 != *p2)
		{
			if (*p1 < *p2)
			{
				return -1;
			}else{
				return 1;
			}
		}
		p1++;
		p2++;
		num--;
	}
	return 0;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */

	char *ptr = (char *)source;

	while (num > 0)
	{
		*ptr = (char)value;
		ptr++;
		num--;
	}
	return source;
}

#include "str.h"
#include <stdlib.h> // for size_t

char* str_cpy(char* dest, char* src){
	char* enter_point = dest;
	do
	{
		*dest++ = *src; 	
	}
	while(*src++);
	return enter_point;
}

char* str_cat(char* dest, char* src){
	char* enter_point = dest;
	while(*dest)dest++;
	do
	{
		*dest++ = *src;
	}
	while(*src++);
	*dest = '\0';
	return enter_point;
}

int str_cmp(char* str1, char* str2)
{
	int ans = 0;
	while(*str1 && *str2)
	{
		ans = *str1++ - *str2++;
		if(ans)
			return ans;
	}
	return *str1 - *str2;
}

size_t str_len(char* str)
{
	size_t n = 0;
	while(*str++)n++;
	return n;
}

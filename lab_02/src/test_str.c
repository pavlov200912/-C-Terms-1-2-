#include "test_str.h"
#include "str.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void test_str_cpy(){
	printf("________________________________ \n Testing function str_cpy() \n ________________________________ \n");
	char a[5][40] = {"SPBAU", "USSR", "Tea", "WA", "author"};
	char b[5][20] = {"SPBGU", "Russia", "Coffee", "OK", "S_P_"};
	int i = 0;
	while(i < 5)
	{
		char c[40];
		char d[40];
		strcpy(d, a[i]);
		strcpy(c, a[i]);
		str_cpy(a[i], b[i]);
		strcpy(c, b[i]);
		int j = strcmp(c, a[i]);
		if(j == 0)
			printf("Test %d : OK \n", i + 1);
		else 
			printf("Test %d : WA \n", i + 1);
		printf("str_cpy(\"%s\", \"%s\") : \"%s\" \n", d, b[i], a[i]);
		i++;
	}
}

void test_str_cat(){
	printf("________________________________ \n Testing function str_cat()\n________________________________ \n");
	char a[5][40] = {"Hello", "Ivan", "Modern", "C", "S_"};
	char b[5][20] = {" World!", " Pavlov", " Programming", "++", "P_"};
	int i = 0;
	while(i < 5)
	{
		char c[40];
		char d[40];
		strcpy(d, a[i]);
		strcpy(c, a[i]);
		str_cat(a[i], b[i]);
		strcat(c, b[i]);
		int j = strcmp(c, a[i]);
		if(j == 0)
			printf("Test %d : OK \n", i + 1);
		else 
			printf("Test %d : WA \n", i + 1);
		printf("str_cat(\"%s\", \"%s\") : \"%s\" \n", d, b[i], a[i]);
		i++;
	}
}

void test_str_cmp(){
	printf("________________________________ \n Testing function str_cmp()\n________________________________ \n");
	char a[5][40] = {"SPBAU", "C++", "C", "Pavlov", "Correct"};
	char b[5][20] = {"SPBGU", "c++", "C#", "Pav1ov", "Correct"};
	int i = 0;
	while(i < 5)
	{
		char c[40];
		char d[40];
		strcpy(c, a[i]);
		strcpy(d, a[i]);
		int o1 = str_cmp(a[i], b[i]);
		int o2 = strcmp(c, b[i]);
		char* ans;
		if(o1 == 0 && o2 == 0){
			printf("Test %d : OK \n", i + 1);
			ans = "Equal";
		}
		else if(o1 * o2 > 0){
			printf("Test %d : OK \n", i + 1);
			ans = "NonEqual";
		}
		else{
			printf("Test %d : WA \n", i + 1);
			ans = "NonEqual";
		}
			
		printf("str_cmp(\"%s\", \"%s\") : %s \n", d, b[i], ans);
		i++;
	}
}


void test_str_len(){
	printf("________________________________ \n Testing function str_len()\n________________________________ \n");
	char a[5][40] = {"Pavlov Ivan", "Modern Programming", "C++", "Homework", "S_P_"};
	int i = 0;
	while(i < 5)
	{
		char c[40];
		char d[40];
		strcpy(c, a[i]);
		strcpy(d, a[i]);
		size_t o1 = str_len(a[i]);
		size_t o2 = strlen(c);
		if(o1 == o2)
			printf("Test %d : OK \n", i + 1);
		else
			printf("Test %d : WA \n", i + 1);
		printf("str_len(\"%s\") : %d \n", d, (int)o1);
		i++;
	}
}

#include "largeInt.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

char* 	reverse(char* str);
void* 	largeInt_create(const char* str);
int 	largeInt_compare(void* largeInt1, void* largeInt2);
char* 	largeInt2str(void* largeInt);
void* 	largeInt_add(void*	largeInt1, void* largeInt2);
void* 	largeInt_increment(void* largeInt);
char* 	diff(void* largeInt1, void* largeInt2);
void* 	largeInt_diff(void* largeInt1, void* largeInt2);
void* 	largeInt_decrement(void* largeInt);
void* 	largeInt_multiply_function(void* largeInt1, void* largeInt2);
void* 	largeInt_multiply(void* largeInt1, void* largeInt2);
void* 	largeInt_divide(void* largeInt1, void* largeInt2);
void* 	largeInt_pow(void* largeInt1, void* largeInt2);
void 	largeInt_destroy(void* largeInt);

char* reverse(char* str)
{

	int len=strlen(str), index=0, i;
	char* answer=(char*)malloc(sizeof(char)*(len+1));
	for(i=len-1;i>=0;i--)
	{
		answer[index++]=str[i];
	}
	answer[index]=0;
	return answer;
}

void* largeInt_create(const char* str)
{

	int len=strlen(str);	
	if(len==0) 
		return NULL;

	for(int i=0;i<len;i++)
	{  
		char ch=str[i];
		if(ch<'0' || ch>'9')
			return NULL;
	}

	char* number=(char*)malloc(sizeof(char)*(len+1));
	strcpy(number,str);	
	strcpy(number,reverse(number));
	
	while(number[len-1]=='0' && len>1)
		number[--len]=0;
	
	strcpy(number,reverse(number));
	return number;
}

int largeInt_compare(void* largeInt1, void* largeInt2)
{

	if(largeInt1==NULL || largeInt2==NULL) 
		return -2;   

	char* str1=(char*)largeInt1;
	char* str2=(char*)largeInt2;
	int len1=strlen(str1);
	int len2=strlen(str2);

	if(len1>len2) return 1;               
	else if(len2>len1) return -1;
	else 
	{
		int cmp = strcmp(str1,str2);
		if(cmp>0)	
			return 1;
		else if(cmp<0)
			return -1;
		else return 0;
	}
}

char* largeInt2str(void* largeInt)
{
	if(largeInt==NULL) 
	{
		char* str=(char*)malloc(sizeof(char)*4);
		strcpy(str,"NaN");
		return str;
	}
	char* temp=(char*)largeInt;
	char* str=(char*)malloc(sizeof(char)*(strlen(temp)+1)); 
	strcpy(str,temp);
	return str;
}

char* diff(void* largeInt1, void* largeInt2)
{

	char* str1=(char*)largeInt1;
	int len1=strlen(str1);
	char* str2=(char*)largeInt2;
	int len2=strlen(str2);

	char* answer=(char*)malloc(sizeof(char)*(len1+1));
	
	char* str1r=(char*)malloc(sizeof(char)*(len1+1));
	char* str2r=(char*)malloc(sizeof(char)*(len2+1));
	strcpy(str1r,reverse(str1));    
	strcpy(str2r,reverse(str2));

	int result=0,borrow=0,i=0;
	
	for(;i<len1 && i<len2;i++)
	{
		result = (str1r[i]-'0')-(str2r[i]-'0')-borrow;
		if(result<0)
		{
			result=result+10;
			borrow=1;
		}
		else borrow=0;
		answer[i]=result+'0';

	}
	for(;i<len1;i++)
	{
		result=(str1r[i]-'0')-borrow;
		if(result<0)
		{
			result=result+10;
			borrow=1;
		}
		else borrow=0;

		answer[i]=result+'0';
	}
	answer[i]=0;
	
	while(answer[i-1]=='0')
		answer[--i]=0;
	
	strcpy(answer,reverse(answer));
	free(str1r);
	free(str2r);
	return answer;	
}

void* largeInt_diff(void* largeInt1, void* largeInt2)
{
	
	if(largeInt2==NULL || largeInt1==NULL) return NULL;

	int n=largeInt_compare(largeInt1,largeInt2);  
	if(n==0)
		return largeInt_create("0");
	if(n>0)
		return diff(largeInt1,largeInt2);
	else
		return diff(largeInt2,largeInt1);
}

void* largeInt_decrement(void* largeInt)
{

	if(largeInt==NULL) 
		return NULL;
	void *zero=largeInt_create("0");
	if(largeInt_compare(largeInt,zero)==0) 
		return zero;
	free(zero);
	return largeInt_diff(largeInt, largeInt_create("1"));
}

void* largeInt_add(void* largeInt1, void* largeInt2)
{

	if(largeInt1==NULL || largeInt2==NULL) 
		return NULL;
	
	char* str1=(char*)largeInt1;
	int len1=strlen(str1);
	char* str2=(char*)largeInt2;
	int len2=strlen(str2);

	char* str1r=(char*)malloc(sizeof(char)*(len1+1));
	char* str2r=(char*)malloc(sizeof(char)*(len2+1));
	char* answer=(char*)malloc(sizeof(char)*(len1+len2+2));

	strcpy(str1r,reverse(str1));
	strcpy(str2r,reverse(str2)); 

	int max = (len1>len2)?len1:len2;

	int result=0,carry=0,i=0;
	for(;i<len1 && i<len2;i++)
	{							
		result=(str1r[i]-'0')+(str2r[i]-'0')+carry;
		if(result>=10)
		{
			result=result%10;
			carry=1;
		}
		else 
			carry=0;
		answer[i]=result +'0';
	}

	for(;i<max;i++)
	{
		if(max==len2)			
			result=(str2r[i]-'0')+carry;
		else
			result=(str1r[i]-'0')+carry;

		if(result>=10)
		{
			result=result%10;
			carry=1;
		}
		else 
			carry=0;
		answer[i]=result +'0';
	}

	if(carry==1)					
		answer[i++]='1';
	answer[i]=0;

	strcpy(answer,reverse(answer));

	free(str2r);
	free(str1r);

	return answer;
}

void* largeInt_increment(void* largeInt)
{
	if(largeInt==NULL) 
		return NULL;    
	return largeInt_add(largeInt, largeInt_create("1")); 
}

void* largeInt_multiply_function(void* largeInt1, void* largeInt2)
{
	char* str1=(char*)largeInt1;
	int len1=strlen(str1),i;
	char* str2=(char*)largeInt2;
	int len2=strlen(str2);

	char* str1r=(char*)malloc(sizeof(char)*(len1+1));
	char* str2r=(char*)malloc(sizeof(char)*(len2+1));
	char* answer=(char*)malloc(sizeof(char)*(len1+len2)+1);
	int* digits=(int*)malloc(sizeof(int)*(len1+len2)+1);
	for (i=0; i<(len1+len2); i++)
        digits[i] = 0;   

	strcpy(str1r,reverse(str1));
	strcpy(str2r,reverse(str2));
	
	for(i=0;i<len2; i++)
		for(int j=0;j<len1;j++)
			digits[i+j]+= (str1r[j]-'0')*(str2r[i]-'0');

	int carry=0;
	i=0;
	while(i<len1+len2)
	{
		digits[i]+=carry;
		answer[i]=(digits[i]%10) + '0';
		carry=digits[i]/10;
		i++;
	}
	free(str1r);
	free(str2r);
	free(digits);
	answer[i]=0;

	while(answer[i-1]=='0')
		answer[--i]=0;
	
	strcpy(answer,reverse(answer));
	
	return answer;
}

void* largeInt_multiply(void* largeInt1, void* largeInt2)
{
	if(largeInt1==NULL || largeInt2==NULL) 
		return NULL;
	void *zero=largeInt_create("0");
	if(largeInt_compare(largeInt2,zero)==0 || largeInt_compare(largeInt1,zero)==0) return zero;
	free(zero);
	if(largeInt_compare(largeInt1,largeInt2)<0) 
		return largeInt_multiply_function(largeInt2,largeInt1);
	else 
		return largeInt_multiply_function(largeInt1,largeInt2);
}

void* largeInt_divide(void* largeInt1, void* largeInt2)
{

	if(largeInt1==NULL || largeInt2==NULL) return NULL;

	if(largeInt_compare(largeInt2,largeInt_create("0"))==0)	return NULL; //Division by zero

	void *zero=largeInt_create("0");

	if(largeInt_compare(largeInt1,zero)==0)	return zero; 
	if(largeInt_compare(largeInt1,largeInt2)<0)	return zero;
	free(zero);

	void *one=largeInt_create("1");

	if(largeInt_compare(largeInt2,one)==0)	
	{
		char* str1=(char*)largeInt1;
		free(one);
		return largeInt_create(str1);
	}
	free(one);
	char digits[2];
	digits[1]=0;
	int i=0,j,k;
	char* str1=(char*)largeInt1;
	int len1=strlen(str1);
	char* str2=(char*)largeInt2;
	int len2=strlen(str2);
	char*temp=(char*)malloc(sizeof(char)*(len2+2));
	char*answer=(char*)malloc(sizeof(char)*(len1-len2+2));

	for(;i<len2;i++)
		temp[i]=str1[i];
	temp[i]=0;
	i=0;

	void* multiplier;
	j=len2;
	while(j<len1+1)
	{
		void* temp2=largeInt_create(temp);
		void* op2=largeInt_create(str2);
		if(largeInt_compare(temp2,op2)<0)
		{	
			free(temp2);
		    temp[strlen(temp)+1]=0;
		    if(j==len1)
		    {
		        answer[i]='0';
		        i++;
		        break;
		    }
		    temp[strlen(temp)]=str1[j];
		    temp2=largeInt_create(temp);
		    j++;
		    answer[i]='0';
		    i++;
		}
		k=0;
		while(largeInt_compare(temp2,op2)>=0)
		{
		    k++;
		    if(k<10)
		    {
		        digits[0]=k+'0';
		        multiplier=largeInt_create(digits);
			}
		    else
		        multiplier=largeInt_create("10");
		    op2=largeInt_multiply(largeInt2,multiplier);
		    free(multiplier);
		}
		if(j==len1)
		{
		    if(k>0)
		        answer[i++]=k+'0'-1;
		    else
		        answer[i++]='0';
		    break;
		}
		if(k!=0)
			answer[i++]=k-1+'0';
		else
		    answer[i++]='0';
		
		
		op2=largeInt_diff(op2,largeInt2);
		void* diff=largeInt_diff(temp2,op2);
		free(temp);
		temp=largeInt2str(diff);
		for(k=0;k<strlen(temp);k++)
		    temp[k]=temp[k];

		temp[k++]=str1[j++];
		temp[k]=0;
		free(temp2);
		free(op2);
	}
	answer[i]=0;
	free(temp);
	strcpy(answer,reverse(answer));
	while(answer[i-1]=='0')
		answer[--i]=0;
	strcpy(answer,reverse(answer));
	return answer;
}

void* largeInt_pow(void* largeInt1, void* largeInt2)
{

	if(largeInt1==NULL ||largeInt2==NULL)	return NULL;

	char *str1=(char*)largeInt1;
	char *str2=(char*)largeInt2;
	
	if(str1[0]=='0')
		return largeInt_create("0");

	if(str2[0]=='0')
		return largeInt_create("1");

	void *two=largeInt_create("2");
	void *largeInt=largeInt_pow(largeInt1,(largeInt_divide(largeInt2,two)));
	int len=strlen(str2);
	free(two);
	if((str2[len-1]-'0')%2!=0)
		return largeInt_multiply(largeInt1,(largeInt_multiply(largeInt,largeInt)));

	return largeInt_multiply(largeInt,largeInt);    
}

void largeInt_destroy(void* largeInt)
{
	if(largeInt==NULL) 
		return;
	free(largeInt);
}

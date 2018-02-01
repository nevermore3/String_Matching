#include "kmp.h"



void Alter_info::KMP::replace(char *text, int tLen, char* str , int sLen)
{
	int pLen = pattern.size();
	if( NULL == text || NULL == str || tLen <= 0 || sLen <= 0 )
	{
		fprintf(stderr, "the input string is NULL!!!\n");
		return;
	}
	if(sLen != pLen)
	{
		fprintf(stderr, "the source's len  %s is not same as destion's len %s\n", str, pattern.c_str() );
		return ;
	}
	std::vector<int> result;
	
	if(ERROR != search(text, tLen, result) )
	{
		if(1== result.size() && -1 == result[0])
		{
			fprintf(stderr, "the  word : %s is not exist in Text\n", pattern.c_str());
			return;
		}
		else
		{
			for(int i = 0; i < result.size(); i++)
			{
				int index = result[i];		
				for(int j = 0; j < pLen; j++)
				{
					text[index++] = str[j];
				}
			}
		}
	}
	else
	{
		fprintf(stderr, " Error in search() !!!\n");
		return;
	}
}

void Alter_info::KMP::replace_default(char *text, int tLen, char c )
{
	int pLen = pattern.size();
	if( NULL == text  || tLen <= 0)
	{
		fprintf(stderr, "the input string is NULL!!!\n");
		return;
	}
	std::vector<int> result;
	
	if(ERROR != search(text, tLen, result) )
	{
		if(1== result.size() && -1 == result[0])
		{
			fprintf(stderr, "the  word : %s is not exist in Text\n", pattern.c_str());
			return;
		}
		else
		{
			for(int i = 0; i < result.size(); i++)
			{
				int index = result[i];		
				for(int j = 0; j < pLen; j++)
				{
					text[index++] = c;
				}
			}
		}
	}
	else
	{
		fprintf(stderr, " Error in search() !!!\n");
		return;
	}
}


int Alter_info::KMP::search(char *text, int tLen, std::vector<int>&result)
{
	if(NULL == text || tLen <= 0 )
	{
		fprintf(stderr, "The text is NULL !!!!!\n");
		return ERROR;
	}
	
	int i = 0;
	int j = 0;
	int pLen = pattern.size();

	while(i < tLen)
	{
		while(i < tLen && j < pLen)
		{
			if( '\0' == text[i])
				i++;
			if( -1 == j  || text[i] == pattern[j])
			{
				i++;
				j++;
			}
			else
			{
				j = next[j];
			}
		}

		if( pLen == j)
		{
			result.push_back(i - j);
			j = 0; 
		}
	}
	// if not matched, 
	if( 0 == result.size())
	{
		result.push_back(-1);
	}
}


Alter_info::KMP::KMP(char* pattern_s)
{
	/*
	char * to string
	the '\0' in char* is not allowed
	*/
	std::stringstream  stream;
	stream<<pattern_s;
	stream>>pattern;
	get_next();
}

void Alter_info::o_print(int i)
{
	fprintf(stdout, "%d\t", i);
}


void Alter_info::KMP::print_next()
{
	for_each(next.begin(), next.end(), o_print);
	std::cout<<std::endl;
}


void Alter_info::KMP::get_next()
{
	int pLen = pattern.size();
	next.resize(pLen, 0);
	next[0] = -1;

	int i = -1;   //prefix index
	int j = 0;    // subfix index

	while( j < pLen - 1 )
	{
		if(-1 == i || pattern[j] == pattern[i])
		{
			i++;
			j++;
			if(pattern[i] != pattern[j])
				next[j] = i;
			else
				next[j] = next[i];
		}
		else
		{
			i = next[i];
		}
	}
}

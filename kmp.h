#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

/*
kernal ：主串位置不做改动， 那如何知道该从模式串的哪个位置开始比较？  充分利用之前已经部分匹配这个有效信息。
 所以需要我们对模式串做一个预处理，
 通过预处理可以得到一个next数组，其保存的就是当我们在模式串某个位置匹配失败后，应该从模式串的哪个位置重新开始比较

 next 数组就是：对于模式串j这个位置之前(1-> j-1)的串中，是否存在
 从模式串第一个位置出发向右移动得到的子串
 和
 从模式串第j-1个字符位置出发向左移动得到的子串匹配
 而且当该串达到最大长度时， next的值就是该串的长度加1
*/


namespace Alter_info{

#define ERROR -1


void o_print(int i);
class KMP
{
	public:
		KMP(char* pattern_s);
		int search(char* text, int len, std::vector<int>&result);
		void replace(char* text, int tLen, char* str, int sLen);
		void replace_default(char* text, int tLen, char c);
		void print_next();
	private:

		void get_next();
		std::vector<int>next;     
		std::string  pattern;
};

}

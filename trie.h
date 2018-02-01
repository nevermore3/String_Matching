#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
using namespace std;


const int size = 26;

typedef struct Node
{
	char val;
	int freq;
	Node *child[size];
	bool is_end;
	vector<string>brother;
	Node(char c)
	{
		val = c;
		freq = 1;
		is_end = false;
		memset(child, 0, sizeof(Node*)*size);
	}
}Node;



class Trie
{
public:
	Trie(char c);
	Node *get_head();
	int insert(string word);
	bool search(string word, vector<string>&result);
	int findsimlarwordnum(string word);
	int findonesimlarword(string word, int i, char *simlar);
	void destory(Node *node);
	void print_tree();
	void print_word();
private:
	Node *Head;
};

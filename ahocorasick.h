#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using  namespace std;

const int ERROR = -1;

const int size = 127;
const char SPECIAL = 0;
typedef struct  Node
{
	char val;
	Node* FailNode;  
	bool is_end;
	vector<string> output;  
	Node *child[size];
	Node(char c)
	{
		val = c;
		FailNode = NULL;
		is_end = false;
		memset(child, NULL , sizeof(Node*)*size);
	}
}Node;

class  AC_Trie
{
public:
	AC_Trie(vector<string>patterns_);
	bool create_trie();
	void set_failstate();
	void search(char* text, int tLen);
	void get_result(map<pair<int, int>, string> &temp);
private:
	void update_output(Node *node , Node* jump_node);
	void insert(string word);
	vector<string>patterns;
	vector< pair<int, int> >postion_;
	map< pair<int, int >, string>postion;
	Node *Root;
};

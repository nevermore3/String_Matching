#include "ahocorasick.h"


AC_Trie::AC_Trie(vector<string> patterns_)
{
	Root = new Node('#');
	patterns.swap(patterns_);
}

bool AC_Trie::create_trie()
{
	if(NULL == Root || patterns.size() == 0)
	{
		fprintf(stderr, "Root is NULL or Pattern's size is 0\n");
		return false;
	}
    for(int i = 0; i < patterns.size(); i++)
	{
		insert(patterns[i]);
	}
	fprintf(stderr, "Create AC_Trie Success!!!\n");
	return true;
}


//goto function
void AC_Trie::insert(std::string word)
{
	Node *curr = Root;
	int wLen = word.size();
	for(int i = 0; i < wLen; i++)
	{
		int index = word[i] - SPECIAL;   
		Node **temp = &curr->child[index];
		if(NULL == *temp)
		{
			fprintf(stderr, "the character %c is not in tree, create it\n", word[i]);
			*temp = new Node(word[i]);
			curr = *temp;
		}
		else
		{
			curr = *temp;
		}
		if( i == wLen - 1)
		{
			(*temp)->is_end  = true;
			vector<string>::iterator iter = find((*temp)->output.begin(), (*temp)->output.end(), word);
			if(iter == (*temp)->output.end())
				(*temp)->output.push_back(word);
		}
	}
}

/*
设这个节点上的字母是c，沿着他父亲的失败指针走，直到走到一个节点，他的儿子中也有字母为c的节点
然后把当前节点的失败节点指向那个字母也为c的儿子，如果一直走到了root都没有找到，则将失败指针指向
root
*/

//fail function
void AC_Trie::set_failstate()    
{
	if(NULL == Root)
	{
		fprintf(stderr, "The Root is NULL in update_failstate\n");
		return;
	}
	queue<Node*> q;
	Node *root = Root;
	q.push(root);
	while(!q.empty())
	{
		Node *parent = q.front();
		q.pop();
		for(int i = 0; i < size; i++)
		{
			Node *curr = parent->child[i];
			//  find FailNode of current node
			if(NULL != curr)
			{
				if(parent == Root)
				{
					curr->FailNode = Root;
				}
				else
				{
					Node *p_fail = parent->FailNode;
					while(p_fail != NULL)
					{
						if(NULL != p_fail->child[i] && p_fail->child[i]->val == curr->val)       //指向curr_value的指针也是第i个 
						{
							curr->FailNode = p_fail->child[i];
							update_output(curr, p_fail->child[i]);     //update output
							//fprintf(stderr,"Update Output   Success!!! the value is %c\n ", curr->val);
							break;
						}
						p_fail = p_fail->FailNode;
					}
					if(NULL == p_fail)
						curr->FailNode = Root;
				}
				q.push(curr);
			}
		}
	}
	fprintf(stderr,"set fail_state Success!!!\n ");
}


void AC_Trie::update_output(Node *node, Node* jump_node)
{
	if(jump_node->is_end)
	{
		for(int i = 0; i < jump_node->output.size(); i++)
		{
			node->output.push_back(jump_node->output[i]);
		}
	}
	return;
}

/*
	当前字符匹配，表示从当前节点沿着树边有一条路径可以达到目标字符，此时只需要沿着路径继续走向下一个节点匹配，目标字符串指针指向下个字符
	当前字符不匹配，去当前节点的失败节点继续匹配，匹配过程随着指针指向root结束。
*/
void AC_Trie::search(char *text, int tLen)
{
	if(NULL == Root)
	{
		fprintf(stderr, "Root is NULL in search function\n");
		return;
	}
	Node *curr = Root;
	for(int i = 0; i < tLen; i++)
	{
		if(curr->is_end )
		{
			int end = i - 1;
			for(int j = 0; j < curr->output.size(); j++)
			{
				string Matched_word = curr->output[j];
				int start = end - Matched_word.size() + 1;
				pair<int , int >pos = make_pair(start, end);
				postion[pos] = Matched_word;
			}
		}

		int index = text[i] - SPECIAL;
		while(curr->child[index] == NULL && curr != Root)
			curr = curr->FailNode;

		//matched  and move on
		curr = curr->child[index];
		curr = (curr == NULL) ? Root : curr;   //

	}
}

void AC_Trie::get_result(map<pair<int, int>, string> &temp)
{
	temp = postion;
}

void function_ac()
{
	vector<string> pattern;
	pattern.push_back("he");
	pattern.push_back("she");
	pattern.push_back("hers");
	pattern.push_back("his");
	//string  text = "kelv ;sdf'sdl;sd;'gjmnsdiksdlihisxfdknlnishiwoxiaoaxiaopingguowoaiskfjknihzidaoklguyashweldphislsherhlikjhisrshelopkmiijimingquan";
	//char buffer[1000] = {0};
	//stringstream sstream;
	//sstream <<text;
	//sstream >>buffer;
	AC_Trie tree(pattern);
	tree.create_trie();
	tree.set_failstate();
	char *buffer =  "kelv ;shedf'sdl;sd;'gjmnsdiksdldfg*(&*&(%%&*(*)&(gquhishesuhserhersan";

	tree.search(buffer, strlen(buffer));
	map< pair<int, int >, string>result;
	tree.get_result(result);
	
	for(map< pair<int, int>, string>::iterator it = result.begin(); it != result.end(); it++)
	{
		string word = it->second;
		pair<int, int>pos = it->first;
		cout<<word<<"\t"<<pos.first<<"\t"<<pos.second<<endl;
	}

}

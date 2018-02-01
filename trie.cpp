string to_string( char*str)
{
	string word;
	stringstream  stream;
	stream << str;
	stream >> word;
	return word;
}
int Trie::insert(string origin)
{
	string word = origin;
	sort(word.begin(), word.end());
	int sLen = word.size();
    Node *curr = Head;
    for(int i = 0; i < sLen; i++)
    {
        int index = word[i] - 'a';
        Node **temp = &curr->child[index];
        if(NULL == *temp)
        {
            Node *node = new Node(word[i]);
            *temp = node;
            curr = *temp;
        }
        else
        {
            (*temp)->freq++;
            curr = *temp;
        }
        if( i == sLen - 1)
        {
			Node *t = *temp;
            t->is_end = true;
            std::vector<string>::iterator iter = find(t->brother.begin(), t->brother.end(), origin);
            if(iter != t->brother.end())
            {
                cout<<"the word :"<<origin<<"is exist"<<endl;
				return -1;
            }
            else
            {
                t->brother.push_back(origin);
                sort(t->brother.begin(), t->brother.end());
				return 0;
            }
        }
    }
}

Trie::Trie(char c)
{
    Head = new Node(c);
    cout<<"Create Head success"<<endl;
}

bool Trie::search(string origin ,vector<string>&result)
{
	string word = origin;
	sort(word.begin(), word.end());
	int sLen = word.size();
    Node *curr = Head;
    for(int i = 0; i < sLen; i++)
    {
		int index = word[i] - 'a';
        Node *next = curr->child[index];
        if(NULL == next)
        {
            cout<<"word "<<word<<"is not exist in dictory"<<endl;
            return false;
        }
        else
        {
            curr = next;
        }
        if( i == sLen - 1)
        {
            if(next->is_end == false)
            {
                cout<<"word "<<word<<"is not exist in dictory"<<endl;
                return false;
            }
            else
            {
                cout<<"word "<<word<<"is in dictory"<<endl;
				result = next->brother;
                return true;
            }
        }
    }

}
int Trie::findsimlarwordnum(string word)
{
		vector<string>result;
		bool flag = search(word, result);
		if(flag)
		{
			return result.size();
		}
		else
		{
			return 0;
		}
	
}
int Trie::findonesimlarword(string origin, int i, char *simlar)
{
		string word = origin;
		sort(word.begin(), word.end());
		vector<string>result;
		bool flag = search(word, result);
		if(!flag || result.size() < i - 1)
		{
			return -1;
		}
		else
		{
			stringstream  stream;
			stream << result[i-1];
			stream >>simlar;
			return 0;
		}

}
void Trie::destory(Node *node)
{
    Node *curr = node;
    if(curr == NULL)
        return;
    for(int i = 0; i < size; i++)
    {
        destory(node->child[i]);
    }
    delete node;
    node = NULL;
}

void Trie::print_tree()
{
	if(Head == NULL)
	{
		cout<<"The tree is not exist"<<endl;
		return;
	}
	Node *node = Head;
	queue<Node *>q;
	q.push(node);
	int l_size = 1;
	while( !q.empty())
	{
		Node *temp = q.front();
		q.pop();
		l_size-- ;
		cout << temp->val<<"\t";
		for(int i = 0; i < size; i++)
		{
			if(NULL != temp->child[i])
				q.push(temp->child[i]);
		}
		if(l_size == 0)
		{
			l_size = q.size();
		}

	}
}

void Trie::print_word()
{
	Node *node = Head;
	queue<Node *>q;
	q.push(node);
	while(!q.empty())
	{
		Node *temp = q.front();
		if(temp->is_end)
		{
			vector<string>b = temp->brother;
			for(int i = 0; i < b.size(); i++)
			{
				cout<<b[i]<<"\t";
			}
		}
		q.pop();
		for(int i = 0; i < size; i++)
		{
			if(NULL != temp->child[i])
				q.push(temp->child[i]);
		}
	}
}

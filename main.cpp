
#include "pch.h"
#include <queue>
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>
#include <fstream>

using namespace std;
std::ifstream::pos_type filesize(string filename)
{
	ifstream file(filename.c_str(), ios::binary | ios::ate);
	return file.tellg();
}

struct node
{
	char ch;
	int count;
	node*left, *right;
public:
	node(char chi ,int ci ) {
		ch = chi;
		count = ci;
		left = right = nullptr;

	}
};
struct compare {

	bool operator()(node* l, node* r)

	{
		return (l->count > r->count);

	}
};

void PrintTree(struct node* root, string str,std::map<char, string> &convertion)
{

	if (!root)
		return;

	if (root->ch != '$') {
		cout << root->ch << ": " << str << "\n";
		convertion[root->ch] = str;
	}

	PrintTree(root->left, str + "0",convertion);
	PrintTree(root->right, str + "1",convertion);
}


void huffman(string text,string output) {
	ifstream read;
	ofstream write;
	read.open(text.c_str());
	map<char, int> counts;
	priority_queue<node*, vector<node*>, compare> MinHeap;
	//counting
	char ch;
	while(read.good()) {
		ch = read.get();
		auto it = counts.find(ch);
		if (it == counts.end())
			counts[ch] = 1;
		else
			it->second = it->second + 1;
	}//eoc


	//feeding to pq
	
	for (map<char, int>::const_iterator it = counts.begin(); it != counts.end(); ++it)
	{
		MinHeap.push(new node(it->first,it->second));
	}
	//creating tree
	while (MinHeap.size() != 1)
	{
		
		node*temp, *tempright, *templeft;
		temp = new node('$',0);
		templeft = MinHeap.top();
		MinHeap.pop();
		tempright = MinHeap.top();
		MinHeap.pop();
		temp->left = templeft;
		temp->right = tempright;
		temp->ch = '$';
		temp->count = templeft->count + tempright->count;
		MinHeap.push(temp);

	}//eo
	node* newtree = MinHeap.top();
	map<char, string> convertion;
	PrintTree(newtree, "",convertion);
	read.clear();
	read.seekg(0, ios::beg);
	write.open(output.c_str());
	while (read.good())
	{
		char temp = read.get();
		write << convertion.find(temp)->second;
	}
	
}

int main()
{
	string text, output;
cout << "enter input location    ";
	cin >> text;
	cout << "enter output location    ";
	cin >> output;
	
	huffman(text,output);
	cout << endl << "input size is:   " << filesize(text) * 8 << "     bits";
	cout << "    output size is:  " << filesize(output) << "     bits" << endl;
	cout << " you just saved      "<< filesize(text) * 8 - filesize(output) << " bits " << endl;
	system("PAUSE");
	return 0;
}


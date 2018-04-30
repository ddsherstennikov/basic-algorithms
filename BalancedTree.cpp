// Answer if the tree is balanced
// input: 20 21 10 5 2 8 1 15 18 0
// output: NO

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::set;
using std::vector;

typedef int      key_t;   // data type of the keys
typedef int      value_t; // data type of the value associated with the key

int max(int a, int b) { return a > b ? a : b; }
int abs(int a) {return a >= 0 ? a : -a; }

//data type of tree nodes
class node_t
{
public:
  key_t key;
	node_t *left, *right, *prev;

	node_t(key_t k) : key(k), left(NULL), right(NULL), prev(NULL) {}
	node_t() : key(0), left(NULL), right(NULL), prev(NULL) {}

};

class tree
{
private:
	void removeChildrenAndRoot(node_t* root);

public:
	node_t* root;

	tree(node_t* n) : root(n) {}
	~tree();

	void insert(node_t *newNode, node_t* currentRoot);
	int is_balanced(node_t* currentNode);

};

void tree::removeChildrenAndRoot(node_t* root)
{
	//delete all on the left and right of root
	if((!root->left)&&(!root->right))
		delete root;
	if((root->left)&&(!root->right))
		removeChildrenAndRoot(root->left);
	if((!root->left)&&(root->right))
		removeChildrenAndRoot(root->right);
	if((root->left)&&(root->right))
	{
		removeChildrenAndRoot(root->left);
		removeChildrenAndRoot(root->right);
	}
	
	return;
}

tree::~tree()
{
	removeChildrenAndRoot(root);
}

void tree::insert(node_t* newNode, node_t* currentRoot)
{
	if((currentRoot->left) &&  (newNode->key < currentRoot->key))
	{ insert(newNode, currentRoot->left); return; }
	if((currentRoot->right) && (currentRoot->key < newNode->key))
	{ insert(newNode, currentRoot->right); return; }
	if(newNode->key < currentRoot->key)
	{ currentRoot->left = newNode; newNode->prev = currentRoot; return; }
	if(currentRoot->key < newNode->key)
	{ currentRoot->right = newNode; newNode->prev = currentRoot; return; }

	//if root->key == newNode->key, do nothing: decline repetitions
}

//each node`s left branch height is +/-1 of it`s right branch height
int tree::is_balanced(node_t* currentNode)
{
	if(!(currentNode->left) && !(currentNode->right))
		return 1;
	else if(!(currentNode->left) && (currentNode->right))
	{
		int rightResult = is_balanced(currentNode->right);
		if ( rightResult == 1 ) return (rightResult + 1);
		else return 0;
	}
	else if((currentNode->left) && !(currentNode->right))
	{
		int leftResult = is_balanced(currentNode->left);
		if ( leftResult == 1 ) return (leftResult + 1);
		else return 0;
	}
	else
	{
		int leftResult = is_balanced(currentNode->left);
		int rightResult = is_balanced(currentNode->right);
		
		if ( ( abs(rightResult - leftResult) <= 1 ) && ( rightResult ) && ( leftResult ) ) return(1 + max(leftResult, rightResult));
		else return 0;
	}
}


int main(int argc, char* argv[])
{
	//create tree
	int currentNodeValue;
	cin >> currentNodeValue;
	if(currentNodeValue == 0) {	cout << "NO";	return -1; }
	node_t *newNode = new node_t(currentNodeValue);
	tree T(newNode);

	//fill tree
	cin >> currentNodeValue;
	while(currentNodeValue != 0)
	{
		node_t* newNode = new node_t(currentNodeValue);
		T.insert(newNode, T.root);
		cin >> currentNodeValue;
	}

	//check tree
	if( T.is_balanced(T.root) )
		cout << "YES";
	else
		cout << "NO";

	return 0;	
}

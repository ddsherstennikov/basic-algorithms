// input: 
/*
102 101
3
1 0 3
*/
// output:
// 10201

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <queue>

using std::iostream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::queue;
using std::set;
using std::sort;
using std::reverse;

const int defined_depth = 100;
const int base = 1000*1000*1000;
enum reason {none, all_branches_cut, answer_node_found};

void reverseString(string* s);

//long arythmetics implementation class
class longArithmeticUInt
{
  //storing BIG number
	vector<int> longNumber;
	int longNumberRest;

public:

	//constructing BIG number from string
	longArithmeticUInt(string inputString, int divisorK)
	{
		int rest = 0;
		int digit = 0;
		for (int i=0; i<(int)inputString.length(); ++i)
		{
			digit = atoi(inputString.substr(i, 1).c_str());
			rest = (rest*10 + digit) % divisorK;
		}
		longNumberRest = rest;

		for (int i=(int)inputString.length(); i>0; i-=9)
		{
			if (i < 9)
				longNumber.push_back (atoi (inputString.substr(0, i).c_str()));
			else
				longNumber.push_back (atoi (inputString.substr(i-9, 9).c_str()));
		}
	}

	//getting BIG number % k
	int getRest()
	{
		return longNumberRest;
	}
	
	//for output
	friend ostream& operator<<(ostream& os, const longArithmeticUInt& LA_a);

};

ostream& operator<<(ostream& os, const longArithmeticUInt& LA_a)
{
	printf ("%d", LA_a.longNumber.empty() ? 0 : LA_a.longNumber.back());
	for (int i = (int) LA_a.longNumber.size() - 2; i >= 0; --i)
		printf ("%09d", LA_a.longNumber[i]);

	return cout; 
}

//node of a tree of added digits
struct node
{
	int digit;
	int rest;
	struct node* prev;

	node() : digit(-1), rest(-1), prev(0) {}
	node(int inputDigit, int inputRest, node* inputPrev) : digit(inputDigit), rest(inputRest), prev(inputPrev) {}
};

#define struct node node

//getting user input
void input(string* stringLongNumber, int* divisorK, vector<int>* digits)
{
	int n = 0;
	char longUIntCharStringView[1001];

	scanf("%s %d/n", &longUIntCharStringView, divisorK);
	string sGetStringFromCharArray(longUIntCharStringView);
	*stringLongNumber = sGetStringFromCharArray;

	int numberOfDigits;
	scanf("%d/n", &numberOfDigits);
	for (int i = 0; i < numberOfDigits; ++i)
	{
		int singleDigit;
		scanf("%d", &singleDigit);
		digits->push_back(singleDigit);
	}

	sort(digits->begin(), digits->end());

	return;
}

//main function, which is to find LCM
reason LCM(longArithmeticUInt* bigNumberX, int rest, int divisorK, vector<int>* digits, node* answerNode)
{
	set<int> Rests;
	queue<node*> NodeQueue;
	node* currentNode = new node(-1, rest, 0);
	NodeQueue.push(currentNode);
	Rests.insert(currentNode->rest);
	reason stopCode = none;
	node* newNode = new node();

	while (stopCode == none)
	{
		if(NodeQueue.empty())
		{
			stopCode = all_branches_cut;
			continue;
		}

		currentNode = NodeQueue.front();
		for(vector<int>::iterator it = digits->begin(); it != digits->end(); ++it)
		{
			int rest = (10 * currentNode->rest + *it) % divisorK;

			//add new node to Q
			newNode = new node();
			newNode->digit = *it; newNode->prev = currentNode; newNode->rest = rest;

			//if r==0 then qq is the answer node, mission accomplished
			if (rest == 0)
			{
				stopCode = answer_node_found;
				break;
			}

			//if the r (rest) is new, create new branch (new node)
			if (Rests.find(rest) == Rests.end())
			{
				Rests.insert(rest);
				NodeQueue.push(newNode);
			}
		}

		NodeQueue.pop();
	}

	*answerNode = *newNode;
	return stopCode;
}

void restoreSolution(node* answerNode, reason stopCode, string* addedDigits)
{
	char strDigit[2];
	strDigit[1] = '\0';
	if(stopCode == answer_node_found)
	{
		while (answerNode->prev != 0 )
		{
			char charDigit = '0' + answerNode->digit;
			strDigit[0] = charDigit;
			string sWrapCStyleString(strDigit);

			*addedDigits += sWrapCStyleString;
			answerNode = answerNode->prev;
		}		
	}

	reverseString(addedDigits);

}

//utility function to reverse a string
void reverseString(string* s)
{
	string reverse;

	for(int i=s->size(); i>=0; --i)
	{
		string digit(s->c_str());
		reverse += digit.substr(i, 1);
	}

	*s = reverse;

	return;
}


int main(int argc, char* argv[])
{
	int divisorK;
	string stringLongNumber;
	vector<int> digits;

	//get input and construct data structures
	input(&stringLongNumber, &divisorK, &digits);
	longArithmeticUInt bigNumberX(stringLongNumber, divisorK);
	int rest = bigNumberX.getRest();

	//if we have to add digits
	if(rest != 0)
	{
		//get LCM
		node* answerNode = new node();
		reason stopCode = LCM(&bigNumberX, rest, divisorK, &digits, answerNode);

		//if we have managed to find LCM
		if(stopCode == answer_node_found)
		{
			//unwinding added digits sequence
			string addedDigits = "";			
			restoreSolution(answerNode, stopCode, &addedDigits);
			cout << bigNumberX << addedDigits;
		}

		//if LCM could not be found
		else 	
			cout << -1;
	}

	//if numberX is a multiple of divisorKK already
	else
		cout << bigNumberX;

	return 0;	
}

// Calc number of all palindromes of the string
// input: abACAbab
// output: 1 1 1 7 1 1 3 1

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::min;

//for odd-length palindromes only
vector<int>* calcPalindromeRadii(string* text)
{
  int textLength = (int)text->length();
	vector<int>* palindromeRadius = new vector<int>(textLength);

	int left = 0, right = -1;
	for(int i=0; i<textLength; ++i) 
	{
		int radius = (i > right ? 1 : min(palindromeRadius->at(left+right-i), right-i));

		while(i + radius < textLength && i - radius >= 0 && text->at(i+radius) == text->at(i-radius))  
			++radius;

		palindromeRadius->at(i) = radius--;

		if(i + radius > right)
			left = i-radius, right = i+radius;
	}

	return palindromeRadius;
}

int main(int argc, char* argv[])
{	
	string text;
	cin >> text;
	vector<int>* answer;

	answer = calcPalindromeRadii(&text);

	for(int i=0; i<answer->size(); ++i)
		cout << 2*answer->at(i)-1 << (i == answer->size()-1 ? "" : " ");

	return 0;
}

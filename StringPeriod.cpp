// Find number of periods in string
// using z-function
// input: abcda
// output: 1

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

int findNOfPeriods() 
{
  string text;
	cin >> text;

	int textLength = (int)text.length();
	vector<int> zFunction(textLength);

	for(int i=1, left=0, right=0; i<textLength/2+1; ++i) 
	{
		if (i <= right)
			zFunction[i] = min(right-i+1, zFunction[i-left]);

		while((i + zFunction[i] < textLength) && (text[zFunction[i]] == text[i+zFunction[i]]))
			++zFunction[i];

		if(i + zFunction[i] - 1 > right)
			left = i,  right = i + zFunction[i] - 1;

		if((i + zFunction[i] == textLength) && (textLength % i == 0))
			return textLength/i;
	}

	return 1;
}

int main(int argc, char* argv[])
{	
	cout << findNOfPeriods();

	return 0;
}

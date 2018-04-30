// Being given numbers N and K, output all ASC sequences of length K from numbers 1..N lexigraphically ordered.
// input: 3 -2
// output: 0

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
using std::set;

int main(int argc, char* argv[])
{
  int number, sum;
	cin >> number >> sum;
		
	int result = 0;

	for(int l=0; l<=number; ++l)
	{
		int k = number - l;

		for(int n=0; n<k/2+1; ++n)
		{
			int s = (2*n-k)*(2*n-k)/2 - k/2;

			if(s == sum)
			{
				++result;
				break;
			}

		}		

	}

	cout << result;

	return 0;	
}

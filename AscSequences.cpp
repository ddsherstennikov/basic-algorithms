// Being given numbers N and K, output all ASC sequences of length K from numbers 1..N lexigraphically ordered.
// input: 5 3
// output: 
/*
1 2 3
1 2 4
1 2 5
1 3 4
1 3 5
1 4 5
2 3 4
2 3 5
2 4 5
3 4 5
*/

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

bool next_combination (vector<int>& combination, int limit) 
{
  int power = (int)combination.size();

	for (int i=power-1; i>=0; --i)
		if (combination[i] < limit - power + i + 1) 
		{
			++combination[i];

			for (int j=i+1; j<power; ++j)
				combination[j] = combination[j-1] + 1;

			return true;
		}

		return false;
}


int main(int argc, char* argv[])
{
	int limit, power;
	cin >> limit >> power;

	vector<int> combination;
	for(int i=0; i<power;++i)
	{
		combination.push_back(i+1);
		cout << combination[i] << (i==power-1 ? "" : " ");	
	}

	while(next_combination(combination, limit))
	{
		cout << endl;

		for(int i=0; i<power;++i)
			cout << combination[i] << (i==power-1 ? "" : " ");
	}
	
	return 0;	
}

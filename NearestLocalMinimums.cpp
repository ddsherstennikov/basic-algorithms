// Calc least distance between local minimums
// input: 
/*
1
2
1
2
1
0
*/
// output: 2


#include <cstdlib>
#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::min;

const int MAX_INT = 2147483647;

int localMinLeastDistance()
{
  int min1 = 0, min2 = 0; 
	int prev = -1, curr = -1, next = -1;
	int idx = 1, distance = MAX_INT;

	cin >> prev; if(prev == 0) return 0;
	cin >> curr; if(curr == 0) return 0;
	cin >> next; if(next == 0) return 0;
	
	while(next)
	{
		if(prev < curr && curr > next)
		{
			//try to fill both min-s
			if(!min1 || !min2)
			{
				if(!min1)
					min1 = idx;
				else
					min2 = idx;
			}
			
			//if both min-s filled
			if(min1 && min2)
			{
				//if we have 3rd min, switch
				if(min2 != idx)
				{
					min1 = min2;
					min2 = idx;
				}

				//if the current distance is less, rewrite
				if(min2 - min1 < distance)
					distance = min2 - min1;
			}	
		}

		prev = curr;
		curr = next;
		cin >> next;
		++idx; 
	}

	return (distance == MAX_INT ? 0 : distance);
}

int main(int argc, char* argv[])
{	
	cout << localMinLeastDistance();

	return 0;
}

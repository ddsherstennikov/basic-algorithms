// find elem-s of one array in another approximately
// input: 4 16
//        8 12 17 25
//        11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
// output:
/*
12
12
12
12
17
17
17
17
17
17
17
25
25
25
25
25
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
using std::swap;
using std::min;

int abs(int a) {return a >= 0 ? a : -a; }

int mindiff(int x, int a, int b) 
{
  if (abs(x-a) < abs(x-b))
		return a;
	else if (abs(x-a) > abs(x-b))
		return b;
	else return min(a, b);
}

int ApproximateBinarySearch(vector<int>& a, int x)
{
	int n = a.size();
	int first = 0;
  int last = n-1;
  int mid = first + (last - first) / 2; 
 
	//check for border cases
  if (n == 0)
		return 0;
  else if (a[0] >= x)
    return a[0];
  else if (a[n - 1] <= x)
    return a[n-1];
 
	//do work (overflow-stable code)
  while (first < last)
  {
		if (x <= a[mid])
		{
			if (mid > 0 && x >= a[mid-1])
				return mindiff(x, a[mid], a[mid-1]);
			else if (x < a[mid-1])
				last = mid - 1;
		}
		else
		{
			if (mid < n-1 && x <= a[mid+1])
				return mindiff(x, a[mid], a[mid+1]);
			else if (x > a[mid+1])
				first = mid + 1;
		}

		mid = first + (last - first) / 2;
  }
 
  return 0;
}


int main(int argc, char* argv[])
{
	int N, K;  /* N - main array (sorted ASC) length, K - elements 2b-searched-for array length */
	cin >> N >> K;

	vector<int> array(N);
	for(int i=0; i<N; ++i)
	{
		cin >> array[i];
	}
	for(int j=0; j<K; ++j)
	{
		int element;
		cin >> element;
		cout << ApproximateBinarySearch(array, element) << endl;
	}

	return 0;	
}

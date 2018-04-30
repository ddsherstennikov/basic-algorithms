// Fill matrix ASC with natural numbers one diagonal by another
// input: 3 1
// output: 
//   0
//   1
//   2

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

int main(int argc, char* argv[])
{  
	int n, m;

	cin >> n >> m;
	vector< vector<int> > A(n);
	
	if(!n || !m)
		return 0;

	//fill 1st row
	A[0].push_back(0);
	cout.width(3);
	cout << A[0][0];
	for(int j=1;j<m;++j)
	{
		A[0].push_back(A[0][j-1] + min(j, n));
		cout.width(3);
		cout << A[0][j];
	}
	
	//fill rows 2 to n
	for(int i=1;i<n;++i)
	{
		cout << endl;

		//fill columns 1 to m
		for(int j=0;j<m;++j)
		{
			//if call has upper right neigbour just ++it
			if(j < m-1 && m > 1)
			{
				A[i].push_back(A[i-1][j+1] + 1);
				cout.width(3);
				cout << A[i][j];
			}
			//else add <rest of it`s diag length> to left neighbour 
			else if (m > 1)
			{
				A[i].push_back(A[i][j-1] + min(n-i, m-1));
				cout.width(3);
				cout << A[i][j];
			}
			//else we have just 1 column
			else
			{
				A[i].push_back(A[i-1][j] + 1);
				cout.width(3);
				cout << A[i][j];
			}
		}
	}

	return 0;
}

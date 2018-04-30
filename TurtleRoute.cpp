// TrtleRoute.cpp:
// find the route and it`s weight for 2D table
// input: 
/*
5 1
0
0
0
0
1
*/
// output:
// 1
// D D D D

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
using std::vector;
using std::set;

vector<int> OldRow;
vector<int> NewRow;
vector<string> OldMoves;
vector<string> NewMoves;

//refresh iteration
void RefreshAt(int k)
{
  //we shouldn`t write for (1,1) start cell
	if((OldRow[k] == -1) && (k == 1))
		return;

	if(NewRow[k-1] >= OldRow[k])
	{
		NewRow[k] = NewRow[k-1] + NewRow[k];
		NewMoves[k] = NewMoves[k-1] + "R ";
	}

	else
	{
		NewRow[k] = OldRow[k] + NewRow[k];
		NewMoves[k] = OldMoves[k] + "D ";
	}

	return;
}

int main(int argc, char* argv[])
{
	//N - rows number, M - row length
	int N, M;
	cin >> N >> M;

	//fill initial placeholder values
	OldRow.assign(M+1, -1); OldRow[0] = 0;
	OldMoves.assign(M+1, "");
	NewRow.assign(M+1, 0);
	NewMoves.assign(M+1, "");

	//read table & build answer simultaneously
	for(int i=1; i<=N; ++i)
	{
		NewRow[0] = -1;
		for(int j=1; j<= M; ++j) 
			cin >> NewRow[j];
		NewMoves[0] = "";

		for(int k=1; k<= M; ++k)
			RefreshAt(k);

		OldRow.swap(NewRow);
		OldMoves.swap(NewMoves);
	}

	printf("%d", OldRow[M]);
	cout << endl;
	if(!OldMoves[M].empty())
		cout << OldMoves[M].substr(0, OldMoves[M].size()-1);

	return 0;	
}

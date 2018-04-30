// Answer if in the given combination on chess board
// there exists at least one pair of queens beating one another
// input:
/*
1 7
2 4
3 2
4 8
5 6
6 1
7 3
8 5
*/
// output: NO

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::set;
using std::cout;
using std::cin;

const int QUEENS_COUNT = 8;

struct Position 
{
  int row;
	int column;
};

void Input(vector<Position> *queens) 
{
	queens->resize(QUEENS_COUNT);

	for (int i = 0; i < QUEENS_COUNT; ++i) 
		cin >> (*queens)[i].row 
				>> (*queens)[i].column;

	return;
}

bool Contains(const set<int> &input_set, int element) 
{
	return (input_set.find(element) != input_set.end()); 
}

bool ExistsQueenUnderAttack(const vector<Position>& queens) 
{
	set<int> occupied_rows;
	set<int> occupied_columns;
	set<int> occupied_major_diagonals;
	set<int> occupied_minor_diagonals;

	for(vector<Position>::const_iterator queen = queens.begin();
		queen != queens.end(); ++queen) 
	{
			int minor_diagonal = queen->row + queen->column;
			int major_diagonal = queen->row - queen->column;

			if(Contains(occupied_rows, queen->row) ||
				 Contains(occupied_columns, queen->column) ||
				 Contains(occupied_major_diagonals, major_diagonal) ||
				 Contains(occupied_minor_diagonals, minor_diagonal))
				 return true;

			occupied_rows.insert(queen->row);
			occupied_columns.insert(queen->column);
			occupied_minor_diagonals.insert(minor_diagonal);
			occupied_major_diagonals.insert(major_diagonal);
	}

	return false;
}

int main() 
{
	vector<Position> queens;

	Input(&queens);

	if (ExistsQueenUnderAttack(queens))
		cout << "YES";  
	else 
		cout << "NO";

	return 0;
}

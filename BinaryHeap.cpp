// Build binary heap
// input: 6
//        1 2 3 4 5 6
// output:
/*
    6 5 3 4 2 1
    5 4 3 1 2
    4 2 3 1
    3 2 1
    2 1
    1
    1 2 3 4 5 6
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

void SiftDown(vector<int>& array, int parent)
{
  int left = 2*parent + 1, right = 2*parent + 2;
	int heap_size = array.size();
	int largest;

	if(left < heap_size && array[left] > array[parent])
		largest = left;
	else 
		largest = parent;

	if(right < heap_size && array[right] > array[largest])
		largest = right;

	if(largest != parent)
	{
		swap(array[parent], array[largest]);
		SiftDown(array, largest);
	}

	return;
}

void BuildHeap(vector<int>& array)
{
	int heap_size = array.size();

	for(int i=heap_size/2; i>=0; --i)
		SiftDown(array, i);

	return;
}

int ExtractMax(vector<int>& heap)
{
	int s = heap.size()-1;
	int answer = heap[0];

	heap[0] = heap[s];
	heap.pop_back();
	SiftDown(heap, 0);

	return answer;
}

void PrintArray(vector<int>& heap)
{
	int heap_size = heap.size();

	for(int i=0; i<heap_size; ++i)
		cout << heap[i] << ((i==heap_size-1) ? "" : " ");
}

int main(int argc, char* argv[])
{
	int heap_size = 0;
	cin >> heap_size;

	vector<int> heap(heap_size);
	vector<int> sortedArray(heap_size);
	for(int i=0; i<heap_size; ++i)
	{
		int a;
		cin >> a;
		heap[i] = a;
	}

	BuildHeap(heap);

	PrintArray(heap);
	cout << endl;

	for(int i=0; i<heap_size; ++i)
	{
		int a = ExtractMax(heap);
		sortedArray[heap_size-1-i] = a;

		if(!heap.empty())
		{
			PrintArray(heap);
			cout << endl;
		}
	}
	
	PrintArray(sortedArray);

	return 0;	
}

// input:
/*
4
1 10 2 15
4
1 2
1 3
4 2
4 3
*/
// output:
// 3

#include <iostream>
#include <set>
#include <vector>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::pair;

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;

const int MAX = 100;
const int MAXINT = 1000000000;

int citiesNumber;
vvii Roads(MAX);
vi Distances(MAX, MAXINT);

void input(vector<int>* roadPrices, int* roadsNumber, int* startCityNumber, int* terminalCityNumber)
{
  scanf("%d\n", &citiesNumber);
	*startCityNumber = 1;
	*terminalCityNumber = citiesNumber;

	//fill city gas prices array
	for(int i = 0; i < citiesNumber; ++i)
	{
		int price;
		cin >> price;
		roadPrices->push_back(price);
	}
	
	//get edges number 
	scanf("\n%d\n", roadsNumber);
	
	//fill edges info 
	//w is weight of an edge. it`s price of gas in next city:
	//so that for a weight is roadPrices[a] (-1 comes from numeration start at 0) 
	for (int i = 0; i < *roadsNumber; i++)
	{
		int cityANumber, cityBNumber;
		scanf("%d %d\n", &cityANumber, &cityBNumber);
		Roads[cityANumber - 1].push_back( ii(cityBNumber - 1, roadPrices->at(cityANumber-1)) );
		Roads[cityBNumber - 1].push_back( ii(cityANumber - 1, roadPrices->at(cityBNumber-1)) );
	}
}


void Dijkstra(int startCityNumber)
{
	set<ii> citiesToVisit;
	Distances[startCityNumber] = 0;
	citiesToVisit.insert(ii(0, startCityNumber));

	while(!citiesToVisit.empty())
	{
		ii top = *citiesToVisit.begin();
		citiesToVisit.erase(citiesToVisit.begin());
		int currentCityNumber = top.second;

		//loop through city`s neighbours
		for (vii::const_iterator it = Roads[currentCityNumber].begin(); it != Roads[currentCityNumber].end(); it++)
		{
			int currentNeighbourNumber = it->first;
			int currentNeighbourCost = it->second;
			if (Distances[currentNeighbourNumber] > Distances[currentCityNumber] + currentNeighbourCost)
			{
				if (Distances[currentNeighbourNumber] != 1000000000)
				{
					citiesToVisit.erase(citiesToVisit.find(ii(Distances[currentNeighbourNumber], currentNeighbourNumber)));
				}
				Distances[currentNeighbourNumber] = Distances[currentCityNumber] + currentNeighbourCost;
				citiesToVisit.insert(ii(Distances[currentNeighbourNumber], currentNeighbourNumber));
			}
		}
	}
}

int main()
{
	//get input
	int roadsNumber, startCityNumber, terminalCityNumber = 0;
	vector<int> roadPrices;
	input(&roadPrices, &roadsNumber, &startCityNumber, &terminalCityNumber);

	Dijkstra(startCityNumber - 1);

	//in case we didn`t get to terminal vertex
	if(Distances[terminalCityNumber-1] == 1000000000)
		Distances[terminalCityNumber-1] = -1;

	printf("%d\n", Distances[terminalCityNumber - 1]);

	return 0;
}

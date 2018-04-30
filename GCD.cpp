// input: 10 6 8
// output: 2 -4 8

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

int gcd(int a, int b, int& x, int& y) 
{
  if (a == 0) 
	{
		x = 0; y = 1;
		return b;
	}

	int x1, y1;
	int d = gcd (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

int main(int argc, char* argv[])
{
	int a, b, c;
	cin >> a >> b >> c;

	int xForGCD, yForGCD;
	int gcdResult = gcd(a, b, xForGCD, yForGCD);

	if(c % gcdResult != 0)
		cout << "Impossible";
	else
	{
		int xForC = xForGCD * (c/gcdResult), yForC = yForGCD * (c/gcdResult);
		cout << gcdResult << " " << xForC << " " << yForC;
	}

	return 0;	
}

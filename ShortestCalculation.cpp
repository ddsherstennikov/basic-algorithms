// ShortestCalculation.cpp:
// get the shortest sequence of operations making N from 1
// there are 3 op-s: 1) +1; 2) x2; 3) x3;
// output is sequence of operation codes

// input: 534534
// output: 3331132222222222132

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
using std::pair;

const int maxInt = 1000*1000*1000;
enum operation {none, plus1, mult2, mult3};
typedef pair<int, int> ii;

string AnswerOperationSequence = "";//answer string
vector<int> NumberOfOperationsToReachValue;//our decision function values
vector<int> PreviousNumberForValue;//previous number for each number
vector<operation> OperationCodes;//operation code which derived this number from previous (for each number)

void reverseString(string* inputString);

//returns vector v min value`s index
int min(vector<int>& values) 
{
  int currentMin = 1000000000;
	int index = -1;

	for(unsigned int i =0; i < values.size(); ++i)
	{
		if(values[i] < currentMin) 
		{
			currentMin = values[i];
			index = i;
		}
	}

	return index;
}

//main function, that fillls info on numers from 2 to input-value N
void fillCalculationInfoOnValue(int AimNumber)
{
	vector<int> operationStepsNumber(3, maxInt);

	//fill vector with previous steps` values
	operationStepsNumber[0] = NumberOfOperationsToReachValue[AimNumber-1];
	if(AimNumber%2 == 0) 
		operationStepsNumber[1] = NumberOfOperationsToReachValue[AimNumber/2];
	if(AimNumber%3 == 0) 
		operationStepsNumber[2] = NumberOfOperationsToReachValue[AimNumber/3];

	//find min and determine what index is it in v
	int IndexOfOptimalOperation = min(operationStepsNumber);
	int optimalOperationStepsNumber = operationStepsNumber[IndexOfOptimalOperation];

	//fill arrays depending on min, +1 goes from +1 operation applied to prev number
	NumberOfOperationsToReachValue.push_back(optimalOperationStepsNumber + 1);
	switch(IndexOfOptimalOperation)
	{
	case 0: PreviousNumberForValue.push_back(AimNumber-1); OperationCodes.push_back(plus1); break;
	case 1: PreviousNumberForValue.push_back(AimNumber/2); OperationCodes.push_back(mult2); break;
	case 2: PreviousNumberForValue.push_back(AimNumber/3); OperationCodes.push_back(mult3); break;
	}

	return;
}

//form output, the shortes operation sequence to get input-value N
void formOperationSequence(int AimNumber)
{
	int currentNumber = AimNumber;
	char cStyleString[2];
	cStyleString[1] = '\0';
	while(currentNumber > 1)
	{
		char charOperationCode = '0' + (int)OperationCodes[currentNumber];	
		cStyleString[0] = charOperationCode;
		string stringWrapper(cStyleString);

		AnswerOperationSequence += stringWrapper;
		currentNumber = PreviousNumberForValue[currentNumber];
	}

	reverseString(&AnswerOperationSequence);
}

void reverseString(string* inputString)
{
	string reversedString;

	for(int i=inputString->size(); i>=0; --i)
	{
		string digit(inputString->c_str());
		reversedString += digit.substr(i, 1);
	}

	*inputString = reversedString;

	return;
}

int main(int argc, char* argv[])
{
	int AimNumber;
	cin >> AimNumber;
	
	//it is convenient to start from 1 in this particular problem;
	//fill Info for value "1"
	NumberOfOperationsToReachValue.push_back(-1); NumberOfOperationsToReachValue.push_back(0);
	PreviousNumberForValue.push_back(-1); PreviousNumberForValue.push_back(-1);
	OperationCodes.push_back(none); OperationCodes.push_back(none);

	for(int i=2; i <= AimNumber; ++i)
	{
		fillCalculationInfoOnValue(i);
	}

	formOperationSequence(AimNumber);	
	cout << AnswerOperationSequence;

	return 0;	
}

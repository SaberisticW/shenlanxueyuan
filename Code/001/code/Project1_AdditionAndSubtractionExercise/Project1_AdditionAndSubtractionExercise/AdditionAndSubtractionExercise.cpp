#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;



enum CalculationType { Plus, Subtract, Multiply, Divide };
typedef enum { nonMD,MD} CalculationSupportType;


int ProblemTotalNum = 10u;
int NumericalRangeVal = 100u;
CalculationSupportType OperationSelectTypeVal = nonMD;


static void userInterfaceInteractionFunc(void);
static void calculationFunc(void);


/* feature main function */
void AdditionAndSubtraction_MainFunc(void)
{
	/* If we don't need interaction, block this function */
	userInterfaceInteractionFunc();

	calculationFunc();
}

/* used for Interface Interaction and Parameter selection */
static void userInterfaceInteractionFunc(void)
{
	char operationSelectChar;

	cout << "Please select the number of math problems: " << endl;
	cin >> ProblemTotalNum;

	if (ProblemTotalNum < 1u)
	{
		cout << "input error,the number must be great than 1,it will set to 1 by default!" << endl;
		ProblemTotalNum = 1u;
	}
	else
	{

	}


	cout << "Please select the numerical range: " << endl;
	cin >> NumericalRangeVal;

	if (NumericalRangeVal < 10u)
	{
		cout << "input error,the range value must be great than 10,it will set to 10 by default!" << endl;
		NumericalRangeVal = 10u;
	}
	else
	{

	}

	cout << "Please select whether to support multiplication and division by input y or n " << endl;
	cin >> operationSelectChar;

	if (('n' == operationSelectChar) || ('N' == operationSelectChar))
	{
		OperationSelectTypeVal = nonMD;
		cout << "This test will not include multiplication and division calculations! " << endl;
	}
	else if (('y' == operationSelectChar) || ('Y' == operationSelectChar))
	{
		OperationSelectTypeVal = MD;
		cout << "This test will include multiplication and division calculations! " << endl;
	}
	else
	{
		cout << "input error! This test will include multiplication and division calculations by default! " << endl;
	}
}

/* calculation main function */
static void calculationFunc(void)
{
	
	int randOperation = 0u;
	int randValA = 0;
	int randvalB = 0;
	int calculateVal = 0;
	float calculatefloatVal = 0;
	int answerVal = 0;
	float answerfloatVal = 0;
	int finalMark = 0u;
	int rightTotalVal = 0u;
	int wrongTotalVal = 0u;
	float wrongInfoArray[100][2] = {0,0};
	int totalTime = 0u;
	int minTime = 0xFFFFu;
	time_t start, end;

	srand(time(NULL));

	for (int j = 1; j <= ProblemTotalNum; j++)
	{
		randValA = rand() % NumericalRangeVal;
		randvalB = rand() % NumericalRangeVal;

		if (nonMD == OperationSelectTypeVal)
		{
			randOperation = rand() % 2u;

		}
		else
		{
			randOperation = rand() % 4u;
		}

		
		if (Plus == randOperation)
		{
			calculateVal = randValA + randvalB;
			cout << randValA << '+' << randvalB << '=';
		}
		else if (Subtract == randOperation)
		{
			calculateVal = randValA - randvalB;
			cout << randValA << '-' << randvalB << '=';
		}
		else if (Multiply == randOperation)
		{
			calculateVal = randValA * randvalB;
			cout << randValA << '*' << randvalB << '=';
		}
		else if (Divide == randOperation)
		{
			calculatefloatVal = ((float)randValA) / ((float)randvalB);
			cout << randValA << '/' << randvalB << '=' << "(Retain up to 6 decimal places)";
		}
		else
		{

		}

		/*Start timing for solve math problems */
		start = time(NULL);

		/* Division is a floating-point calculation and needs to be separated separately */
		if (Divide == randOperation)
		{
			cin >> answerfloatVal;
			if (answerfloatVal == calculatefloatVal)
			{
				cout << "Correct!\n" << endl;
				finalMark = finalMark+10;
				rightTotalVal++;
 			}
			else
			{
				cout << "Wrong!\n" << endl;
				wrongTotalVal++;
				wrongInfoArray[wrongTotalVal][0] = (float)j;
				wrongInfoArray[wrongTotalVal][1] = calculatefloatVal;
			}
		
		}
		else
		{
			cin >> answerVal;
			if (answerVal == calculateVal)
			{
				cout << "Correct!\n" << endl;
				finalMark = finalMark + 10;
				rightTotalVal++;
			}
			else
			{
				cout << "Wrong!\n" << endl;
				wrongTotalVal++;
				wrongInfoArray[wrongTotalVal][0] = (float)j;
				wrongInfoArray[wrongTotalVal][1] = (float)calculateVal;
			}
			
		}

		/*end timing */
		end = time(NULL);

		cout << "The time spent on this problem is:" << difftime(end, start) << endl;
		totalTime += difftime(end, start);
		if (minTime > difftime(end, start))
		{
			minTime = difftime(end, start);
		}
		else
		{

		}
	}

	cout << "Final mark is: " << finalMark << endl;
	cout << "The average time is: " << totalTime / ProblemTotalNum << "s" << endl;
	cout << "The Minimum time is: " << minTime << "s" << endl;
	cout << "The number of correct answers is: " << rightTotalVal << endl;
	cout << "The number of wrong answers is: " << wrongTotalVal << endl;
	for (int k = 0; k < wrongTotalVal; k++)
	{
		cout << "The serial number of the wrong math problem is: " << wrongInfoArray[k][0] << 
			" , It's correct answer is: " << wrongInfoArray[k][1] << endl;
	}
	
}
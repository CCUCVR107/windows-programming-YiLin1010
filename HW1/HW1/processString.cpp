#include <iostream>
#include <string>
#include <vector>

#include <gtest\gtest.h>

using namespace std;


// getAscendingStr Function requirement
//
// Take space seperated digit string (ex. "1 2 3 5 4") and 
//   modify input string to ascending order ("1 2 3 4 5").
//
// return 0 if success, (empty string)
//       -1 if exception occur (ex. string containing non-digit character)
int getAscendingStr(string& inputStr)
{
	int i, j = 0, num = 0, sign = 0, temp = 0, next = 0;
	int arr[32];
	int len = inputStr.length();
	stringstream ss;
	string str;

	for (i = 0; i < len; i++) {
		if ((inputStr[i] > '9' || inputStr[i] < '0') && inputStr[i] != ' ' && inputStr[i] != '-')
			return -1;

		//digit of a number
		if (inputStr[i] != ' ') {
			if (inputStr[i] == '-') { sign = 1; continue; }

			if (num == 0)
				num += inputStr[i] - '0';
			else {
				num *= 10;
				num += inputStr[i] - '0';
			}
		}

		//a new number
		if (inputStr[i] == ' ' || i + 1 == inputStr.size()) {
			if (sign == 1)	num *= -1;

			arr[j] = num;
			j++;
			num = 0;	sign = 0;
		}
	}

	//the last one
	for (i = 1; i < j; i++) {
		temp = arr[i];
		next = i;
		while ((arr[next - 1] > temp) && next > 0) {
			arr[next] = arr[next - 1];
			next--;
		}
		arr[next] = temp;
	}

	//int array 2 string
	inputStr.erase();
	for (i = 0; i < j; i++) {
		ss.clear();	ss << arr[i];	ss >> str;
		inputStr += str;
		if (i + 1 != j) inputStr += " ";
	}


	return 0;
}

// solveQ Function requirement
// 
// solve quadratic function ax^2 + bx + c = 0
//
// return 1 if equation has two different real number root 
//          (return vector size should be 2 containing 2 solution.  
//          Greater value should put into smaller vector index)
//        0 there is only one possible solution to the quadratic equation 
//          (return vector size should be 1)
//       -1 complex roots 
//          (return vector size should be 0)
int solveQ(vector<double> &x, double a, double b, double c)
{
	double delta, x1, x2;
	delta = pow(b, 2) - 4 * a * c;

	//two solutions
	if (delta > 0) {
		x1 = ((-1 * b) + sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;
		x2 = ((-1 * b) - sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;

		//cout << "x1 : " << x1 << endl;
		//cout << "x2 : " << x2 << endl;
		x.push_back(x1);
		x.push_back(x2);
		return 1;
	}

	//complex solutions
	else if (delta < 0) {
		return -1;
	}

	//one solution
	else {
		x1 = ((-1 * b) + sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;

		//cout << "x1 : " << x1 << endl;
		x.push_back(x1);
		return 0;
	}

	return 0;
}

int main(int argc, char*argv[]) {
	
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}

TEST(getAscendingStr, SimpleAscending)
{//Simple ascending test case

	string inputStr = "1 -3 2195 4 50";
	string tmpStr = inputStr;
	int err = getAscendingStr(tmpStr);
	EXPECT_EQ(tmpStr, "-3 1 4 50 2195");
	EXPECT_EQ(err, 0);
}

TEST(getAscendingStr, handleNonDigit)
{//getAscendingStr function should handle non digit case
	string tmpStr = "1 3 2 4 a 7f415";
	int err = getAscendingStr(tmpStr);
	EXPECT_EQ(err, -1);
}

TEST(solveQ, twoSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, 2, -3);
	EXPECT_EQ(iSol, 1);
	EXPECT_EQ(sol.size(), 2);
	EXPECT_EQ(sol.at(0), 1);
	EXPECT_EQ(sol.at(1), -3);
}

TEST(solveQ, oneSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, -8, 16);
	EXPECT_EQ(iSol, 0);
	EXPECT_EQ(sol.size(), 1);
	EXPECT_EQ(sol.at(0), 4);
}

TEST(solveQ, noSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, 1, 16);
	EXPECT_EQ(iSol, -1);
	EXPECT_EQ(sol.size(), 0);
}
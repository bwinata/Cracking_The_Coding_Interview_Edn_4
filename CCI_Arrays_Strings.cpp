#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdio>

using namespace std;

/* --------------------------------------------------------------------------
 * Question 1.1
 * --------------------------------------------------------------------------
 * Implement an algorithm to determine if a string has all unique characters. 
 * What if you can not use additional data structures?
 */

/* Solution One - Pre-defined array / vector */
bool solutionOne_1_1 (const char * str, int size) {
	vector<bool> asciiVec (256, false);

	if (str == NULL) return false;
	else {
		for (int i = 0; i < size; i++) {
			if (asciiVec[str[i]] == true) return false;
			asciiVec[str[i]] = true;
		}
		return true;
	}
}


/* --------------------------------------------------------------------------
 * Question 1.2
 * --------------------------------------------------------------------------
 * Write code to reverse a C-Style String. (C-String means that “abcd” is 
 * represented as five characters, including the null character.)
 */

/* Solution One - Iterate to the half-way point of the string (IN PLACE)*/
void solutionOne_1_2 (char * str, int size) {
	char tmp = ' ';
	if (str == NULL) return;
	else {
		// Be aware that the size incorporates the NULL terminator
		// This terminator should remain in its place and should not be reversed
		for (int i = 0; i < (size-1) / 2; i++) {
			tmp = str[i];
			str[i] = str[size-2-i];
			str[size-2-i] = tmp;
		}
	}
}

/* --------------------------------------------------------------------------
 * Question 1.3
 * --------------------------------------------------------------------------
 * Design an algorithm and write code to remove the duplicate characters in a 
 * string without using any additional buffer. NOTE: One or two additional 
 * variables are fine. An extra copy of the array is not.
 *
 * FOLLOW UP
 * Write the test cases for this method.
 */

/* Solution One - Keep track of duplicates in pre-defined array */
 void solutionOne_1_3 (char * str, int size) {
 	vector<bool> asciiVec (256, false);
 	int tracker = 0;

 	if (str == NULL) return;
 	else {
		for (int i = 0; i < size; i++) {
			if (asciiVec[str[i]] == false) {
				str[tracker] = str[i];
				tracker++;
			}

			asciiVec[str[i]] = true;
 		}
 		// Terminate new string with null terminator
 		str[tracker] = '\0';
 	}
 }

/* --------------------------------------------------------------------------
 * Question 1.4
 * --------------------------------------------------------------------------
 * Write a method to decide if two strings are anagrams or not.
 */

/* Solution One - Sort strings. T(n) = O(nlogn) */
bool solutionOne_1_4 (string str1, string str2) {
	sort (str1.begin (), str1.end ());
	sort (str2.begin (), str2.end ());

	return (str1 == str2 ? true : false);
}

/* Solution Two - Pre-defined ASCII array to detemine number of already identified characters
 *                including duplicates. T(n) = O(n)
 */
bool solutionTwo_1_4 (string str1, string str2) {
	vector<int> asciiVec (256, 0); // Set all elements to zero to indicate no identified characters yet.

	if (str1.length () != str1.length ()) return false;
	else {
		for (int i = 0; i < str1.length (); i++) {
			asciiVec[str1[i]]++;
		}

		for (int i = 0; i < str2.length (); i++) {
			asciiVec[str2[i]]--;
			if (asciiVec[str2[i]] < 0) return false;
		}

		for (int i = 0; i < asciiVec.size (); i++) {
			if (asciiVec[i] != 0) return false;
		}
	}	
	return true;
}


/* --------------------------------------------------------------------------
 * Question 1.6
 * --------------------------------------------------------------------------
 * Given an image represented by an NxN matrix, where each pixel in the image 
 * is 4 bytes, write a method to rotate the image by 90 degrees. Can you do 
 * this in place?
 */

/* Solution One - In place algorithm. Iteratively rotate each loop starting
 * 				  from the outside and ending with the innest loop 
 */

void printMatrix (int n, int matrix [][4]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void solutionOne_1_6 (int n, int matrix [][4]) {
	int one = 0, two = 0, three = 0;

	if (n <= 0) return;
	else {
		for (int i = 0; i < n / 2; i++) {
			for (int j = i; j < n - i - 1; j++) {
				
				one = matrix[j][n-1-i];
				matrix[j][n-1-i] = matrix[i][j];

				two = matrix[n-1-i][n-1-j];
				matrix[n-1-i][n-1-j] = one;

				three = matrix[n-1-j][i];
				matrix[n-1-j][i] = two;

				matrix[i][j] = three;
			}
		}
	}
}


int main (void) {

	/* Unit Test - 1.1 */
	char str1 [] = {"Hello"};
	assert (solutionOne_1_1 (str1, sizeof (str1) / sizeof (str1[0])) == false);

	/* Unit Test - 1.2 */
	char str2 [] = {"Hello"};
	solutionOne_1_2 (str2, sizeof (str2) / sizeof (str2[0]));
	cout << str2 << endl;

	/* Unit Test - 1.3 */
	char str3 [] = {"Woorld"};
	solutionOne_1_3 (str3, sizeof (str3) / sizeof (str3[0]));
	cout << str3 << endl;

	/* Unit Test - 1.4 */
	string str4 = "Hello World";
	string str5 = "World Hello";

	assert (solutionOne_1_4 (str4, str5) == true);
	assert (solutionTwo_1_4 (str4, str5) == true);

	/* Unit Test - 1.6 */
	int n = 4;
	int matrix [][4] = {{10, 20, 30, 40},
						{50, 50, 70, 80},
						{15, 25, 35, 45},
						{55, 65, 75, 85}};

	printMatrix (n, matrix);
	solutionOne_1_6 (n, matrix);
	printMatrix (n, matrix);

	return 0;
}
//------------------------------------------------------------------------------
// FA2022_PA7_dynamic_array_allocation.cpp
// 
// Author: Gaddis 9E pp.554-555
//------------------------------------------------------------------------------

//  : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdlib>
#include <iostream>
#include <string>

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cin;
using std::cout;
using std::string;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
static constexpr int MAX_MOVIES = 10;
static constexpr int NO_MODE = -1;

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
int getNumStudents();
int getMode(int* ia, int iaElementCount, int& occurred);
void reportMode();

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {
	// seed random number generator
	srand((unsigned int)time(0));

	int numStudents;
	while ((numStudents = getNumStudents()) > 0) {

		// dynamically allocate array for number of movies watched by each student
		int* moviesWatched = new int[numStudents];

		// preserve original pointer!
		int* pi = moviesWatched;

		// fill int array with random numbers
		for (int i = 0; i < numStudents; i++, pi++) {
			*pi = rand() % MAX_MOVIES;
			cout << "Student " << i + 1 << " watched: " << *pi << " movies\n";
		}

		int occurrenceCount = 0;
		int mode = getMode(moviesWatched, numStudents, occurrenceCount);

		if (mode == NO_MODE) {
			cout << "\nNo mode\n";
		}
		else {
			// report the mode of the moviesWatched array
			cout << "\nMode " << mode
				<< " occurred " << occurrenceCount << " times\n";
		}

		// release dynamically allocated array memory
		delete[] moviesWatched;
	}

	return 0;

}

//------------------------------------------------------------------------------
// returns number of students entered
//------------------------------------------------------------------------------
int getNumStudents() {
	cout << "\nHow many students were surveyed? ";
	int n;
	cin >> n;
	cout << '\n';

	return n;
}

//------------------------------------------------------------------------------
// -returns the mode of the passed int array of given element count
// -updates int reference parameter to number of times the mode occurred
// -if no element occurred more than once, there is no mode
//------------------------------------------------------------------------------
int getMode(int* ia, int iaElementCount, int& occurred) {
	// preserve original pointer
	int* pIa = ia;

	// students watched between 0 and MAX_MOVIES, inclusive
	int* pCounts = new int[MAX_MOVIES + 1];

	// preserve original pointer to array
	int* pC = pCounts;

	// zero array memory
	for (int i = 0; i <= MAX_MOVIES; i++, pC++) {
		*pC = 0;
	}

	// count occurrences of each number of movies watched
	for (int i = 0; i < iaElementCount; i++, pIa++) {

		for (int z = 0; z <= MAX_MOVIES; z++) {
			if (z == *pIa) {
				pCounts[z]++;
				break;
			}
		}
	}

	// calculate mode
	int mode = 0;
	occurred = 0;   // reference parameter tracks mode occurrences

	// restore original pointer to array
	pC = pCounts;

	for (int i = 0; i <= MAX_MOVIES; i++, pC++) {
		if (*pC > occurred) {
			mode = i;
			occurred = *pC;
		}
	}
	// release dynamically allocated array memory
	delete[] pCounts;

	// report no mode condition
	if (occurred < 2) {
		return NO_MODE;
	}

	return mode;
}

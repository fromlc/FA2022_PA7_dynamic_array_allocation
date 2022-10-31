//------------------------------------------------------------------------------
// FA2022_PA7_dynamic_array_allocation.cpp
// 
// Author: Gaddis 9E pp.554-555
//------------------------------------------------------------------------------
#include <cstdlib>
#include <iostream>
#include <string>

#include "input_util.h"

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
// globals
//------------------------------------------------------------------------------
const string prompt = "\nEnter the number of students (0 quits): ";
const string errorPrompt("Sorry, that won't work as number of students.");

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
inline void appSetup();
inline void appLoop();
int getNumStudents();
void reportMode(int* moviesWatched, int numStudents);
void getArrayData(int* moviesWatched, int numStudents);
int getMode(int* ia, int iaElementCount, int& occurred);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

	appSetup();
	appLoop();

	cout << "\nGoodbye!\n";

	return 0;
}

//------------------------------------------------------------------------------
// display app banner
//------------------------------------------------------------------------------
inline void appSetup() {
	// seed random number generator
	srand((unsigned int)time(0));

	cout << "\n\nCalculate mode for number of movies";
	cout << " that students watched in one month\n\n";

	setErrorPrompt(errorPrompt);
}

//------------------------------------------------------------------------------
// user input loop, 0 quits
//------------------------------------------------------------------------------
inline void appLoop() {
	// loop until user quits
	int ns;
	while ((ns = getNumStudents()) > 0) {

		// dynamically allocate array for number of movies each student watched
		int* moviesWatched = new int[ns];

		// fill array with random data #TODO read from file?
		getArrayData(moviesWatched, ns);

		// find and display the mode of the array 
		reportMode(moviesWatched, ns);

		// release dynamically allocated array memory
		delete[] moviesWatched;
	}
}

//------------------------------------------------------------------------------
// returns true on positive number of students entered, false otherwise
//------------------------------------------------------------------------------
int getNumStudents() {

	// getConsoleInt() displays this string on bad input
	try {
		// prompt for int input
		return getConsoleInt(prompt);
	}
	catch (UserQuitException& e) {
		return 0;
	}
}

//------------------------------------------------------------------------------
// fill array with data, #TODO random numbers for now
//------------------------------------------------------------------------------
void getArrayData(int* pWatched, int numStudents) {

	cout << '\n';

	// fill int array with random numbers and display them
	for (int i = 0; i < numStudents; i++, pWatched++) {

		*pWatched = rand() % MAX_MOVIES;
		cout << "Student " << i + 1 << " watched: " << *pWatched << " movies\n";
	}
}

//------------------------------------------------------------------------------
// display the mode of the passed array
//------------------------------------------------------------------------------
void reportMode(int* moviesWatched, int numStudents) {

	// find the mode of the filled array
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
}

//------------------------------------------------------------------------------
// -returns the mode of the passed int array of given element count
// -calculates a single mode #TODO some data sets have two modes
// -updates int reference parameter to number of times the mode occurred
// -if no element occurred more than once, there is no mode
//------------------------------------------------------------------------------
int getMode(int* pIa, int iaElementCount, int& occurred) {

	// track element occurrences with reference parameter
	occurred = 0;

	// dynamically allocate int array to hold counts of movies watched
	// students watched between 0 and MAX_MOVIES, inclusive
	int* pCounts = new int[MAX_MOVIES + 1];

	// zero allocated int array memory
	memset(pCounts, 0, (MAX_MOVIES + 1) * sizeof(int));

	// find a single mode #TODO 
	int mode = 0;

	// calculate mode
	for (int i = 0; i < iaElementCount; i++, pIa++) {

		// x is the number of movies that student #i watched
		int x = *pIa;

		//----------------------------------------------------------------------------
		// -bump count of students that watched x movies
		// -find the highest count of students watching the same number of movies
		// -the corresponding number of movies watched will be the mode
		//----------------------------------------------------------------------------

		if (++(pCounts[x]) > occurred) {
			occurred = pCounts[x];
			mode = x;
		}
	}

	// preserve original pointer to allocated array memory for delete[]
	int* pC = pCounts;

	// report how many times each element occurred
	for (int i = 0; i <= MAX_MOVIES; i++, pC++) {
		if (*pC) {
			cout << '\n' << *pC << " students watched " << i << " movies";
		}
	}
	cout << '\n';

	// release dynamically allocated array memory
	delete[] pCounts;

	// report the mode, or no mode condition
	return (occurred < 2) ? NO_MODE : mode;
}

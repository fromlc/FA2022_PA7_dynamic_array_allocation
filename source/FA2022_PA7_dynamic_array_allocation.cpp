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
static int* g_pMoviesWatched = nullptr;
static int g_numStudents = 0;

const string prompt = "\nEnter the number of students (0 or Q quits): ";
const string errorPrompt("Sorry, that won't work as number of students.");

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
inline void appSetup();
inline void appLoop();
int getNumStudents();
void reportMode();
void getArrayData();
int getMode(int& modeOccurs);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

	appSetup();
	appLoop();

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

	setPrompts(prompt, errorPrompt);
}

//------------------------------------------------------------------------------
// user input loop, 0 quits
//------------------------------------------------------------------------------
inline void appLoop() {

	// loop until user quits
	while ((g_numStudents = getNumStudents()) > 0) {

		// dynamically allocate array for number of movies each student watched
		g_pMoviesWatched = new int[g_numStudents];

		// fill array with random data #TODO read from file?
		getArrayData();

		// find and display the mode of the array 
		reportMode();

		// release dynamically allocated array memory
		delete[] g_pMoviesWatched;
	}

	cout << "\nGoodbye!\n";
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
		e;		// #TODO prevents unreferenced local var e
		return 0;
	}
}

//------------------------------------------------------------------------------
// fill array with data, #TODO random numbers for now
//------------------------------------------------------------------------------
void getArrayData() {

	cout << '\n';

	// preserve pointer to data array
	int* pData = g_pMoviesWatched;

	// fill int array with random numbers and display them
	for (int i = 0; i < g_numStudents; i++, pData++) {

		*pData = rand() % MAX_MOVIES;
		cout << "Student " << i + 1 
			<< " watched: " << *pData << " movies\n";
	}
}

//------------------------------------------------------------------------------
// display the mode of the g_pMoviesWatched data array
//------------------------------------------------------------------------------
void reportMode() {

	// find the mode of the filled array
	int occurrenceCount = 0;
	int mode = getMode(occurrenceCount);

	if (mode == NO_MODE) {
		cout << "\nNo mode\n";
	}
	else {
		// display the mode
		cout << "\nMode " << mode
			<< " occurred " << occurrenceCount << " times\n";
	}
}

//------------------------------------------------------------------------------
// -returns the mode of int data array g_pMoviesWatched with
//		 g_numStudents elements
// -calculates a single mode #TODO some data sets have two modes
// -updates int reference parameter to number of times the mode occurred
// -if no element occurred more than once, there is no mode
//------------------------------------------------------------------------------
int getMode(int& modeOccurs) {

	// track element occurrences with reference parameter
	modeOccurs = 0;

	// dynamically allocate int array to hold counts of movies watched
	// students watched between 0 and MAX_MOVIES, inclusive
	int* pCounts = new int[MAX_MOVIES + 1];

	// zero memory allocated for counts
	memset(pCounts, 0, (MAX_MOVIES + 1) * sizeof(int));

	// find a single mode #TODO 
	int mode = 0;

	// save data array start address
	int* pData = g_pMoviesWatched;

	// find data array mode
	for (int i = 0; i < g_numStudents; i++, pData++) {

		// x is the number of movies that student #i watched
		int x = *pData;

		//----------------------------------------------------------------------------
		// -add 1 to count of students who watched x movies
		// -find highest count of students who watched the same number of movies
		// -corresponding number of movies watched is be the mode
		//----------------------------------------------------------------------------

		// point to the count of x movies watched
		int* pThisCount = (pCounts + x);

		// increase count of students watched x movies
		++(*pThisCount);

		// check whether this count is the new mode
		if ((*pThisCount) > modeOccurs) {
			modeOccurs = *pThisCount;
			mode = x;
		}
	}

	// preserve pointer to allocated array memory for delete[]
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
	return (modeOccurs < 2) ? NO_MODE : mode;
}

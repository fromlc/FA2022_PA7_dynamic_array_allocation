//------------------------------------------------------------------------------
// FA2022_PA7_dynamic_array_allocation.cpp
// 
// Author: Gaddis 9E pp.554-555
//------------------------------------------------------------------------------
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "input_util.h"

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cin;
using std::cout;
using std::string;
using std::vector;

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
int actualMode(vector<int>& v, int mode, int modeOccurs);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

	appSetup();
	appLoop();

	return 0;
}

//------------------------------------------------------------------------------
// app setup tasks
//------------------------------------------------------------------------------
inline void appSetup() {
	// seed random number generator
	srand((unsigned int)time(0));

	// app banner
	cout << "\n\nCalculate mode for number of movies";
	cout << " that students watched in one month\n\n";

	// set user prompts used by getConsoleInt()
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
		return getConsoleInt();
	}
	catch (UserQuitException& e) {
		// #TODO prevents unreferenced local var e warning
		e;
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
		cout << "\nNo single mode exists\n";
	}
	else {
		// display the mode
		cout << "\nMode " << mode
			<< " occurred " << occurrenceCount << " times\n";
	}
}

//------------------------------------------------------------------------------
// -returns the mode of int data array g_pMoviesWatched with
//		 g_numStudents elements, or NO_MODE
// -calculates a single mode
// -updates int reference parameter to number of times the mode occurred
// -if all elements occurred the same number of times,
//		there is no mode
// -if > 1 elements occurred the same number of times as the mode,
//		there is no mode
// -#TODO some data sets have two modes
//------------------------------------------------------------------------------
int getMode(int& modeOccurs) {

	// find a single mode #TODO 
	int mode = 0;

	// initialize reference parameter
	modeOccurs = 0;

	// track count occurrences
	vector<int> vCounts;

	// must force needed number of counts in vector
	vCounts.resize(MAX_MOVIES + 1, 0);

	// save data array start address
	int* pData = g_pMoviesWatched;

	// find the mode of data array
	for (int i = 0; i < g_numStudents; i++, pData++) {

		// x is the number of movies that student #i watched
		int x = *pData;

		//----------------------------------------------------------------------------
		// -add 1 to count of students who watched x movies
		// -find highest count of students who watched the same number of movies
		// -corresponding number of movies watched is the mode
		//----------------------------------------------------------------------------

		// increase count of students who watched x movies
		// and check whether x is the new mode

		if (++vCounts.at(x) > modeOccurs) {
			modeOccurs = vCounts.at(x);
			mode = x;
		}
	}

	// display how many times each element occurred
	int vIndex = 0;
	for (int count : vCounts) {
		if (count > 0) {
			cout << '\n' << count << " students watched "
				<< vIndex << " movies";
		}
		vIndex++;
	}

	cout << '\n';

	//--------------------------------------------------------------------------
	// report mode, or that there is no mode
	//--------------------------------------------------------------------------
	return modeOccurs < 2 ? NO_MODE : actualMode(vCounts, mode, modeOccurs);
}

// ---------------------------------------------------------------------
// screen further for no mode, or no single mode
// ---------------------------------------------------------------------
int actualMode(vector<int>& v, int mode, int modeOccurs) {

	// -------------------------------------------------------------------------
	// check for all counts the same, if so there's no mode
	// -------------------------------------------------------------------------
	bool allCountsSame = true;
	int x = v.back();

	for (int count : v) {
		if (count != x) {
			allCountsSame = false;
			break;
		}
	}

	if (allCountsSame) {
		return NO_MODE;
	}

	// -------------------------------------------------------------------------
	// check for more than 1 mode, if so there's no mode #TODO
	// -------------------------------------------------------------------------
	vector<int> vModes{};

	// check for same number of occurrences as mode
	for (int count : v) {
		if (count == modeOccurs) {
			vModes.push_back(count);
		}
	}

	// -------------------------------------------------------------------------
	// return:
	//		NO_MODE if 2+ counts occurred same number of times as mode,
	//		passed value of mode otherwise
	// -------------------------------------------------------------------------
	return (vModes.size() > 1) ? NO_MODE : mode;
}
//------------------------------------------------------------------------------
// FA2022_PA7_dynamic_array_allocation.cpp
// 
// Author: Gaddis 9E pp.554-555
//------------------------------------------------------------------------------
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>

#include "input_util.h"

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cout;
using std::string;
using std::unordered_map;

//------------------------------------------------------------------------------
// conditional compiles
//------------------------------------------------------------------------------
// ALL_ONES is defined the data set contains all 1's 
//#define ALL_ONES		// comment this line to generate random numbers

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
static constexpr int MAX_MOVIES = 10;

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
static int* g_pMoviesWatched = nullptr;
static int g_numStudents = 0;

const string g_prompt = "\nEnter the number of students (0 or Q quits): ";
const string g_errorPrompt("Sorry, that won't work as number of students.");

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
inline void appSetup();
inline void appLoop();
int getNumStudents();
void loadArrayData();
void reportMode();
int getMode(int& mode1, int& mode2, int& modeOccurs);

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
	setPrompts(g_prompt, g_errorPrompt);
}

//------------------------------------------------------------------------------
// user input loop, 0 quits
//------------------------------------------------------------------------------
inline void appLoop() {
	int mode = 0;
	int modeOccurs = 0;

	// loop until user quits
	while ((g_numStudents = getNumStudents()) > 0) {

		// dynamically allocate array for number of movies each student watched
		g_pMoviesWatched = new int[g_numStudents];

		// fill array with random data #TODO read from file?
		loadArrayData();

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
void loadArrayData() {

	cout << '\n';

	// preserve pointer to data array
	int* pData = g_pMoviesWatched;

	// fill int array with random numbers and display them
	for (int i = 0; i < g_numStudents; i++, pData++) {

#ifdef ALL_ONES
		// specific test case: all data values are the same
		*pData = 1;
#else
		*pData = rand() % MAX_MOVIES;
#endif
		cout << "Student " << i + 1
			<< " watched: " << *pData << " movies\n";
	}
}

//------------------------------------------------------------------------------
// display the mode of the g_pMoviesWatched data array
//------------------------------------------------------------------------------
void reportMode() {

	// find the mode of the filled array
	int mode1, mode2;
	int modeOccurs = 0;

	int modeCount = getMode(mode1, mode2, modeOccurs);
	switch (modeCount) {
	case 0:
		cout << "\nNo mode exists for this dataset\n";
		return;

	case 1:
		cout << "\nMode " << mode1
			<< " occurred " << modeOccurs << " times\n";
		return;

	case 2:
		cout << "\nModes " << mode1 << " and " << mode2
			<< " occurred " << modeOccurs << " times\n";
		return;

	default:
		cout << "Error in getMode()\n";
	}
}

//------------------------------------------------------------------------------
// -returns the number of modes in data array g_pMoviesWatched with
// -updates int reference parameters
// -if all elements occurred the same number of times,
//		there is no mode
// -if > 1 elements occurred the same number of times as the mode,
//		there is no mode
//------------------------------------------------------------------------------
int getMode(int& mode1, int& mode2, int& modeOccurs) {

	//--------------------------------------------------------------------------
	// maps contain <key, value> pairs
	// dataOccurs will contain these pairs:
	//		key = x, number of movies watched
	//		value = number of students who watched x movies
	//--------------------------------------------------------------------------
	unordered_map<int, int> dataOccurs;

	// use working pointer pData to preserve address in g_pMoviesWatched
	int* pData = g_pMoviesWatched;

	//--------------------------------------------------------------------------
	// fill dataOccurs map with <key, value> pairs
	//		key = x, number of movies watched
	//		value = number of students who watched x movies
	//--------------------------------------------------------------------------
	for (int i = 0; i < g_numStudents; i++, pData++) {
		dataOccurs[*pData]++;
	}

	// initialize reference parameters
	modeOccurs = 1;

	// find the biggest number of occurrences
	// this will be the mode, or the first of two modes
	for (auto it = dataOccurs.begin(); it != dataOccurs.end(); it++) {
		if (it->second > modeOccurs) {
			mode1 = it->first;
			modeOccurs = it->second;
		}
	}

	// assume one mode
	int modeCount = 1;

	// find other counts that occurred the same number of times
	for (auto it = dataOccurs.begin(); it != dataOccurs.end(); it++) {

		if (it->second == modeOccurs && it->first != mode1) {
			
			// 2 modes max
			if (++modeCount > 2) {
				return 0;
			}

			mode2 = it->first;
		}
	}

	return modeCount;
}
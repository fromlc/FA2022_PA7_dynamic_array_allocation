//------------------------------------------------------------------------------
// FA2022_PA7_dynamic_array_allocation.cpp
// 
// Author: Gaddis 9E pp.554-555
//------------------------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include <string>

#include "RandomArray.h"

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cin;
using std::cout;
using std::string;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
static constexpr int MAX_STUDENTS = 10;
static constexpr int MAX_MOVIES_WATCHED = 10;

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
inline void displayBanner();
int getNumStudents();
void displayMode(RandomArray* p);
void displayMean(RandomArray* p);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

	displayBanner();

	// loop until the number of students entered is 0
	int numStudents;
	while ((numStudents = getNumStudents()) > 0) {
		RandomArray* pRa = new RandomArray(numStudents, MAX_MOVIES_WATCHED);

		displayMode(pRa);
		displayMean(pRa);

		// release dynamically allocated array memory
		delete pRa;
	}

	cout << "Goodbye!\n";

	return 0;
}

//------------------------------------------------------------------------------
// display app banner
//------------------------------------------------------------------------------
inline void displayBanner() {
	cout << "\nCalculate mode for number of movies";
	cout << " that students watched in one month\n\n";
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
// display the array's mode
//------------------------------------------------------------------------------
void displayMode(RandomArray* p) {
	int mode, modeOccurs;

	if (!p->getMode(mode, modeOccurs)) {
		cout << "\nThere is no mode, no element occurred more than once.\n";
	}
	else {
		cout << "\nMode " << mode
			<< " occurred " << modeOccurs << " times\n";
	}
}

//------------------------------------------------------------------------------
// display the array's mean
//------------------------------------------------------------------------------
void displayMean(RandomArray* p) {

	cout << "\nMean: " << p->getMean() << "\n";
}


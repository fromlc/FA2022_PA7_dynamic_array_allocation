//------------------------------------------------------------------------------
// FA2022_PA7_dynamic_array_allocation.cpp
// 
// Author: Gaddis 9E pp.554-555
//------------------------------------------------------------------------------

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include "RandomArray.h"

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cin;
using std::cout;
using std::fixed;
using std::setprecision;
using std::showpoint;
using std::string;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
static constexpr int MAX_STUDENTS = 10;
static constexpr int MAX_MOVIES_WATCHED = 10;

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
inline void appInit();
int getNumStudents();
void displayMode(RandomArray* p);
void displayMean(RandomArray* p);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

	appInit();

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
// app setup and display app banner
//------------------------------------------------------------------------------
inline void appInit() {
	// format numerical output
	cout << setprecision(3) << fixed << showpoint;

	// display banner
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

	// set custom strings for data display
	p->setOutputStrings("Student ", " watched ", " movies");

	// display RandomArray data values
	cout << *p << '\n';

	int modeOne, modeOccurs;
	bool isSingleMode = p->getSingleMode(modeOne, modeOccurs);

	// display mode information
	if (!isSingleMode) {
		cout << "There is no mode, no element occurred more than once.\n";
	}
	else {
		cout << "Mode " << modeOne
			<< " occurred " << modeOccurs << " times\n";
	}
}

//------------------------------------------------------------------------------
// display the array's mean
//------------------------------------------------------------------------------
void displayMean(RandomArray* p) {

	cout << "\nMean: " << p->getMean() << "\n";
}


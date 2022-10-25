//------------------------------------------------------------------------------
// RandomArray.cpp : class definition
//------------------------------------------------------------------------------
#include <cstdlib>		// rand()
#include <cstring>		// memset()
#include <ctime>		// srand(time(0))
#include <vector>		// data store

#include "RandomArray.h"

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::ostream;
using std::string;
using std::vector;

//----------------------------------------------------------------------------
// constructors
//----------------------------------------------------------------------------
RandomArray::RandomArray() : RandomArray(NUM_ELEMENTS, MAX_ELEMENT_VALUE) {}

//----------------------------------------------------------------------------
RandomArray::RandomArray(int nElements, int xMax) {

	m_numElements = nElements;
	m_vE.reserve(nElements);

	m_elementMax = xMax;

	// values range from 0 to xMax
	// allocateInts fixes compiler warning c26451
	//m_pCounts = new int[xMax + 1];
	int allocateInts = xMax + 1;
	m_pCounts = new int[allocateInts];

	// store random data values 0 to m_elementMax
	fillRandomArray();

	// init counts array and set mode member variables
	setupModeVars();

	// set default strings for data display
	setOutputStrings("Person", "acted", "times");
}

//----------------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------------
RandomArray::~RandomArray() {
	delete[] m_pCounts;
}

//----------------------------------------------------------------------------
// getters
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
int RandomArray::getMaxDataValue() { return m_elementMax; }

//----------------------------------------------------------------------------
int RandomArray::getDataItemCount() { return m_numElements; }

//----------------------------------------------------------------------------
// updates reference params with mode info calculated in setupModeVars()
// returns true if data set has a single mode, false otherwise
//----------------------------------------------------------------------------
bool RandomArray::getSingleMode(int& modeOne, int& modeOneOccurs) {
	modeOne = m_modeOne;
	modeOneOccurs = m_modeOneOccurs;
	return m_singleMode;
}

//----------------------------------------------------------------------------
// updates reference params with mode info calculated in setupSecondMode()
// returns true if data set has two modes, false otherwise
//----------------------------------------------------------------------------
bool RandomArray::getSecondMode(int& modeTwo, int& modeTwoOccurs) {
	modeTwo = m_modeTwo;
	modeTwoOccurs = m_modeTwoOccurs;
	return m_twoModes;
}

//----------------------------------------------------------------------------
// calculates arithmetic mean of the array
//----------------------------------------------------------------------------
float RandomArray::getMean() {
	// accumulator
	int total = 0;

	// accumulate total and calculate mean
	for (auto e : m_vE) {
		total += e;
	}

	m_mean = (float)total / (float)m_numElements;
	return m_mean;
}

//----------------------------------------------------------------------------
// setters
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// use passed strings for output with overloaded operator << 
//
// Output format: 
//		"Student x saw z movies" 
//		"Person x walked z miles" 
//
// subject is the actor (Student, Person)
// verb is the act (saw, walked)
// object is the thing acted on or the units acted (movies, miles)
//----------------------------------------------------------------------------
void RandomArray::setOutputStrings(const string& subject,
	const string& verb,
	const string& object) {
	m_subject = subject;
	m_verb = verb;
	m_object = object;
}

//------------------------------------------------------------------------------
// private util
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// fill array with random numbers between 0 and the max element value
//------------------------------------------------------------------------------
void RandomArray::fillRandomArray() {
	// seed random number generator
	srand((unsigned int)time(0));

	int max = m_elementMax + 1;

	// get rid of any old vector elements
	m_vE.clear();

	// initialize vector of data values
	for (int i = 0; i < m_numElements; i++) {
		m_vE.push_back(rand() % max);
	}

	// zero int array memory for counting element data occurrence counts
	memset(m_pCounts, 0, max * sizeof(int));
}

//----------------------------------------------------------------------------
// initialize mode member vars and approximate a single mode
//----------------------------------------------------------------------------
void RandomArray::setupModeVars() {
	m_modeTwo = 0;
	m_modeTwoOccurs = 0;

	// number of times array mode occurs
	m_modeOneOccurs = 0;

	// init counts array and assumes a single mode
	for (auto e : m_vE) {
		//----------------------------------------------------------------------------
		// e is the number of movies that student #i watched
		// 
		// -bump count of students that watched e movies
		// -find the highest count of students watching the same number of movies
		// -the corresponding number of movies watched is the mode
		//----------------------------------------------------------------------------
		if (++(m_pCounts[e]) > m_modeOneOccurs) {
			m_modeOneOccurs = m_pCounts[e];
			m_modeOne = e;
		}
	}

	// search for a second mode and set all mode booleans
	setupSecondMode();
}

//----------------------------------------------------------------------------
// search for a second mode and set all mode booleans
// updates reference parameters with member variable values
// returns true if data set has a second mode, false otherwise
//----------------------------------------------------------------------------
void RandomArray::setupSecondMode() {

	// init second mode member vars
	m_modeTwoOccurs = 0;
	m_modeTwo = 0;
	m_twoModes = false;
	m_singleMode = true;	// assume one mode
	m_noMode = false;

	// a mode must occur at least twice
	if (m_modeOneOccurs < 2)
		return;

	// find a different count value equal to the first mode
	for (int i = 0; i < m_elementMax; i++) {

		if (m_pCounts[i] == m_modeOneOccurs) {
			if (i == m_modeOne) {
				continue;
			}
			if (m_twoModes) {
				m_singleMode = false;
				m_twoModes = false;
				m_noMode = true;
				m_modeTwo = 0;
				m_modeTwoOccurs = 0;
				return;
			}

			m_singleMode = false;
			m_twoModes = true;
			m_noMode = false;

			m_modeTwoOccurs = m_modeOneOccurs;
			m_modeTwo = i;
		}
	}
}

//--------------------------------------------------------------------------------
// overload operator <<
//--------------------------------------------------------------------------------
ostream& operator<<(ostream& os, const RandomArray& ra) {
	int i = 0;
	for (auto e : ra.m_vE) {
		os << ra.m_subject << ++i << ra.m_verb << e << ra.m_object << '\n';
	}
	return os;
}

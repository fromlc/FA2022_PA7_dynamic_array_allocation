//------------------------------------------------------------------------------
// RandomArray.cpp : class definition
//------------------------------------------------------------------------------
#include <algorithm>	// sort(), copy()
#include <cstdlib>		// rand()
#include <cstring>		// memset()
#include <ctime>		// srand(time(0))
#include <iterator>		// back_inserter()
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
	m_vData.reserve(nElements);
	m_vSortedData.reserve(nElements);

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

	// copy data to another vector, sort copy, calculate median
	setupMedian();

	// calculate arithmetic mean
	setupMean();

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
int RandomArray::getMaxDataValue() const { return m_elementMax; }

//----------------------------------------------------------------------------
int RandomArray::getDataItemCount() const { return m_numElements; }

//----------------------------------------------------------------------------
// returns number of modes for data set: 0, 1, or 2
//----------------------------------------------------------------------------
int RandomArray::getModeCount() const { return m_modeCount; }

//----------------------------------------------------------------------------
// updates reference parameters with member variable values
// returns number of modes for data set: 0, 1, or 2
//----------------------------------------------------------------------------
int RandomArray::getModeData(int& mode1, int& mode2, int& occurs) const {
	mode1 = m_mode1;
	mode2 = m_mode2;
	occurs = m_modeOccurs;
	return m_modeCount;
}

//----------------------------------------------------------------------------
// calculates arithmetic mean of the array
//----------------------------------------------------------------------------
float RandomArray::getMean() { return m_mean; }

//----------------------------------------------------------------------------
// returns median of the array
//----------------------------------------------------------------------------
void RandomArray::getMedianData(int& median1, int& median2) {
	median1 = m_median1;
	median2 = m_median2;
}

//----------------------------------------------------------------------------
// get a vector copy of the random data values
// #TODO make inline
//----------------------------------------------------------------------------
void RandomArray::getRandomDataVector(vector<int>& vCopy) {

	// use iterators to copy random data vector
	copy(m_vData.begin(), m_vData.end(), back_inserter(vCopy));
}

//----------------------------------------------------------------------------
// get a vector copy of sorted data values
//----------------------------------------------------------------------------
void RandomArray::getSortedDataVector(vector<int>& vCopy) {

	// use iterators to copy random data vector
	copy(m_vSortedData.begin(), m_vSortedData.end(), back_inserter(vCopy));
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
	m_vData.clear();

	// initialize vector of data values
	for (int i = 0; i < m_numElements; i++) {
		m_vData.push_back(rand() % max);
	}

	// zero int array memory for counting element data occurrence counts
	memset(m_pCounts, 0, max * sizeof(int));
}

//----------------------------------------------------------------------------
// initialize mode member vars and approximate a single mode
//----------------------------------------------------------------------------
void RandomArray::setupModeVars() {
	m_mode2 = 0;

	// number of times array mode occurs
	m_modeOccurs = 0;

	// init counts array and assumes a single mode
	for (const auto dataItem : m_vData) {
		//----------------------------------------------------------------------------
		// dataItem is the number of movies that student #i watched
		// 
		// -bump count of students that watched that many
		// -find max count of students watching the same number of movies
		// -that number of movies watched is the mode
		//----------------------------------------------------------------------------
		if (++(m_pCounts[dataItem]) > m_modeOccurs) {
			m_modeOccurs = m_pCounts[dataItem];
			m_mode1 = dataItem;
		}
	}

	// search for a second mode and set mode count
	setupSecondMode();
}

//----------------------------------------------------------------------------
// search for a second mode and set mode count
// updates reference parameters with member variable values
// returns true if data set has a second mode, false otherwise
//----------------------------------------------------------------------------
void RandomArray::setupSecondMode() {

	// a mode must occur at least twice
	if (m_modeOccurs < 2) {
		m_modeCount = 0;
		m_mode1 = 0;
		m_mode2 = 0;
		return;
	}

	// init second mode member vars
	m_modeCount = 1;	// assume one mode for data set

	// find a different count value equal to the first mode
	for (int i = 0; i < m_elementMax; i++) {

		if (m_pCounts[i] == m_modeOccurs) {
			// ignore first mode already found
			if (i == m_mode1) {
				continue;
			}
			// already found second mode, third candidate means zero modes
			if (m_modeCount == 2) {
				m_modeCount = 0;
				return;
			}
			// candidate second mode, keep looking
			m_modeCount = 2;
			m_mode2 = i;
		}
	}
}

//----------------------------------------------------------------------------
// calculates median of the array
// returns:
//		middle item when odd number of data items, 
//		average of 2 middle items otherwise
//----------------------------------------------------------------------------
void RandomArray::setupMedian() {
	// use iterators to copy data vector
	copy(m_vData.begin(), m_vData.end(), back_inserter(m_vSortedData));
	// sort the copy
	sort(m_vSortedData.begin(), m_vSortedData.end());

	// assume odd number of data items
	int medianIndex = m_numElements / 2;

	// odd number of data items: return middle item
	if (m_numElements % 2 == 1) {
		m_median1 = m_median2 = m_vSortedData.at(medianIndex);
		return;
	}

	// even number of data items: return average of 2 middle items
	int mI1 = medianIndex - 1;
	int mI2 = medianIndex;

	m_median1 = m_vSortedData.at(mI1);
	m_median2 = m_vSortedData.at(mI2);
}

//----------------------------------------------------------------------------
// calculates arithmetic mean of the array
//----------------------------------------------------------------------------
void RandomArray::setupMean() {
	// accumulator
	int total = 0;

	// accumulate total and calculate mean
	for (const auto dataItem : m_vData) {
		total += dataItem;
	}

	m_mean = (float)total / (float)m_numElements;
}

//------------------------------------------------------------------------------
// overload operator <<
//------------------------------------------------------------------------------
ostream& operator<<(ostream& os, const RandomArray& ra) {
	int i = 0;
	for (const auto dataItem : ra.m_vData) {
		os << ra.m_subject << ++i
			<< ra.m_verb << dataItem
			<< ra.m_object << '\n';
	}
	return os;
}

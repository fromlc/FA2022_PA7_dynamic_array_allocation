//------------------------------------------------------------------------------
// RandomArray.h : class declaration and definition
//------------------------------------------------------------------------------
#ifndef RANDOMARRAY_H
#define RANDOMARRAY_H

#include <cstdlib>		// rand()
#include <cstring>		// memset()
#include <ctime>		// srand(time(0))
#include <vector>		// for data

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::ostream;
using std::string;
using std::vector;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
static constexpr int DEFAULT_ELEMENTS = 100;
static constexpr int MAX_ELEMENTS = 100;
static constexpr int MAX_ELEMENT_VALUE = 10;
static constexpr int NO_MODE_EXISTS = -1;

//------------------------------------------------------------------------------
// RandomArray
//------------------------------------------------------------------------------
class RandomArray {
private:
	int m_numElements;
	vector<int> m_vE;		// data

	int m_elementMax;
	int* m_pCounts;			// array[m_elementMax] counts element occurrences

	int m_modeOccurs;		// how many times the mode occurs in the array
	int m_mode;				// find a single mode #TODO 

	float m_mean;

	string m_s1;			// for display with overloaded operator <<
	string m_s2;
	string m_s3;

public:
	//----------------------------------------------------------------------------
	// constructors
	//----------------------------------------------------------------------------
	RandomArray() : RandomArray(DEFAULT_ELEMENTS, MAX_ELEMENT_VALUE) {}

	//----------------------------------------------------------------------------
	RandomArray(int nElements, int xMax) {

		m_numElements = nElements;
		m_vE.reserve(nElements);

		m_elementMax = xMax;
		m_pCounts = new int[xMax + 1];		// values range from 0 to xMax

		m_mode = -1;
		m_modeOccurs = 0;

		// seed random number generator
		srand((unsigned int) time(0));

		// fill m_pElements array with random numbers between 0 and m_elementMax
		fillRandomArray();
	}

	//----------------------------------------------------------------------------
	// destructor
	//----------------------------------------------------------------------------
	~RandomArray() {
		delete[] m_pCounts;
	}

	//----------------------------------------------------------------------------
	// getters
	//----------------------------------------------------------------------------

	//----------------------------------------------------------------------------
	int getElementMax() { return m_elementMax; }

	//----------------------------------------------------------------------------
	int getNumElements() { return m_numElements; }

	//----------------------------------------------------------------------------
	// -calculates a single mode #TODO some data sets have two modes
	// -updates reference parameters to mode and how many times the mode occurred
	// -if no element occurred more than once return false, otherwise return true
	//----------------------------------------------------------------------------
	bool getMode(int& mode, int& modeOccurs) {
		// number of times array mode occurs
		m_modeOccurs = 0;

		// calculate mode
		for (auto e : m_vE) {

			// e is the number of movies that student #i watched

			//----------------------------------------------------------------------------
			// -bump count of students that watched e movies
			// -find the highest count of students watching the same number of movies
			// -the corresponding number of movies watched is the mode
			//----------------------------------------------------------------------------

			if (++(m_pCounts[e]) > m_modeOccurs) {
				m_modeOccurs = m_pCounts[e];
				m_mode = e;
			}
		}

		// update reference parameters
		mode = m_mode;
		modeOccurs = m_modeOccurs;

		return (modeOccurs < 2) ? false : true;
	}

	//----------------------------------------------------------------------------
	// calculates arithmetic mean of the array
	//----------------------------------------------------------------------------
	float getMean() {
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
	//----------------------------------------------------------------------------
	void setOutputStrings(const string&& s1,
						  const string&& s2, 
						  const string&& s3) {
		m_s1 = s1;
		m_s2 = s2;
		m_s3 = s3;
	}

private:
	//------------------------------------------------------------------------------
	// util
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// fill array with random numbers between 0 and the max element value
	//------------------------------------------------------------------------------
	void fillRandomArray() {
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
	// overload operator <<
	//----------------------------------------------------------------------------
	friend ostream& operator<<(ostream& os, const RandomArray& ra) {
		int i = 0;
		for (auto e : ra.m_vE) {
			os << ra.m_s1 << ++i << ra.m_s2 << e << ra.m_s3 << '\n';
		}
		return os;
	}
};
#endif	// RANDOMARRAY_H
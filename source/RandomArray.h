//------------------------------------------------------------------------------
// RandomArray.h : class declaration and definition
//------------------------------------------------------------------------------
#ifndef RANDOMARRAY_H
#define RANDOMARRAY_H

#include <cstdlib>		// rand()
#include <cstring>		// memset()
#include <ctime>		// srand(time(0))

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
static constexpr int DEFAULT_ELEMENTS = 100;
static constexpr int MAX_ELEMENTS = 100;
static constexpr int MAX_ELEMENT_VALUE = 10;
static constexpr int NO_MODE_EXISTS = -1;

class RandomArray {
private:
	int m_numElements;
	int* m_pElements;		// array[m_numElements] is data

	int m_elementMax;
	int* m_pCounts;			// array[m_elementMax] counts element occurrences

	int m_modeOccurs;		// how many times the mode occurs in the array
	int m_mode;				// find a single mode #TODO 

	float m_mean;

public:
	//----------------------------------------------------------------------------
	// constructors
	//----------------------------------------------------------------------------
	RandomArray() : RandomArray(DEFAULT_ELEMENTS, MAX_ELEMENT_VALUE) {}

	//----------------------------------------------------------------------------
	RandomArray(int nElements, int xMax) {

		m_numElements = nElements;
		m_pElements = new int[nElements];

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
		delete[] m_pElements;
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

		// working pointer pIa preserves original pointer value
		int* pIa = m_pElements;

		// calculate mode
		for (int i = 0; i < m_numElements; i++, pIa++) {

			// x is the number of movies that student #i watched
			int x = *pIa;

			//----------------------------------------------------------------------------
			// -bump count of students that watched x movies
			// -find the highest count of students watching the same number of movies
			// -the corresponding number of movies watched will be the mode
			//----------------------------------------------------------------------------

			if (++(m_pCounts[x]) > m_modeOccurs) {
				m_modeOccurs = m_pCounts[x];
				m_mode = x;
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

		// working pointer pIa preserves original pointer value
		int* pIa = m_pElements;
		
		// accumulate total and calculate mean
		for (int i = 0; i < m_numElements; i++, pIa++) {
			total += *pIa;
		}

		m_mean = (float)total / (float)m_numElements;
		return m_mean;
	}

	//------------------------------------------------------------------------------
	// util
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// fill array with random numbers between 0 and m_elementMax
	//------------------------------------------------------------------------------
	void fillRandomArray() {
		// preserve pointer to array for delete
		int* pE = m_pElements;
		for (int i = 0; i < m_numElements; i++, pE++) {
			*pE = rand() % m_elementMax;
		}

		// zero int array memory that will store elemnent occurrence counts
		memset(m_pCounts, 0, (m_elementMax + 1) * sizeof(int));
	}
};
#endif	// RANDOMARRAY_H
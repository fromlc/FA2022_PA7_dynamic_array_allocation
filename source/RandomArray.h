//------------------------------------------------------------------------------
// RandomArray.h : class declaration
//------------------------------------------------------------------------------
#ifndef RANDOMARRAY_H
#define RANDOMARRAY_H

#include <iostream>		// ostream
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
constexpr int DEFAULT_ELEMENTS = 100;
constexpr int MAX_ELEMENTS = 100;
constexpr int MAX_ELEMENT_VALUE = 10;
constexpr int NO_MODE_EXISTS = -1;

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
	RandomArray();
	RandomArray(int nElements, int xMax);

	//----------------------------------------------------------------------------
	// destructor
	//----------------------------------------------------------------------------
	~RandomArray();

	//----------------------------------------------------------------------------
	// getters
	//----------------------------------------------------------------------------
	int getElementMax();
	int getNumElements();

	//----------------------------------------------------------------------------
	// -calculates a single mode #TODO some data sets have two modes
	// -updates reference parameters to mode and how many times the mode occurred
	// -if no element occurred more than once return false, otherwise return true
	//----------------------------------------------------------------------------
	bool getMode(int& mode, int& modeOccurs);
	//----------------------------------------------------------------------------
	// calculates arithmetic mean of the array
	//----------------------------------------------------------------------------
	float getMean();

	//----------------------------------------------------------------------------
	// setters
	//----------------------------------------------------------------------------

	//----------------------------------------------------------------------------
	// use passed strings for output with overloaded operator << 
	//----------------------------------------------------------------------------
	void setOutputStrings(const string& s1, const string& s2, const string& s3);

private:
	//------------------------------------------------------------------------------
	// fill array with random numbers between 0 and the max element value
	//------------------------------------------------------------------------------
	void fillRandomArray();
	//----------------------------------------------------------------------------
	// overload operator <<
	//----------------------------------------------------------------------------
	friend ostream& operator<<(ostream& os, const RandomArray& ra);
};
#endif	// RANDOMARRAY_H
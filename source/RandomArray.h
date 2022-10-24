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

	int m_modeOne;			// single mode, or first of two modes
	int m_modeOneOccurs;	// how many times first or only mode occurs
	bool m_singleMode;		// do vector data values have a single mode?

	int m_modeTwo;
	int m_modeTwoOccurs;

	float m_mean;
	float m_median;			// #TODO

	//------------------------------------------------------------------------------
	// 3 custom strings for display with overloaded operator <<
	//------------------------------------------------------------------------------
	string m_subject;		// the actor
	string m_verb;			// the act
	string m_object;		// the thing acted on

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
	// updates reference parameters with member variable values
	// returns true if data set has a single mode, false
	//----------------------------------------------------------------------------
	bool getSingleMode(int& mode, int& modeOccurs);
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
	//-----------------------------------------------------------------------------
	// fill array with random numbers between 0 and the max element value
	//-----------------------------------------------------------------------------
	void fillRandomArray();
	//----------------------------------------------------------------------------
	// initialize all mode member variables
	//----------------------------------------------------------------------------
	void setupModeVars();
	//-----------------------------------------------------------------------------
	// overload operator <<
	//-----------------------------------------------------------------------------
	friend ostream& operator<<(ostream& os, const RandomArray& ra);
};
#endif	// RANDOMARRAY_H
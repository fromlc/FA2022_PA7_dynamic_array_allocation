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
constexpr int NUM_ELEMENTS		= 100;
constexpr int MAX_ELEMENT_VALUE = 10;
constexpr int NO_MODE_EXISTS	= -1;

//------------------------------------------------------------------------------
// RandomArray
//------------------------------------------------------------------------------
class RandomArray {
private:
	int m_numElements;
	vector<int> m_vE;		// data

	int m_elementMax;
	int* m_pCounts;			// array[m_elementMax + 1] counts data occurrences

	int m_modeOne;			// single mode, or first of two modes
	int m_modeTwo;			// second mode
	int m_modeOccurs;		// how many times first or only mode occurs
	int m_modeCount;		// how many modes for data set: 0, 1, or 2

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
	int getMaxDataValue() const;
	int getDataItemCount() const;

	//----------------------------------------------------------------------------
	// updates reference parameters with member variable values
	// returns true if data set has a single mode, false otherwise
	//----------------------------------------------------------------------------
	bool getSingleMode(int& modeOne, int& modeOneOccurs) const;
	//----------------------------------------------------------------------------
	// calculates second mode
	// updates reference parameters with member variable values
	// returns true if data set has a second mode, false otherwise
	//----------------------------------------------------------------------------
	bool getSecondMode(int& modeTwo) const;
	//----------------------------------------------------------------------------
	// returns number of modes for data set
	//----------------------------------------------------------------------------
	int getModeCount() const;
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
	// initialize mode member variables, calculate mode(s)
	//----------------------------------------------------------------------------
	void setupModeVars();
	void setupSecondMode();
	//-----------------------------------------------------------------------------
	// overload operator <<
	//-----------------------------------------------------------------------------
	friend ostream& operator<<(ostream& os, const RandomArray& ra);
};
#endif	// RANDOMARRAY_H
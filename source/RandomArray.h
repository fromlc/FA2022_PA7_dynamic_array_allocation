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
	vector<int> m_vData;
	vector<int> m_vSortedData;

	int m_elementMax;
	int* m_pCounts;			// array[m_elementMax + 1] counts data occurrences

	int m_mode1;			// single mode, or first of two modes
	int m_mode2;			// second mode
	int m_modeOccurs;		// how many times first or only mode occurs
	int m_modeCount;		// how many modes for data set: 0, 1, or 2

	float m_mean;			// arithmetic mean
	
	//------------------------------------------------------------------------------
	// middle value when odd number of elements, else average of two middle values
	//------------------------------------------------------------------------------
	int m_median1;
	int m_median2;

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
	// returns number of modes for data set
	//----------------------------------------------------------------------------
	int getModeCount() const;
	//----------------------------------------------------------------------------
	// updates reference parameters with member variable values
	// returns number of modes for data set: 0, 1, or 2
	//----------------------------------------------------------------------------
	int getModeValues(int& mode1, int& mode2, int& occurs) const;
	//----------------------------------------------------------------------------
	// calculates arithmetic mean of the array
	//----------------------------------------------------------------------------
	float getMean();
	//----------------------------------------------------------------------------
	// calculates median of the array
	//----------------------------------------------------------------------------
	void getMedianData(int& median1, int& median2);
	//----------------------------------------------------------------------------
	// get a vector copy of the random or sorted data values
	//----------------------------------------------------------------------------
	void getRandomDataVector(vector<int>& vCopy);
	void getSortedDataVector(vector<int>& vCopy);

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
	void setupMedian();
	//-----------------------------------------------------------------------------
	// overload operator <<
	//-----------------------------------------------------------------------------
	friend ostream& operator<<(ostream& os, const RandomArray& ra);
};
#endif	// RANDOMARRAY_H
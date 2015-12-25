#pragma once

#include "stdafx.h"
#include "Record2.h"

#include "RandomDice.h"

#include <string>
#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>

struct DataNormalizeMethod {
	enum Name { zscore = 0, dividStddev, zeroOneScaling, dividMinMaxRegion, shiftPositive, none, _SIZE };
	static std::string tostr(DataNormalizeMethod::Name n);

	DiceUniformInt dui;
	DataNormalizeMethod();

	DataNormalizeMethod::Name dice();
};

class RecordSet2: public boost::ptr_vector<Record2> {

private:
	typedef boost::ptr_vector<Record2> MyBase;
	typedef MyBase::value_type value_type;

private:

	Record2 min, max;			//keep min and max of each columns
	Record2 mean, stddev;		//keep mean and stddev of each columns

	void compMinMax();
	void compMin();

	void getColumn(unsigned int columnIndex, Record2& column) const;
	void compMean();
	void compStddev();
	void compMeanStddev();

	//normalization
	DataNormalizeMethod::Name usedNormalizedMethod;
	void normZscore();
	void normDividStddev();
	void normZeroOneScaling();
	void normDividMinMaxRegion();
	void normShiftPositive();

public:
	
	RecordSet2();
	RecordSet2(const RecordSet2& rs);

	unsigned int dim() const {
		return begin()->dim();
	}

	
	void normalize(DataNormalizeMethod::Name method);

	void normalizeRandom();

	DataNormalizeMethod::Name getUsedNormalizeMethod() const;

	//dump
	void dump(std::ostream& out) const;

};

std::ostream& operator<<(std::ostream& out, const RecordSet2& rs);


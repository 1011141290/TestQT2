#pragma once

#include "stdafx.h"

#include <vector>
#include <numeric>
#include <iostream>
#include <armadillo>


/////////////////////////////////////////////////////////////////////////////
class Record2: public arma::vec
{
private:
	typedef arma::vec MyBase;
public:
	Record2() {};
	Record2(const arma::vec& armaVec);
	Record2(const std::vector<double>& stdVec);
	Record2(unsigned int size, double fillValue);
	Record2(unsigned int size);
        Record2& operator=(const arma::vec& armaVec);

	unsigned int dim() const {
		return size();
	}

	double innerProduct(const Record2& other) const;
	void hadamardProd(const Record2& rhs);
	//distance
	double squareDist(const Record2& other) const;

        void split(Record2& positive, Record2& negative) const;
        unsigned int maxIntervalSplit();
        
	//normalization
	void normDividStddev(const Record2& stddev);
	void normZscore(const Record2& mean, const Record2& stddev);
	void normZeroOneScaling(const Record2& min, const Record2& max);
	void normDividMinMaxRegion(const Record2& min, const Record2& max);
	
	void normShiftPositive(const Record2& leftMin);

	double mean() const;
	double stddev() const;

	double sigmod() const;


	/////////////////////////////////////////////////////////////////////
	//dump
	void dump(std::ostream& out) const;
	void dumpIfNegative(std::ostream& out, const std::string& info) const;
};

std::ostream& operator<<(std::ostream& out, const Record2& r);


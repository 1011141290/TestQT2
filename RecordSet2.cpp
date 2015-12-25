#include "stdafx.h"
#include "RecordSet2.h"

#include <string>


///////////////////////////////////////////////////////////////////////////////////
DataNormalizeMethod::DataNormalizeMethod() : dui(0, DataNormalizeMethod::_SIZE - 1) {}

DataNormalizeMethod::Name DataNormalizeMethod::dice() {
	return (DataNormalizeMethod::Name)dui.next();
}


std::string DataNormalizeMethod::tostr(DataNormalizeMethod::Name n) {

	switch (n){
	case DataNormalizeMethod::zscore:
		return "zscore";
	case DataNormalizeMethod::dividStddev:
		return "dividStddev";

	case DataNormalizeMethod::zeroOneScaling:
		return "zeroOneScaling";

	case DataNormalizeMethod::dividMinMaxRegion:
		return "dividMinMaxRegion";

	case DataNormalizeMethod::shiftPositive:
		return "shiftPositive";

	case DataNormalizeMethod::none:
		return "none";

	}
	ASSERT_WITH_MSG(false, "DataNormalizeMethod::tostr..unknown normalization method" << n);
	return "unknown";
}




//////////////////////////////////////////////////////////////////////////////////
RecordSet2::RecordSet2() : MyBase(), usedNormalizedMethod(DataNormalizeMethod::none) {

}
RecordSet2::RecordSet2(const RecordSet2& rs) : MyBase(rs),
usedNormalizedMethod(rs.usedNormalizedMethod),
min(rs.min), max(rs.max), mean(rs.mean), stddev(rs.stddev) {}


void RecordSet2::compMin() {

	unsigned int sz = dim();
	min.resize(sz);				//preallocated memory, same as that of each Record2
	min.fill(arma::fill::zeros);

	for (const auto& i : (*this)) {
		const Record2& r = i;
		unsigned int j = 0;
		for (; j < sz; ++j) {
			if (r[j] < min[j])		//keeps min
				min[j] = r[j];
		}
	}//for
}


void RecordSet2::compMinMax() {

	//if (this->size() == 0 || min.size()>0)
	//	return;		//It is already computed or RecordSet is empty

	unsigned int sz = dim();
	min.resize(sz);				//preallocated memory, same as that of each Record2
	min.fill(arma::fill::zeros);
	max.resize(sz);
	max.fill(arma::fill::zeros);

	for (const auto& i : (*this)) {
		const Record2& r = i;

		unsigned int j = 0;
		for (; j < sz; ++j) {
			if (r[j] < min[j])		//keeps min
				min[j] = r[j];
			else if (r[j] > max[j]) {		//keeps max
				max[j] = r[j];
			}
			else {}
		}
	}//for
}
void RecordSet2::getColumn(unsigned int columnIndex, Record2& column) const {
	
	//if (column.size() != this->size())
	//	column.resize(this->size());		//size of column must be same as that of RecordSet

	unsigned int rowIndex = 0;
	for (const auto& i : (*this)) {			//reason is here
		column[rowIndex++] = i[columnIndex];
	}
}
void RecordSet2::compMean() {
	
	unsigned int dim = this->dim();
	mean.resize(dim);			//preallocated memory, one for all row Records

	Record2 column(this->size());
	unsigned int ci = 0;		//ci: column index
	for (; ci < dim; ++ci) {
		getColumn(ci, column);
		mean[ci] = column.mean();
	}
}
void RecordSet2::compStddev() {
	unsigned int dim = this->dim();
	stddev.resize(dim);			//preallocated memory, one for all row Records

	Record2 column(this->size());
	unsigned int ci = 0;		//ci: column index
	for (; ci < dim; ++ci) {
		getColumn(ci, column);
		stddev[ci] = column.stddev();
	}
}
void RecordSet2::compMeanStddev() {

	unsigned int dim = this->dim();
	mean.resize(dim);
	stddev.resize(dim);			//preallocated memory, one for all row Records

	Record2 column(this->size());
	unsigned int ci = 0;		//ci: column index
	for (; ci < dim; ++ci) {
		getColumn(ci, column);
		mean[ci] = column.mean();
		stddev[ci] = column.stddev();
	}
}


///////////////////////////////////////////////////////
//normalization

DataNormalizeMethod::Name RecordSet2::getUsedNormalizeMethod() const {
	return usedNormalizedMethod;
}

void RecordSet2::normalizeRandom() {

	//normalize(DataNormalizeMethod::shiftPositive);

	static DataNormalizeMethod dm;
	
	usedNormalizedMethod = dm.dice();
	
	for (; usedNormalizedMethod == DataNormalizeMethod::none
		|| usedNormalizedMethod == DataNormalizeMethod::shiftPositive;
		usedNormalizedMethod = dm.dice());

	std::cout << "RecordSet2...use normal method: " << DataNormalizeMethod::tostr(usedNormalizedMethod) << std::endl;

	normalize(usedNormalizedMethod);
	
	//normalize(DataNormalizeMethod::shiftPositive);
}

void RecordSet2::normalize(DataNormalizeMethod::Name n) {

	usedNormalizedMethod = n;

	switch (n) {

	case DataNormalizeMethod::zscore:
		normZscore();
		break;

	case DataNormalizeMethod::zeroOneScaling:
		normZeroOneScaling();
		break;

	case DataNormalizeMethod::dividStddev:
		normDividStddev();
		break;

	case DataNormalizeMethod::dividMinMaxRegion:
		normDividMinMaxRegion();
		break;

	case DataNormalizeMethod::shiftPositive:
		normShiftPositive();
		break;

	case DataNormalizeMethod::none:
		break;		//do nothing

	default:
		ASSERT_WITH_MSG(false, "RecordSet2::normalize..unknown normalization method" << n);
	}
	
	
}

void RecordSet2::normShiftPositive() {

	//variables recalcuated as (V - min of V)
	
	compMin();

	for (auto& i : (*this)) {
		i.normShiftPositive(min);
	}
}

void RecordSet2::normZscore() {
	
	//Z-score scaling: variables recalculated as (V - mean of V)/s,
	//where "s" is the standard deviation.
	//As a result, all variables in the data set have equal means (0) and
	//standard deviations (1) but different ranges.

	compMeanStddev();

	for (auto& i : (*this)) {
		i.normZscore(mean, stddev);		//i is Record2*
	}
}
void RecordSet2::normDividStddev() {

	//Dividing each value by the standard deviation.
	//This method produces a set of transformed variables with variances of 1,
	//but different means and ranges.
	compStddev();
	for (auto& i : (*this)) {
		i.normDividStddev(stddev);
	}
}
void RecordSet2::normZeroOneScaling() {
	//0 - 1 scaling
	//for each variable V: (V - min V) / (max V - min V)
	//variables to have differing means and standard deviations but equal ranges

	compMinMax();
	for (auto& i : (*this)) {
		i.normZeroOneScaling(min, max);
	}
}
void RecordSet2::normDividMinMaxRegion() {
	//Dividing each value by the range : recalculates each variable as V / (max V - min V).
	//In this case, the means, variances, and ranges of the variables are still different,
	//but at least the ranges are likely to be more similar.

	compMinMax();

	for (auto& i : (*this)) {
		i.normDividMinMaxRegion(min, max);
	}
}

//dump
void RecordSet2::dump(std::ostream& out) const {
	for (const auto& s : (*this)) {
		const Record2& r = s;
		r.dump(out);
		out << std::endl;
	}
}

std::ostream& operator<<(std::ostream& out, const RecordSet2& rs) {
	rs.dump(out);
	return out;
}
#include "stdafx.h"
#include "Record2.h"
#include <algorithm>

/////////////////////////////////////////////////////////////////////
//dump
void Record2::dump(std::ostream& out) const {
	for (const auto& d : (*this))
		out << d << " ";
}

void Record2::dumpIfNegative(std::ostream& out, const std::string& info) const {
	for (const auto& i : (*this)) {
		if (i < 0) {
			out << std::endl << info << ": " << std::endl;
			dump(out);

			std::cout << std::endl << "...Record2::dumpIfNegative...enter a char to continue: ";
			char c;
			std::cin >> c;
			
			return;
		}
	}
	
}


std::ostream& operator<<(std::ostream& out, const Record2& r) {
	r.dump(out);
	return out;
}

Record2::Record2(unsigned int size, double fillValue) : MyBase(size) {
	this->fill(fillValue);
}
Record2::Record2(const arma::vec& armaVec) : MyBase(armaVec) {}

Record2::Record2(const std::vector<double>& stdVec) : MyBase(stdVec) {}

Record2::Record2(unsigned int size) : MyBase(size, arma::fill::zeros) {}

Record2& Record2::operator=(const arma::vec& armaVec) {
    unsigned int sz = armaVec.size();
    this->resize(sz);
    unsigned int i;
    for(i=0; i<sz; ++i) {
        (*this)(i) = armaVec(i);
    }
    return *this;
}


///////////////////////////////////////////////////////////////////////////////
double Record2::innerProduct(const Record2& other) const {
	return arma::dot((arma::vec)(*this), (arma::vec)other);
}
void Record2::hadamardProd(const Record2& rhs) {
	(*this) %= rhs;
}

//distance
double Record2::sigmod() const {
	double n = arma::norm((arma::vec)*this, 2);
	n *= -1;
	return 1.0 / (1 + std::exp(n));
}

double Record2::squareDist(const Record2& other) const {
	MyBase diff = (MyBase)(*this) - (MyBase)other;
	return arma::dot(diff, diff);
}

void Record2::split(Record2& positive, Record2& negative) const {
   
    unsigned int size = this->size();
    positive.resize(size);
    negative.resize(size);
    unsigned int j=0;
    for(const auto& d: (*this)) {
    
        if (d>0) {
            positive(j) = d;
            negative(j) = 0;
        }
        else { // d<=0
            positive(j) = 0;
            negative(j) = d * -1;
        }
        ++j;
    }
    
}
unsigned int Record2::maxIntervalSplit() {
    Record2::iterator i = this->begin();
    Record2::iterator e = this->end();
    std::sort(i, e);

    double mint = 0, intv;
    unsigned int j, split;
    unsigned int sz = this->size();
    for(j = sz-1; j >= 1; --j) {
        intv = (*this)(j) - (*this)(j-1);
        if (intv > mint) {
            intv = mint;
            split = j;
        }
    }
    return sz - split;
}


///////////////////////////////////////////////////////////////////////////////
void Record2::normShiftPositive(const Record2& leftMin) {
	(*this) -= leftMin;
}

void Record2::normDividStddev(const Record2& stddev) {
	unsigned int i = 0;
	unsigned int sz = this->size();
	for (; i < sz; ++i) {
		(*this)[i] /= stddev[i];  //yjf.WARNING: denominator may be zero. 
	}
}
void Record2::normZscore(const Record2& mean, const Record2& stddev) {
	//Z-score scaling: variables recalculated as (V - mean of V)/s,
	//where "s" is the standard deviation.
	//As a result, all variables in the data set have equal means (0) and
	//standard deviations (1) but different ranges.

	unsigned int i = 0;
	unsigned int sz = this->size();
	for (; i < sz; ++i) {
		(*this)[i] -= mean[i];
		(*this)[i] /= stddev[i];			//yjf.WARNING: denominator may be zero.
	}
}

void Record2::normZeroOneScaling(const Record2& min, const Record2& max) {
	//0 - 1 scaling
	//for each variable V: (V - min V) / (max V - min V)
	unsigned int i = 0;
	unsigned int sz = this->size();
	for (; i < sz; ++i) {
		(*this)[i] -= min[i];
		(*this)[i] /= (max[i] - min[i]);		//yjf.WARNING: denominator may be zero.
	}
}
void Record2::normDividMinMaxRegion(const Record2& min, const Record2& max) {
	//for each variable V: V / (max V - min V)
	unsigned int i = 0;
	unsigned int sz = this->size();
	for (; i < sz; ++i) {
		(*this)[i] /= (max[i] - min[i]);		//yjf.WARNING: denominator may be zero.
	}
}

double Record2::mean() const {
	return arma::mean((arma::vec)(*this));
}
double Record2::stddev() const {
	return arma::stddev((arma::vec)(*this));
}



#pragma once

#include "stdafx.h"
#include "Record2.h"

#include <iostream>
#include <vector>
#include <string>
#include <armadillo>

class GAmatrix: public arma::mat
{
public:

	typedef arma::mat MyBase;
public:
	GAmatrix();
	GAmatrix(const MyBase& base);
	GAmatrix(unsigned int size);
	GAmatrix(unsigned int size1, unsigned int size2);
    ~GAmatrix();
    GAmatrix& operator=(const MyBase& base);
        
        double fnorm() const;
        double frobDistToEye() const;
        double avgRowInnerProd() const;
        unsigned int minNumNonZerosPerRow() const;
        
	void hadamardProd(const GAmatrix& other);
	void hadamardDivd(const GAmatrix& denominator);

	double maxProfitMatch(std::vector<long>& mappedColumns) const;

	unsigned int maxIntersectMatch() const;
	unsigned int maxIntersectMatch(std::vector<long>& mappedColumns) const;

    void assignByOutProd(const Record2& p);
    void assignByOutProd(const Record2& p, const Record2& q); //p * q^T
    void splitPosNeg(GAmatrix& pos, GAmatrix& neg) const;
    
	
	//dump
	void dump(std::ostream& out) const;
	void dumpIfNegative(std::ostream& out, const std::string& info) const;
};

std::ostream& operator<<(std::ostream& out, const GAmatrix& ga);



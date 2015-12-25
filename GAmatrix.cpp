#include "stdafx.h"
#include "GAmatrix.h"

#include <dlib/optimization/max_cost_assignment.h>

GAmatrix::GAmatrix() {
	//using arma::mat::resize to allocate memory for rows and cols later.
}

GAmatrix::GAmatrix(const MyBase& base) : MyBase(base) {}
GAmatrix::GAmatrix(unsigned int size) : GAmatrix(size, size) {}
GAmatrix::GAmatrix(unsigned int size1, unsigned int size2) : MyBase(size1, size2, arma::fill::zeros) { }
GAmatrix::~GAmatrix() {}
GAmatrix& GAmatrix::operator=(const MyBase& base) {
    unsigned int i_size = base.n_rows;
    unsigned int j_size = base.n_cols;
    this->resize(i_size, j_size);
    unsigned int i,j;
    for(i=0; i<i_size; ++i) {
        for(j=0; j<j_size; ++j)
            (*this)(i,j) = base(i,j);
    }
    return *this;
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////


unsigned int GAmatrix::maxIntersectMatch() const {

	std::vector<long> mappedColumns;
	return this->maxIntersectMatch(mappedColumns);
}

unsigned int  GAmatrix::maxIntersectMatch(std::vector<long>& mappedColumns) const {
	
	//transformed to integers, for dlib library can only operate
	//on integer input matrix
	unsigned int i = 0;
	unsigned int i_size = this->n_rows;
	unsigned int j;
	unsigned int j_size = this->n_cols;

	dlib::matrix<int> profit(i_size, j_size);
	for (; i < i_size; ++i) {
		for (j = 0; j < j_size; ++j) {
			profit(i, j) = (int)(*this)(i, j);
		}
	}

	//std::cout << "before max_cost assignemnt" << std::endl;

	// To find out the best assignment of people to jobs we just need to call this function.

	mappedColumns = dlib::max_cost_assignment(profit);

	//yjf.debug.
	//std::cout << "after max_cost assignment" << std::endl;

	unsigned int value = 0;
	for (i = 0; i < i_size; ++i) {
		value += (*this)(i, mappedColumns[i]);
	}

	return value;
}

double GAmatrix::maxProfitMatch(std::vector<long>& mappedColumns) const {

	//transformed to integers, for dlib library can only operate
	//on integer input matrix
	unsigned int i = 0;
	unsigned int i_size = this->n_rows;
	unsigned int j;
	unsigned int j_size = this->n_cols;
	
	dlib::matrix<int> profit(i_size, j_size);
	for (; i < i_size; ++i) {
		for (j = 0; j < j_size; ++j) {
			profit(i, j) = (int)((*this)(i, j) * 10000) + 1;
		}
	}
	
	//std::cout << "before max_cost assignemnt" << std::endl;

	// To find out the best assignment of people to jobs we just need to call this function.
	mappedColumns = dlib::max_cost_assignment(profit);
	
	//yjf.debug.
	//std::cout << "after max_cost assignment" << std::endl;

	double value = 0;
	for (i = 0; i < i_size; ++i) {
		value += (*this)(i, mappedColumns[i]);
	}

	return value;
}





////////////////////////////////////////////////////////////////////////////
void GAmatrix::splitPosNeg(GAmatrix& pos, GAmatrix& neg) const {

    unsigned int rows = this->n_rows;
    unsigned int cols = this->n_cols;
    pos.resize(rows, cols);
    neg.resize(rows, cols);    
    
    double tmp;
    unsigned int i,j;
    for(i=0; i<rows; ++i) {
        for(j=0; j<cols; ++j) {
    
            tmp = (*this)(i,j);
            if(tmp >=0 ) {
                pos(i,j) = tmp;
                neg(i,j) = 0;
            }
            else {
                pos(i,j) = 0;
                neg(i,j) = -1 * tmp;
            }
            
        }
    }//out for

}

 void GAmatrix::assignByOutProd(const Record2& p, const Record2& q) {
     // *this = p * q^T
     ASSERT_WITH_MSG(p.size() == q.size(), "GAmatrix::assignByOutProd..size unequal");

     unsigned int sz = p.size();
     this->resize(sz, sz);

     unsigned int i,j;
     for(i=0; i<sz; ++i) {
         for(j=0; j<sz; ++j)
             (*this)(i,j) = p(i)*q(j);
     }
 }

void GAmatrix::assignByOutProd(const Record2& p) {

    // *this = p * p^T
    unsigned int sz = p.size();
    this->resize(sz, sz);

    unsigned int i,j;
    for(i=0; i<sz; ++i) {
        for(j=0; j<sz; ++j)
            (*this)(i,j) = p(i)*p(j);
    }
}


double GAmatrix::frobDistToEye() const {

    // ||V_txm - I||_F

    unsigned int rows = this->n_rows;
    arma::mat VI = (arma::mat)(*this) * this->t() - arma::eye(rows,rows);

    return arma::norm(VI, "fro");

}
double GAmatrix::avgRowInnerProd() const {

    unsigned int rows = this->n_rows;
    arma::mat VI = (arma::mat)(*this) * this->t();
    
    double sip=0;
    unsigned int i,j,c;
    for(c=0, i=0; i<rows; ++i) {
        for(j=i+1; j<rows; ++j, ++c)
            sip += VI(i, j);        //inner products of different rows of V_txm
    }
    return sip/c;       //average
}
unsigned int GAmatrix::minNumNonZerosPerRow() const {
    unsigned int r;
    unsigned int i;  unsigned int i_size = this->n_rows;
    unsigned int j;  unsigned int j_size = this->n_cols;
    double ave = 0.5;
    unsigned int min = j_size;
    for(i=0; i<i_size; ++i) {
        r = 0;
        for(j=0; j<j_size; ++j) {
          if ((*this)(i,j) >= ave) ++r;
        }
        if (r < min) min = r;       //keep the min # non-zero elements of all rows 
    }
    return min;
}

double GAmatrix::fnorm() const {
    return arma::norm((arma::mat)(*this), "fro");
}

void GAmatrix::hadamardProd(const GAmatrix& other) {
	(*this) %= other;
}
void GAmatrix::hadamardDivd(const GAmatrix& denominator) {
	//(*this) /= denominator;

	unsigned int i = 0;
	unsigned int i_size = this->n_rows;
	unsigned int j;
	unsigned int j_size = this->n_cols;
	double r;
	for (; i < i_size; ++i) {
		for (j = 0; j < j_size; ++j) {
			r = (*this)(i, j) / denominator(i, j);
			if (r > Constant::nearPosInfi)
				(*this)(i, j) = Constant::nearPosInfi;		//set a upper bound
			else
				(*this)(i, j) = r;
		}
	}

}
////////////////////////////////////////////////////////////////////////
//dump
void GAmatrix::dump(std::ostream& out) const {
	this->print(out);
}
void GAmatrix::dumpIfNegative(std::ostream& out, const std::string& info) const {

	unsigned int i = 0;
	unsigned int i_size = this->n_rows;
	unsigned int j;
	unsigned int j_size = this->n_cols;
	int cout = 0;
	for (; i < i_size; ++i) {
		for (j = 0; j < j_size; ++j) {
			if ((*this)(i, j) < 0) {
				++cout;
				if (cout == 1) out << std::endl << info << std::endl;
				out << "(" << i << ", " << j << ")= " << (*this)(i, j) << " ";

				std::cout << std::endl << "...GAmatrix::dumpIfNegative..enter a char to continue: ";
				char c;
				std::cin >> c;
			}
		}
    }//for

}


std::ostream& operator<<(std::ostream& out, const GAmatrix& ga) {
	ga.dump(out);
	return out;
}

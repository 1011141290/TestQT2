#include "stdafx.h"
#include "TestMatrix.h"

#include "Record2.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iostream>

#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include "GAmatrix.h"

namespace las = boost::numeric::ublas;

using namespace arma;

TestMatrix::TestMatrix()
{
}


TestMatrix::~TestMatrix()
{
}

void TestMatrix::testGAmatrixProd() {
	GAmatrix m(3, 3);
	m << 1 << 2.1 << 3 << endr
		<< 4 << 8 << 11.3 << endr
		<< 1.2 << 0 << 8 << endr;

	m.print("before prod:");

	GAmatrix n(3, 3);
	n << 9.2 << 1.1 << 3 << endr
		<< 4 << 8 << 13.3 << endr
		<< 1.5 << 0 << 8 << endr;

	n.print("factor:");

	GAmatrix r;
        r = (arma::mat)m * (arma::mat)n;

	r.print("result:");

}

void TestMatrix::testGAmatrixHadamardDiv() {
	GAmatrix m(3, 3);
	m << 1 << 2.1 << 3 << endr
		<< 4 << 8 << 11.3 << endr
		<< 1.2 << 0 << 8 << endr;

	m.print("before hadamard divid:");

	GAmatrix n(3, 3);
	n << 9.2 << 1.1 << 3 << endr
		<< 4 << 8 << 13.3 << endr
		<< 1.5 << 0 << 8 << endr;

	n.print("factor:");

	GAmatrix r(m);

	m.hadamardDivd(n);

	m.print("after hardmard divid:");

	r.print("copy of m:");

}
void TestMatrix::testGAmatrixHadamard() {

	GAmatrix m(3, 3);
	m << 1 << 2.1 << 3 << endr
		<< 4 << 8 << 11.3 << endr
		<< 1.2 << 0 << 8 << endr;

	m.print("before hadamard product:");

	GAmatrix n(3, 3);
	n << 9.2 << 1.1 << 3 << endr
		<< 4 << 8 << 13.3 << endr
		<< 1.5 << 0 << 8 << endr;

	n.print("factor:");

	GAmatrix r(m);

	m.hadamardProd(n);

	m.print("after hardmard product:");


}


void TestMatrix::testGAmatrixNormal() {

	arma::mat m(3, 3);
	unsigned int i = 0;
	unsigned int size1 = m.n_rows;
	unsigned int size2 = m.n_cols;
	for (; i < size1; ++i) {
		unsigned int j = 0;
		for (; j < size2; ++j) {
			m(i, j) = i + j;
		}
	}

	m.print("before norm:");
	
	i = 0;
	unsigned int sz = m.n_rows;
	for (; i < sz; ++i) {
		arma::rowvec rw = m.row(i);
		double length = arma::norm(rw, 2);
		std::cout << i << ": len" << length << std::endl;
		m.row(i) /= length;
	}

	m.print("after normal:");
}

void TestMatrix::testGAmatrix() {

	arma::mat m(3, 3);
	unsigned int i = 0;
	unsigned int size1 = m.n_rows;
	unsigned int size2 = m.n_cols;
	for (; i < size1; ++i) {
		unsigned int j = 0;
		for (; j < size2; ++j) {
			m(i, j) = i + j;
		}
	}

	std::cout << m << std::endl;

	GAmatrix g(m);

	std::cout << "............................" << std::endl;
	std::cout << g << std::endl;

}

void TestMatrix::testHadamardProd() {

	las::matrix<double> m(3, 3);
	las::matrix<double> n(3, 3);

	unsigned int i = 0;
	unsigned int size1 = m.size1();
	unsigned int size2 = m.size2();
	for (; i < size1; ++i) {
		unsigned int j = 0;
		for (; j < size2; ++j) {
			m(i, j) = i + j;
			n(i, j) = i * j;
		}
			

	}

	std::cout << m << std::endl;
	std::cout << n << std::endl;

	las::matrix<double>::array_type& a = m.data();
	las::matrix<double>::array_type& b = n.data();
	unsigned int sz = a.size();
	for (i=0; i < sz; ++i) {
		a[i] *= b[i];
	}

	std::cout << ".............................." << std::endl;
	std::cout << m << std::endl;
	std::cout << n << std::endl;

}

void TestMatrix::testMatrixVectorProd() {

	GAmatrix m(3, 3);

	unsigned int i = 0;
	unsigned int size1 = m.n_rows;
	unsigned int size2 = m.n_cols;
	for (; i < size1; ++i) {
		unsigned int j = 0;
		for (; j < size2; ++j)
			m(i, j) = i + j;
	}

	std::cout << m << std::endl;

	//las::vector<double> v(3);
	Record2 v(3);
	for (i = 0; i < 3; ++i)
		v(i) = i + 1;

	std::cout << v << std::endl;

	Record2 result;
        result = (arma::mat) m * (arma::vec)v;

	std::cout << result << std::endl;


}


void TestMatrix::testMatrixRowProxyIP() {
	//las::matrix<double> m(3, 3);

	//unsigned int i = 0;
	//unsigned int size1 = m.size1();
	//unsigned int size2 = m.size2();
	//for (; i < size1; ++i) {
	//	unsigned int j = 0;
	//	for (; j < size2; ++j)
	//		m(i, j) = i + j;
	//}

	//std::cout << m << std::endl;

	//for (i = 0; i < size1; ++i) {
	//	las::matrix_row<las::matrix<double> > mr(m, i);
	//	double length = las::norm_2(mr);
	//	mr *= (1 / length);
	//}

	//std::cout << m << std::endl;

}


void TestMatrix::testInitial() {

	GAmatrix m(2, 3);
	std::cout << m << std::endl;

}


void TestMatrix::testMatrixSimple() {

	int t = 2;
	int m = 3;
	using namespace boost::numeric::ublas;
	
	matrix<double>* pV = new matrix<double>(t, m);
	
	
	
	matrix<double>& Vref = *pV;  //matrix<double> V = *pV;

	//Vref = *(new matrix<double>(t, m));


	int i = 0;
	int j = 0;
	for (; i < t; ++i) {
		for (j = 0; j < m; ++j) {

			//pV->operator()(i, j) = i + j;


			//(*pV)(i, j) = i + j;

			Vref(i, j) = i + j;

		//	pV[i, j] = i + j;
		}

	}

	std::cout << (*pV) << std::endl;

	
}


void TestMatrix::testIdentity() {

	typedef las::identity_matrix<double>  IDoub;
	
	IDoub m(3);
	std::cout << m << std::endl;

	IDoub::const_iterator1 i = m.begin1();
	IDoub::const_iterator1 e = m.end1();
	for (; i != e; ++i) {

		IDoub::const_iterator2 ii = i.begin();
		IDoub::const_iterator2 ee = i.end();
		for (; ii != ee; ++ii)
			std::cout << *ii << ".";
		std::cout << std::endl;

	}

}

void TestMatrix::testMatrixRowProxy() {

	using namespace boost::numeric::ublas;
	matrix<double> m(3, 3);
	
	for (unsigned i = 0; i < m.size1(); ++i) {   // for each row of m(3,3)
		matrix_row<matrix<double> > mr(m, i);   //get the proxy to access the elements in the i-th row

		std::cout << "\n\n....before changing the " << i << "-th row:" << std::endl;
		std::cout << mr << std::endl;

		for (unsigned j = 0; j < mr.size(); ++j) //set the elements in the i-th row
			mr(j) = 3 * i + j;

		std::cout << "....after changing the " << i << "-th row:" << std::endl;
		std::cout << mr << std::endl;
	}

	std::cout << ".........................." << std::endl;
	std::cout << m << std::endl;

	matrix_row<matrix<double> > rm(m, 1);
	vector<double> vt(m.size2());
	int j = 0;
	int len = vt.size();
	for (; j < len; ++j) {
		vt(j) = 10 + j;
	}

	rm = vt;

	std::cout << m << std::endl;

	//get the 1-th row and put it into a vector
	vector<double> row2(m.size2());
	row2 = row(m, 2);					//rm;  //matrix_row<matrix<double> > also ok.
	std::cout << row2 << std::endl;

	//vector<double> vect(m.size1());
	column(m, 1);
	std::cout << "column 1-th: " << column(m,1) << std::endl;

}

void TestMatrix::testMatrixRange()
{
	using namespace boost::numeric::ublas;
	matrix<double> m(4, 4);
	for (unsigned i = 0; i < m.size1(); ++i)
	for (unsigned j = 0; j < m.size2(); ++j)
		m(i, j) = 3 * i + j;

	std::cout << m << std::endl;

	matrix_vector_range<matrix<double> > mvr(m, range(0, 3), range(0, 3));
	std::cout << mvr << std::endl;
	
	std::cout << "..................." << std::endl;

	//WARNING: size of first range must be equal to size of second range,
	//and they both must be in the range of the row index and column index.

	//matrix_vector_range<matrix<double> > mvr2(m, range(0, 3), range(3,6));
	//std::cout << mvr2 << std::endl;

	

	//slice(start, step_len, how_many):
	matrix_vector_slice<matrix<double> > mvs(m, slice(0, 1, 3), slice(3, 0, 3));
	std::cout << mvs << std::endl;


}


void TestMatrix::testProject() {

	using namespace boost::numeric::ublas;
	matrix<double> m(3, 3);

	for (unsigned i = 0; i < m.size1(); ++i)
	for (unsigned j = 0; j < m.size2(); ++j)
		m(i, j) = 1;
	
	std::cout << m << std::endl;

	std::cout << "......................" << std::endl;

	std::cout << project(m, slice(0, 1, 2), slice(0, 1, 2)) << std::endl;

	for (unsigned i = 0; i < m.size1(); ++i)
	for (unsigned j = 0; j < m.size2(); ++j)
		project(m, slice(0, 1, 3), slice(0, 1, 3)) (i, j) = 3 * i + j;

	std::cout << project(m, slice(0, 1, 3), slice(0, 1, 3)) << std::endl;

}
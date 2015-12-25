#include "stdafx.h"
#include "ArmaTester.h"

#include <iostream>
#include <armadillo>

#include "Record2.h"

using namespace std;
using namespace arma;

ArmaTester::ArmaTester()
{
}


ArmaTester::~ArmaTester()
{
}

void ArmaTester::testVecClear() {

	Record2 r;

	r.resize(20);
	r.print("r:");
	
	r(13) = 12;

	r.resize(15);
	r.print("r: set&resize:");

	r.fill(arma::fill::zeros);
	r.print("r: fill 0s:");

	r.reset();
	r.print("r: set&resize,reset:");

	r.clear();
	r.print("r: clear");

}

void ArmaTester::testRecord2Hadamard(){

	Record2 r(10);
	r << 11 << 12 << 32 << 12 << 2 << 1 << 0 << 111 << 98 << 199;
	r.print("r:");

	Record2 t(10);
	t << 111 << 129 << 322 << 121 << 26 << 11 << 0 << 11 << 98 << 199;
	t.print("t:");

	r.hadamardProd(t);
	r.print("hadamardProd: ");

}

void ArmaTester::testRecord2MeanStddev() {

	Record2 r(10);
	r << 11 << 12 << 32 << 12 << 2 << 1 << 0 << 111 << 98 << 199;
	r.print("r:");

	std::cout << "mean: " << r.mean() << std::endl;
	cout << "stddev: " << r.stddev() << endl;

	Record2 mean(r.dim());
	Record2 stddev(r.dim());
	for (auto& i : mean) {
		i = r.mean();
	}
	for (auto& j : stddev) {
		j = r.stddev();
	}
	
	r.normZscore(mean, stddev);
	r.print("r.zscore:");

}

void ArmaTester::testRecord2() {

	Record2 r(3);
	r << 1 << 2 << 3;
	r.print("r:");

	Record2 s(3);
	s << 3 << 1 << 2;
	s.print("s:");

	std::cout << r.squareDist(s) << endl;

	
}

void ArmaTester::testMatrixHadamard() {

	mat m(2, 3, fill::zeros);
	m << 1 << 2 << 3 << endr
		<< 4 << 5 << 6 << endr
		<< 3 << 2 << 1 << endr;

	mat n(2, 3, fill::zeros);
	n << 2 << 1 << 4 << endr
		<< 4 << 2 << 2 << endr
		<< 4 << 2 << 1 << endr;

	m.print("m:");
	n.print("n:");

	mat mCpy(m);

	m %= n;
	m.print("m %= n:");

	mCpy /= n;
	mCpy.print("mCpy /= n:");

}

void ArmaTester::testMatrix() {

	mat m(2, 3, fill::zeros);
	m << 1 << 2 << 3 << endr
		<< 4 << 5 << 6 << endr
		<< 3 << 2 << 1 << endr;
	
	m.print("m:");

	vec a(3);
	a << 1 << 2 << 3;

	a.size();

	a.print("a:");

	vec d = m * a;

	d.print("d:");

	mat n(3, 2);

	n << 2 << 4 << endr
		<< 3 << 1 << endr
		<< 7 << 9 << endr;
	n.print("n:");

	mat r = m * n;			//matrix product
	r.print("r:");

	mat hada = m % m;
	hada.print("hada:");		//hadamard product

	mat haddiv = m / m;
	haddiv.print("hadadiv");

	//diag matrix
	mat diag = diagmat(a);
	diag.print("diag:");

	vec f(a);
	a.print("a:");
	a %= a;

	a.print("vector hadamard: ");

	f.print("f:");
	f /= f;
	f.print("vector hadamard div:");


}

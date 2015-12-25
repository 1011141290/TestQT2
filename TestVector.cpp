#include "stdafx.h"

#include <iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <algorithm>
#include <iostream>
#include <time.h>
#include <queue>

#include <numeric>
#include <functional>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

namespace acum = boost::accumulators;
namespace blas = boost::numeric::ublas;

#include "TestVector.h"

#include "Cluster.h"


#include <iostream>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

#include <list>

#include "RandomDice.h"

#include "RecordSet2.h"


#include <string>

#include <boost/unordered_set.hpp>

namespace bun = boost::unordered;

//#include <hash_set>

TestVector::TestVector() {

	std::list<int> ls;
	ls.push_back(1);
}


TestVector::~TestVector() {

}


class TestNode {
public:
	
	int _id;
	std::string _name;


	TestNode() {
		std::cout << ".ctor" << std::endl;
	}
	~TestNode() {
		std::cout << "---dtor" << std::endl;
	}

	TestNode(int id, const std::string& name):_id(id), _name(name) {
		
	}

	operator unsigned int() const {
		
		unsigned int sum = _id;
		for (const auto& i : _name) {
			sum += sum * 5 + (int(i));
		}

		return sum;
	}


};

std::ostream& operator<<(std::ostream& out, const TestNode& tn) {
	out << "(" << tn._id << ", " << tn._name;
	return out;
}

bool operator<(const TestNode& a, const TestNode& b) {
	std::cout << "...<" << std::endl;
	return a._id < b._id;
}



void TestVector::testHashset() {

	//bun::unordered_set<TestNode> hash;
//	std::hash_set<TestNode> hash;
//
//	hash.insert(TestNode(1, "abc"));
//	hash.insert(TestNode(2, "efg"));
//
//	for (const auto& i : hash) {
//		std::cout << i << std::endl;
//	}


}


void TestVector::testHadaProd() {

	unsigned int size = 3;
	Record2 r(size);

	for (auto& i : r) {
		i = rand() % 10;
	}

	r.print("before hadaProd:");

	r.hadamardProd(r);

	r.print("after hadaProd:");


}


void TestVector::testVectorClear() {

	std::vector<int> vt;
	vt.reserve(5);
	//vt.resize(5);

	vt.push_back(1);
	vt.push_back(2);
	vt.push_back(3);

	std::cout << "before clear" << std::endl;
	std::cout << vt.size() << std::endl;
	std::cout << "cap: " << vt.capacity() << std::endl;

	std::cout << "after clear" << std::endl;
	vt.clear();
	std::cout << vt.size() << std::endl;
	std::cout << "cap: " << vt.capacity() << std::endl;


	std::cout << "after push two" << std::endl;
	vt.push_back(100);
	vt.push_back(1111);
	std::cout << vt.size() << std::endl;
	std::cout << "cap: " << vt.capacity() << std::endl;

}




void TestVector::testPtrVector() {

	boost::ptr_vector<TestNode> pts;

	pts.push_back(new TestNode());
	pts.push_back(new TestNode());

	std::cout << "........start clear..........." << std::endl;
	pts.clear();

	std::cout << "ptr_vector.size: " << pts.size() << std::endl;
	std::cout << "ptr_vector.cap: " << pts.capacity() << std::endl;
}

void TestVector::testEnumRandom() {

	DataNormalizeMethod dn;

	std::cout << "enum size=" << DataNormalizeMethod::_SIZE << std::endl;

	int i = 0;
	int sz = 100;
	for (; i < sz; ++i) {
		if (i % 5 == 0) std::cout << std::endl;
		std::cout << dn.dice() << " ";
	}


}

void TestVector::testRecord2OutProd() {

	Record2 p(3);
	p << 1 << 2 << 3;

	GAmatrix PP;
        PP = (arma::vec)p * p.t();

	std::cout << PP << std::endl;

}

void TestVector::testRecordInit() {

	Record2 rd(10);

	rd.print("rd initi:");
	

}

void TestVector::testRecordEle() {

	unsigned int dim = 3;
	RecordSet2 rds;
	unsigned int i = 0;
	for (; i < 10; ++i) {
		Record2* r = new Record2(dim);
		for (unsigned int j = 0; j < dim; ++j) {
			(*r)[j] = std::rand() % 10;
		}
		rds.push_back(r);
	}
	std::cout << rds << std::endl;

	std::cout << ".................." << std::endl;
	for (const auto& i : rds) {
		std::cout << i << std::endl;
	}

	std::cout << "-----------------------" << std::endl;
	i = 0;
	unsigned int size = rds.size();
	for (; i < size; ++i) {
		std::cout << rds[i] << std::endl;
	}

	//rds.freeMemory();

}


void testStackFree() {

	std::vector<int> s;
	s.push_back(1);
	s.push_back(2);

	std::vector<int>::iterator i = s.begin();
	s.size();



    //int* first = &s[0];


	std::vector<int>* ps = new std::vector<int>();
	ps->push_back(3);
    ps->push_back(4);

    //int* seFirst = &((*ps)[0]);

	delete ps;
}


void TestVector::testVectorStackFree() {

	testStackFree();

	//can't take 
}


void TestVector::testRandom() {

	//typedef boost::mt19937 RNGType;
	//RNGType rng;
	//boost::uniform_int<> one_to_six(0, 6);
	//boost::variate_generator< RNGType, boost::uniform_int<> >
	//	dice(rng, one_to_six);

	DiceUniformInt dice(0, 6);

	for (int i = 0; i < 100; i++) {
        //int n = dice();
        int n = dice.next();

        if (i % 10 == 0)
			std::cout << std::endl;

		std::cout << " " << n;
	}

}

void TestVector::testRandom2() {
	
    /*
    typedef boost::mt19937 RNGType;
    RNGType rng;
    boost::normal_distribution<float> indexes(5, 1.5);
    boost::variate_generator< RNGType,
            boost::normal_distribution<float> >
        dice(rng, indexes); */


    //typedef boost::mt19937 RNGType;
    //RNGType rng;
    //boost::uniform_int<> one_to_six(0, 6);
    //boost::variate_generator< RNGType,
    //      boost::uniform_int<> >
    //	dice(rng, one_to_six);



    DiceNormalDouble dice(10, 1);

    //DiceUniformInt dice(0, 6);




	
	for (int i = 0; i < 100; i++) {
		double n = dice.next();
		if (i % 10 == 0)
			std::cout << std::endl;

		std::cout << " " << n;
	}



}


void TestVector::testInnProd() {

	Record2 a(3);
	Record2 b(3);
	int i = 0;
	for (; i < 3; ++i) {
		a[i] = i;
		b[i] = i + 3;
	}
	
	std::cout << a << std::endl;
	std::cout << b << std::endl;

	std::cout << a.innerProduct(b) << std::endl;
}

void TestVector::testPriorityQueue() {

	//typedef DistIndex<double> ET;
	////std::priority_queue<ET, std::vector<ET>, BiggerDist<double> > pq;
	//std::priority_queue<ET, std::vector<ET> > pq;

	//pq.push(ET(19.2, 1));
	//pq.push(ET(199.2, 2));
	//pq.push(ET(2.3, 3));
	//pq.push(ET(98.3, 4));
	//
	//while (!pq.empty()) {
	//	std::cout << pq.top() << std::endl;
	//	pq.pop();
	//}
	
}




struct TestData{
	int x;
	int y;
};

void TestVector::testStdVectorSize() {

	std::size_t size = 10;
	std::vector<TestData> d(size);
	std::cout << d.size();

}


void TestVector::testVarData2(const blas::vector<double>& record) {

	double sum = std::accumulate(record.begin(), record.end(), 0.0);
	double mean = sum / record.size();

	double sq_sum = blas::inner_prod(record, record);
	double stdev = std::sqrt(sq_sum / record.size() - mean * mean);

	std::cout << record << std::endl;
	std::cout << "mean: " << mean << std::endl;
	std::cout << "std variance: " << stdev << std::endl;

}
void TestVector::testVarData1(const blas::vector<double>& record) {

	typedef double value_type;

	acum::accumulator_set<value_type, acum::stats<acum::tag::variance> > acc;
	std::for_each(record.begin(), record.end(), std::bind<void>(std::ref(acc), std::placeholders::_1));

	value_type m = acum::mean(acc);
	value_type sdv = std::sqrt(acum::variance(acc));

	std::cout << record << std::endl;
	std::cout << "mean: " << m << std::endl;
	std::cout << "std variance: " << sdv << std::endl;

}

void TestVector::testVariance() {

	srand((unsigned int) time(NULL));

	blas::vector<double> record(100);
	for (unsigned i = 0; i < record.size(); ++i)
		record(i) = (std::rand() % 10) * 0.1;

	testVarData1(record);
	testVarData2(record);

}


void TestVector::testNorm() {

	using namespace boost::numeric::ublas;
	vector<double> v(3);
	for (unsigned i = 0; i < v.size(); ++i)
		v(i) = i;

	std::cout << sum(v) << std::endl;
	std::cout << norm_1(v) << std::endl;
	std::cout << norm_2(v) << std::endl;
	std::cout << norm_inf(v) << std::endl;
	std::cout << index_norm_inf(v) << std::endl;

}


void TestVector::testVectorOper() {

	using namespace boost::numeric::ublas;
	vector<std::complex<double>, std::vector<std::complex<double> > > v(3);
	for (unsigned i = 0; i < v.size(); ++i)
		v(i) = std::complex<double>(i, i);

	std::cout << v << std::endl;
	std::cout << conj(v) << std::endl;
	std::cout << real(v) << std::endl;
	std::cout << imag(v) << std::endl;
	std::cout << trans(v) << std::endl;
	std::cout << herm(v) << std::endl;

	std::cout << "testing outprod......" << std::endl;

	using namespace boost::numeric::ublas;
	vector<double> v1(3), v2(3);
	for (unsigned i = 0; i < std::min(v1.size(), v2.size()); ++i)
		v1(i) = v2(i) = i;

	std::cout << outer_prod(v1, v2) << std::endl;

}

struct TestStudent{
	int j;
};

struct TestName{
	int n;
	TestStudent* p[4];
};

void TestVector::testNameLayout() {

	TestName* p = new TestName();
	
	TestName& pf = *p;

    //TestName* pfaddr = &pf;


	TestName pValue = *p;
    pValue.n = 2;

	pf.n = 1;


}


void TestVector::testVectors() {

	using namespace boost::numeric::ublas;
	scalar_vector<double> v(3);
	
	std::cout << v(1) << std::endl;


	scalar_vector<double> t(3, 5);

	std::cout << v * 5 << std::endl;
	std::cout << "..." << t << std::endl;


	typedef TestName* intptr;
	intptr p = new TestName();
	p->n = 10;

	//Name a[10];

	for (int i = 0; i < 3; i++){
		
	}

}



void TestVector::testUnitVector() {

	using namespace boost::numeric::ublas;

	for (int i = 0; i < 3; ++i) {
		unit_vector<double> v(3, i);
		std::cout << v << std::endl;
	}

}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& v) {

	std::vector<int>::const_iterator i = v.begin();
	std::vector<int>::const_iterator e = v.end();
	for (; i != e; ++i) {

		out << *i << " ";

		// out << *i
		//(out.operator<<(*i)).operator<<(" ");

		//(out << *i) << " ";
	}
	return out;
}


void TestVector::testPermutation() {

	std::vector<int> v;
	int i = 0;
	for (; i < 6; ++i) {
		v.push_back(i);
	}

	std::cout << v << std::endl << "...................." << std::endl;

	int j = 0;
	while (std::next_permutation(v.begin(),
		v.end()
		)
		) {
		std::cout << ++j << " :" << v << std::endl;
	}

}

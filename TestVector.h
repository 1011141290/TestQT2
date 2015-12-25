#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace blas = boost::numeric::ublas;

class TestVector
{
public:
	TestVector();
	~TestVector();

	static void testUnitVector();
	static void testPermutation();

	static void testVectors();
	static void testVectorOper();


	static void testNorm();

	static void testNameLayout();

	static void testVariance();

	static void testVarData1(const blas::vector<double>& record);
	static void testVarData2(const blas::vector<double>& record);

	static void testStdVectorSize();

	static void testPriorityQueue();
	
	static void testInnProd();

	static void testRandom();
	static void testRandom2();

	static void testVectorStackFree();

	static void testRecordEle();
	static void testRecordInit();

	static void testRecord2OutProd();

	static void testEnumRandom();

	static void testPtrVector();

	static void testVectorClear();

	static void testHashset();

	static void testHadaProd();


};


#pragma once
class TestMatrix
{
public:
	TestMatrix();
	~TestMatrix();



	static void testIdentity();
	static void testMatrixRowProxy();
	static void testMatrixRange();
	static void testProject();
	static void testMatrixSimple();

	static void testInitial();

	static void testMatrixRowProxyIP();

	static void testMatrixVectorProd();
	static void testHadamardProd();

	static void testGAmatrix();

	static void testGAmatrixNormal();

	static void testGAmatrixHadamard();

	static void testGAmatrixHadamardDiv();

	static void testGAmatrixProd();

};


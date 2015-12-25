#include "stdafx.h"
#include "XDataTester.h"

#include "DataSet.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

XDataTester::XDataTester()
{
}


XDataTester::~XDataTester()
{
}

void XDataTester::testDataSet() {
	std::string fn = "e:/vsworkspace/TestingBoost/data/batch1.txt";

	std::ifstream in;
	in.open(fn.c_str(), std::ios::in);
	if (in.fail()) {
		std::cout << "XDataTester::testDataSet..failed to open " << fn << std::endl;
		return;
	}

	
	DataSet xd;
	xd.parse(fn, 0);

	std::string of("./testBatch1.txt");
	std::ofstream out;
	out.open(of.c_str(), std::ios::out);
	if (out.fail()) {
		std::cout << "XDataTester::testDataSet..failed to open " << of << std::endl;
		return;
	}

	const RecordSet2& ors = xd.getRecords();

	out << "------------------original data -----------------------" << std::endl;
	out << ors << std::endl;
	
	out << "=====================================" << std::endl;
	out.flush();

	//normZeroOneScaling
	RecordSet2 rs(ors);
	rs.normalize(DataNormalizeMethod::zeroOneScaling);
	out << "..................normZeroOneScaling..............." << std::endl;
	out << rs << std::endl;

	//normZscore
	RecordSet2 zs(ors);
	zs.normalize(DataNormalizeMethod::zscore);
	out << "------------------normZscore-----------------------" << std::endl;
	out << zs << std::endl;

	out << "------------------original data again-----------------------" << std::endl;
	out << ors << endl;

	out.flush();
	out.close();

	std::string of2("./testBatch1_2.txt");
	std::ofstream out2;
	out2.open(of2.c_str(), std::ios::out);
	if (out2.fail()) {
		std::cout << "XDataTester::testDataSet..failed to open " << of2 << std::endl;
		return;
	}
	out2 << xd << endl;
}

void XDataTester::testTOX171(){
    std::string fn = "E:/vsworkspace/TestQT2/data/TOX171.txt";

    std::ifstream in;
    in.open(fn.c_str(), std::ios::in);
    if (in.fail()) {
        std::cout << "XDataTester::testUMinst..failed to open " << fn << std::endl;
        return;
    }


    DataSet xd;
    xd.parse(fn, 0);

    std::string of("./testTOX171.txt");
    std::ofstream out;
    out.open(of.c_str(), std::ios::out);
    if (out.fail()) {
        std::cout << "XDataTester::testTOX171..failed to open " << of << std::endl;
        return;
    }

    const RecordSet2& ors = xd.getRecords();

    out << "------------------original data -----------------------" << std::endl;
    out << ors << std::endl;

    out << "=====================================" << std::endl;
    out.flush();

    //normZeroOneScaling
    RecordSet2 rs(ors);
    rs.normalize(DataNormalizeMethod::zeroOneScaling);
    out << "..................normZeroOneScaling..............." << std::endl;
    out << rs << std::endl;

    //normZscore
    RecordSet2 zs(ors);
    zs.normalize(DataNormalizeMethod::zscore);
    out << "------------------normZscore-----------------------" << std::endl;
    out << zs << std::endl;

    out << "------------------original data again-----------------------" << std::endl;
    out << ors << endl;

    out.flush();
    out.close();

    std::string of2("./testTOX171_2.txt");
    std::ofstream out2;
    out2.open(of2.c_str(), std::ios::out);
    if (out2.fail()) {
        std::cout << "XDataTester::testTOX171..failed to open " << of2 << std::endl;
        return;
    }
    out2 << xd << endl;

}



void XDataTester::testUMinst(){
    std::string fn = "E:/vsworkspace/TestQT2/data/uminst.txt";

    std::ifstream in;
    in.open(fn.c_str(), std::ios::in);
    if (in.fail()) {
        std::cout << "XDataTester::testUMinst..failed to open " << fn << std::endl;
        return;
    }


    DataSet xd;
    xd.parse(fn, 0);

    std::string of("./testuminst.txt");
    std::ofstream out;
    out.open(of.c_str(), std::ios::out);
    if (out.fail()) {
        std::cout << "XDataTester::testUMinst..failed to open " << of << std::endl;
        return;
    }

    const RecordSet2& ors = xd.getRecords();

    out << "------------------original data -----------------------" << std::endl;
    out << ors << std::endl;

    out << "=====================================" << std::endl;
    out.flush();

    //normZeroOneScaling
    RecordSet2 rs(ors);
    rs.normalize(DataNormalizeMethod::zeroOneScaling);
    out << "..................normZeroOneScaling..............." << std::endl;
    out << rs << std::endl;

    //normZscore
    RecordSet2 zs(ors);
    zs.normalize(DataNormalizeMethod::zscore);
    out << "------------------normZscore-----------------------" << std::endl;
    out << zs << std::endl;

    out << "------------------original data again-----------------------" << std::endl;
    out << ors << endl;

    out.flush();
    out.close();

    std::string of2("./testuminst_2.txt");
    std::ofstream out2;
    out2.open(of2.c_str(), std::ios::out);
    if (out2.fail()) {
        std::cout << "XDataTester::testUMinst..failed to open " << of2 << std::endl;
        return;
    }
    out2 << xd << endl;

}


void XDataTester::testSimple() {

	std::cout << "please enter the data set file name with full path:" << std::endl;
	std::string fn;
	std::cin >> fn;

	std::ifstream in;
	in.open(fn.c_str(),std::ios::in);
	if (in.fail()) {
		std::cout << "XDataTester::testSimple..failed to open " << fn << std::endl;
		return;
	}

	DataSet xd;
	xd.parse(fn, 0);

	std::string of("./XDout.txt");
	std::ofstream out;
	out.open(of.c_str(), std::ios::out);
	if (out.fail()) {
		std::cout << "XDataTester::testSimple..failed to open " << of << ", dump to cout instead" << std::endl;
		std::cout << xd;
		return;
	}
	out << xd;

	out.flush();
	out.close();
}

void XDataTester::testRecordSet() {

	std::string fn = "e:/vsworkspace/TestingBoost/data/wine.data.txt";

	std::ifstream in;
	in.open(fn.c_str(), std::ios::in);
	if (in.fail()) {
		std::cout << "XDataTester::testRecordSet..failed to open " << fn << std::endl;
		return;
	}

	//XData<float>* xd = new XData;

	DataSet xd;
	xd.parse(fn, 0);

	std::string of("./testRecordSet.txt");
	std::ofstream out;
	out.open(of.c_str(), std::ios::out);
	if (out.fail()) {
		std::cout << "XDataTester::testRecordSet..failed to open " << of << std::endl;
		return;
	}

	const RecordSet2& ors = xd.getRecords();

	out << ors << std::endl;
	out << "=====================================" << std::endl;
	out.flush();

	//normZeroOneScaling
	RecordSet2 rs(ors);
	rs.normalize(DataNormalizeMethod::zeroOneScaling);
	out << "..................normZeroOneScaling..............." << std::endl;
	out << rs << std::endl;

	//normZscore
	RecordSet2 zs(ors);
	zs.normalize(DataNormalizeMethod::zscore);
	out << "------------------normZscore-----------------------" << std::endl;
	out << zs << std::endl;


	out.flush();
	out.close();
}

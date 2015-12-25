#include "stdafx.h"
#include "RunnerTester.h"


RunnerTester::RunnerTester()
{
    dsDir = "../../data/";
	dsNames.push_back("wine.data.txt");
}


RunnerTester::~RunnerTester()
{
}

void RunnerTester::test_batch1_wine() {

	test_batch1();
	test_wine_dataset();

}

void RunnerTester::test_TOX171() {
    //total records: 575
    //clusters: 20
    //dimension: 10304

    std::string fn = "../../data/";
    fn += "TOX171.txt";

    RunnerConfig rc;
    rc.lambda_min = 0;
    rc.lambda_max = 0.00001;
    //rc.beta_min = 100000;
    //rc.beta_max = 100001;

    //1000: too small will not make enough orthongoality
    //i.e., orthIpIndex can't less than 0.01
    rc.beta_min = 10000000;
    rc.beta_max = 10000001;

    rc.preDefinedClusters = 4;
    rc.labelColumn = 0;
    rc.RunTimes = 10;

    rc.VupdMethod = VupdateMethod::m3_china;
    Runner run;
    run.prepareRun(fn, rc.labelColumn);

    unsigned int t = 2;
    unsigned int ts = 10;
    for (; t <= ts; ++t) {

        rc.t_min = t;
        rc.t_max = t;

        run.run(fn, rc);
    }
    run.printResults();


}


void RunnerTester::test_uminst() {
    //total records: 575
    //clusters: 20
    //dimension: 10304

    std::string fn = "./";
    fn += "uminst.txt";

    RunnerConfig rc;
    rc.lambda_min = 0;
    rc.lambda_max = 0.00001;
    //rc.beta_min = 100000;
    //rc.beta_max = 100001;

    //1000: too small will not make enough orthongoality
    //i.e., orthIpIndex can't less than 0.01
    rc.beta_min = 10000000;
    rc.beta_max = 10000001;

    rc.preDefinedClusters = 20;
    rc.labelColumn = 0;
    rc.RunTimes = 10;

    rc.VupdMethod = VupdateMethod::m3_china;

    Runner run;
    run.prepareRun(fn, rc.labelColumn);

    unsigned int t = 2;
    unsigned int ts = 10;
    for (; t <= ts; ++t) {

        rc.t_min = t;
        rc.t_max = t;


        run.run(fn, rc);

    }
    run.printResults();

}

void RunnerTester::test_batch1() {

    std::string fn = "../../data/";
    fn += "batch1.txt";

	RunnerConfig rc;
	rc.lambda_min = 0;
	rc.lambda_max = 0.00001;
    //rc.beta_min = 100000;
    //rc.beta_max = 100001;

    //1000: too small will not make enough orthongoality
    //i.e., orthIpIndex can't less than 0.01
    rc.beta_min = 10000000;
    rc.beta_max = 10000001;

    rc.preDefinedClusters = 6;
	rc.labelColumn = 0;
    rc.RunTimes = 10;

	rc.t_min = 2;
    rc.t_max = 10;		//number of groups equal to attributes of the dataset

    Runner run;
    run.prepareRun(fn, rc.labelColumn);

    unsigned int t = 2;
    unsigned int ts = 10;

    /*
    rc.VupdMethod = VupdateMethod::m3_china;
	for (; t <= ts; ++t) {

		rc.t_min = t;
		rc.t_max = t;

        run.run(rc);

	}

    run.printResults(); */


    /*
    rc.VupdMethod = VupdateMethod::m1_korea;
    t = 2;
    for (; t <= ts; ++t) {

        rc.t_min = t;
        rc.t_max = t;

        std::cout << ",,,,,,,, " << std::endl;
        run.run(rc);

    }
    run.printResults(); */


    rc.VupdMethod = VupdateMethod::m2_us;
    t = 2;
    for (; t <= ts; ++t) {

        rc.t_min = t;
        rc.t_max = t;

        run.run(rc);

    }
    run.printResults();



}

void RunnerTester::test_wine_dataset() {

    std::string fn = "../../data/";
    fn += "wine.data.txt";

	RunnerConfig rc;
	rc.lambda_min = 0.0001;
	rc.lambda_max = 0.0002;
	rc.beta_min = 300000;
	rc.beta_max = 300001;

	rc.preDefinedClusters = 3;
	rc.labelColumn = 0;
	rc.RunTimes = 30;

	rc.t_min = 6;
	rc.t_max = 6;		//number of groups equal to attributes of the dataset


    Runner run;
    run.prepareRun(fn, rc.labelColumn);

	unsigned int t = 2;
	unsigned int ts = 6;
	for (; t <= ts; ++t) {

		rc.t_min = t;
		rc.t_max = t;


		run.run(fn, rc);

	}

    run.printResults();

}

//#groups: 6, lambda : 1.04775, beta : 10.9551,
//objectVal : 0.769377,
//	2015 - Nov - 21 17 : 57 : 52.274867,
//p : 0.598182, r : 0.589751, F1 : 3.33333e+006, G : 0.580798, ac : 0.726592, NMI : 0.303932, CA : 0.589888,

	//RunnerConfig rc;
	//rc.lambda_min = 1;
	//rc.lambda_max = 1.5;
	//rc.beta_min = 10;
	//rc.beta_max = 20;

	//rc.preDefinedClusters = 3;
	//rc.labelColumn = 0;
	//rc.RunTimes = 30;

	//rc.t_min = 6;
	//rc.t_max = 6;		//number of groups equal to attributes of the dataset



//#groups: 6, lambda : 0.000197394, beta : 19.7394,
//objectVal : 0.45272,
//	2015 - Nov - 21 17 : 54 : 54.635648,
//p : 0.766603, r : 0.764144, F1 : 0.765346, G : 0.76536, ac : 0.820225, NMI : 0.573381, CA : 0.730337,

	//RunnerConfig rc;
	//rc.lambda_min = 0.0001;
	//rc.lambda_max = 0.0002;
	//rc.beta_min = 10;
	//rc.beta_max = 20;

	//rc.preDefinedClusters = 3;
	//rc.labelColumn = 0;
	//rc.RunTimes = 30;

	//rc.t_min = 6;
	//rc.t_max = 6;		//number of groups equal to attributes of the dataset




	//not good config, for lambda is to big.

//#groups: 6, lambda : 1.14366, beta : 300000,
//objectVal : 1.57021,
//2015 - Nov - 21 17 : 33 : 16.500739,
//p : 0.400589, r : 0.555821, F1 : 3.33333e+006, G : 0.471234, ac : 0.734082, NMI : 0.261104, CA : 0.601124,

	//RunnerConfig rc;
	//rc.lambda_min = 1;
	//rc.lambda_max = 1.5;
	//rc.beta_min = 300000;
	//rc.beta_max = 300001;

	//rc.preDefinedClusters = 3;
	//rc.labelColumn = 0;
	//rc.RunTimes = 30;

	//rc.t_min = 6;
	//rc.t_max = 6;		//number of groups equal to attributes of the dataset


	//good config, have gotten 
//#groups: 6, lambda : 0.000186054, beta : 300001,
//objectVal : 0.327845,
//	2015 - Nov - 21 17 : 24 : 58.023228,
//p : 0.93927, r : 0.946107, F1 : 0.940159, G : 0.941423, ac : 0.958801, NMI : 0.797205, CA : 0.938202,

	//but the result is not repeatable for the random initialized V matrix and w vector !

	//RunnerConfig rc;
	//rc.lambda_min = 0.0001;
	//rc.lambda_max = 0.0002;
	//rc.beta_min = 300000;
	//rc.beta_max = 300001;

	//rc.preDefinedClusters = 3;
	//rc.labelColumn = 0;
	//rc.RunTimes = 30;

	//rc.t_min = 6;
	//rc.t_max = 6;		//number of groups equal to attributes of the dataset


#include "stdafx.h"
#include "Runner.h"

#include "RandomDice.h"
#include <iostream>
#include <fstream>

#include "LogFile.h"

#include "AveResult.h"

Runner::Runner() : t_dice(0), lambda_dice(0), beta_dice(0), v_dice(0)
{ }

void Runner::resetDice() {
    if (t_dice != 0) {
        delete t_dice;
        t_dice = 0;
    }
    if (lambda_dice != 0) {
        delete lambda_dice;
        lambda_dice = 0;
    }
    if (beta_dice != 0) {
        delete beta_dice;
        beta_dice = 0;
    }
    if (v_dice != 0) {
        delete v_dice;
        v_dice = 0;
    }
}

Runner::~Runner() {

    resetDice();
}



void Runner::runOnce(const RecordSet2& rs) {


    //1) gather an initial result
    OnceRunResult* por = new OnceRunResult();
    por->startTime();

    cs.initial(runcfg.preDefinedClusters, t_dice->next(), ds.dim(),
        lambda_dice->next(), beta_dice->next(),
        &rs, (VupdateMethod::Name) v_dice->next());

    por->InitFinished();		//calculate the time needed for initialization
    cs.gatherInitResult(*por);

    unsigned int iterCount = 0;
    std::string info;

    for (; !cs.isConvergent() && iterCount < 100; ++iterCount) {

        cs.partitionData();			//partition all the data

       // std::cout << "\t\t cluError: " << cs.getClusteringError() << "\t.......# " << iterCount << std::endl;
       // std::cout << "\t\t maxip: " << cs.getMaxOrthIpIndex() << "\t.......# " << iterCount << std::endl;

        info.clear();
        double ca = cs.gatherEvalIndex(ds.getPreDefinedClusters(), info);
        if (ca > 0.5 ) {
            perf << "iterCount: " << iterCount << std::endl;
            perf << info << std::endl;
            perf.flush();
        }
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t iterCout: " << iterCount << std::endl;
        std::cout << info << std::endl;
    }

    //2) have gotten a stop result

    por->stopTime();
    por->IterativeCount = iterCount;

    cs.gatherStopResult(*por, ds.getPreDefinedClusters());
    results.push_back(por);
}

bool Runner::prepareRun(const std::string& dataSetPath, unsigned int labelColumn) {

    if (!ds.parse(dataSetPath, labelColumn))
        return false;

    //get dataset name for printing results;
    unsigned int index = dataSetPath.find_last_of("/");
    datasetName = dataSetPath.substr(index + 1, dataSetPath.size());
    perf.open(datasetName + "perf");     //open for recording performance


    /*
    this->runcfg = rcf;


    //initial dices for the random sequence of t_groupNum, lambda.
    t_dice = new DiceUniformInt(runcfg.t_min, runcfg.t_max);
    lambda_dice = new DiceUniformDouble(runcfg.lambda_min, runcfg.lambda_max);
    beta_dice = new DiceUniformDouble(runcfg.beta_min, runcfg.beta_max);

    //try only one V updating method
    v_dice = new DiceUniformInt(VupdateMethod::m3_china, VupdateMethod::m3_china);
    //v_dice = new DiceUniformInt(VupdateMethod::m1_korea, VupdateMethod::_SIZE - 1); */

    return true;

}

void Runner::run(const std::string& dataSetPath, const RunnerConfig& rcf){


    if (!prepareRun(dataSetPath, rcf.labelColumn))
        return;

    resetDice();

    this->runcfg = rcf;


    //initial dices for the random sequence of t_groupNum, lambda.
    t_dice = new DiceUniformInt(runcfg.t_min, runcfg.t_max);
    lambda_dice = new DiceUniformDouble(runcfg.lambda_min, runcfg.lambda_max);
    beta_dice = new DiceUniformDouble(runcfg.beta_min, runcfg.beta_max);

    //std::cout << "***** Runner: " << VupdateMethod::tostr(rcf.VupdMethod) << std::endl;

    v_dice = new DiceUniformInt(rcf.VupdMethod, rcf.VupdMethod);


    //
    //  main loop
    //
    unsigned int i = 0;
    for (; i < runcfg.RunTimes; ++i) {

        //clone a new copy of the original data,
        //to get a random normalized data.
        RecordSet2 rs(ds.getRecords());
        rs.normalizeRandom();

        runOnce(rs);


        //yjf.debug.
        std::cout << "..............finished: #" << i << std::endl;
        results[i].dumpSummaryInfo(std::cout);
        //std::cout << results[i].V_ks << std::endl;
        //std::cout << std::endl;
    }

    //printResults();
}

//run many times with different configure,
//such as different number of groups
void Runner::run(const RunnerConfig& rcf) {

    resetDice();


    this->runcfg = rcf;

    //initial dices for the random sequence of t_groupNum, lambda.
    t_dice = new DiceUniformInt(runcfg.t_min, runcfg.t_max);
    lambda_dice = new DiceUniformDouble(runcfg.lambda_min, runcfg.lambda_max);
    beta_dice = new DiceUniformDouble(runcfg.beta_min, runcfg.beta_max);

    //try only one V updating method
    //v_dice = new DiceUniformInt(VupdateMethod::m3_china, VupdateMethod::m3_china);
    //v_dice = new DiceUniformInt(VupdateMethod::m1_korea, VupdateMethod::_SIZE - 1);

    v_dice = new DiceUniformInt(rcf.VupdMethod, rcf.VupdMethod);

    //
    //  main loop
    //
    unsigned int i = 0;
    for (; i < runcfg.RunTimes; ++i) {

        //clone a new copy of the original data,
        //to get a random normalized data.
        RecordSet2 rs(ds.getRecords());
        rs.normalizeRandom();

        runOnce(rs);


        //yjf.debug.
        std::cout << "..............finished: #" << i << std::endl;
        results[i].dumpSummaryInfo(std::cout);
        //std::cout << results[i].V_ks << std::endl;
        //std::cout << std::endl;
    }

}


void Runner::printResults() {

    //yjf.WARNING: must let AveResult.printResults
    //run first, for it compute the average for
    //each kind of number of groups

    AveResult ar;
    ar.printResults(results, datasetName);


    LogFile outSum, outDet;
    outSum.open(datasetName +"_sum_");
    outDet.open(datasetName + "_detail_");
    
    //sort the results by each eval index
    //yjf.DELETE temp
    int i = EvalIndex::_SIZE -1;
    int sz = 0;
    for (; i >= sz; --i) {
        results.sort(SortByIndex(EvalIndex::Name(i)));
        for (const auto& r : results) {
            outSum << std::endl << std::endl << "=========================== " << EvalIndex::tostr(i) << "=========================" << std::endl;
            outDet << std::endl << std::endl << "=========================== " << EvalIndex::tostr(i) << "=========================" << std::endl;
            r.dumpSummaryInfo(outSum);
            r.dumpDetailInfo(outDet);
	}
    }//for

    outSum.flush();
    outSum.close();
    outDet.flush();
    outDet.close();

}

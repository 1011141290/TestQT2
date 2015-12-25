#pragma once

#include "DataSet.h"
#include "ClusterSet.h"
#include "OnceRunResult.h"
#include "RandomDice.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <string>
#include "LogFile.h"

struct RunnerConfig {
	unsigned int RunTimes;
	unsigned int preDefinedClusters;
	unsigned int labelColumn;			//starting from 0
	unsigned int t_min, t_max;
	double lambda_min, lambda_max;
	double beta_min, beta_max;

    VupdateMethod::Name VupdMethod;
};

class Runner
{
private:
	RunnerConfig runcfg;
	DiceUniformInt* t_dice;
	DiceUniformDouble* lambda_dice;
	DiceUniformDouble* beta_dice;
	DiceUniformInt* v_dice;

	std::string datasetName;
	DataSet ds;
	ClusterSet cs;

    boost::ptr_vector<OnceRunResult> results;

    void runOnce(const RecordSet2& rs);
        
    LogFile perf;
        
    void resetDice();

public:
	Runner();
	~Runner();

    bool prepareRun(const std::string& dataSetPath, unsigned int labelColumn);
    void run(const RunnerConfig& rcf);

	void run(const std::string& dataSetPath, const RunnerConfig& rcf);

    void printResults();
};


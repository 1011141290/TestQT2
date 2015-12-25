#pragma once

#include "ClusterMembershipSet.h"
#include "RecordSet2.h"
#include "GAmatrixSet.h"
#include "EvalIndex.h"

#include <armadillo>
#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

using namespace boost::posix_time;

class OnceRunResult
{
private:
	ptime time_start_AfterClusterInit;

public:

	//
	// summary info
	//
	ptime time_start;
	time_duration duration_clustersInit;
	time_duration duration_clustersIter;
	unsigned int IterativeCount;
	std::string dataNormalizeMethod;

    unsigned int numGroups;
	double lambda;	//chosen hyperparameter labmda
	double beta;
	double objectValue;		//
	std::string clusterInitialMethods;	//initial methods of all clusters

	//each row index represents a eval index from EvalIndex::Name {accuracy, F1_score,...}
	//first column is the average of the eval evalues computed on the similar match,
	//second column to xth column,
    //represent the assignment of indexes of h_ks to those of the ground truth
	GAmatrix matches;

	//
	//details
	//
	ClusterMembershipSet h_ks;	//each element is corresponding to each computed cluster
	RecordSet2 z_ks0;		//initial z_ks0
	RecordSet2 z_ks;		//the centers for clusters
	GAmatrixSet V_ks;		//the contributions of all attributes to the group variables Gs in this cluster
	GAmatrixSet V_ks0;		//initial V_ks
	RecordSet2 w_ks;		//the weight vector of group variables Gs
	RecordSet2 w_ks0;		//initial w_ks


	

public:
	
	void startTime();
	void InitFinished();
	void stopTime();

	//dump
	void dump(std::ostream& out) const;
	void dumpSummaryInfo(std::ostream& out) const;
	void dumpSummaryInfo(std::ostream& out, EvalIndex::Name n) const;
	void dumpDetailInfo(std::ostream& out) const;
};

std::ostream& operator<<(std::ostream& out, const OnceRunResult& orr);


struct SortByIndex {
private:
	unsigned int whichIndex;	//can be EvalIndex::Name= {accuracy, F1_score,...}
public:

	SortByIndex(EvalIndex::Name index);
	bool operator()(const OnceRunResult& a, const OnceRunResult& b) const;
};

struct SortByAverageIndex {
public:

	bool operator()(const OnceRunResult& a, const OnceRunResult& b) const;
};

struct SortByStartTime {
public:

	bool operator()(const OnceRunResult& a, const OnceRunResult& b) const;
};

struct SortByDuration {
public:
	bool operator()(const OnceRunResult& a, const OnceRunResult& b) const;
};

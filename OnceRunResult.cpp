#include "stdafx.h"
#include "OnceRunResult.h"
#include <algorithm>

void OnceRunResult::startTime() {
	time_start = ptime(microsec_clock::local_time());
}
void OnceRunResult::InitFinished() {
	time_start_AfterClusterInit = ptime(microsec_clock::local_time());
	duration_clustersInit = time_start_AfterClusterInit - time_start;
}
void OnceRunResult::stopTime() {
	 duration_clustersIter = ptime(microsec_clock::local_time()) - time_start_AfterClusterInit;
}


/////////////////////////////////////////////////////////////////////
//dump

void OnceRunResult::dump(std::ostream& out) const {
	dumpSummaryInfo(out);
	dumpDetailInfo(out);
}

void OnceRunResult::dumpSummaryInfo(std::ostream& out) const {
	
	//
	// summary info
	////
	
	//ptime time_start;

	//time_duration duration_clustersInit;
	//time_duration duration_clustersIter;
	//unsigned int IterativeCount;
	
	//t_groupNum

	//std::string dataNormalizeMethod;
	//std::string initialMethods;	//initial methods of all clusters
	
	//double lambda;	//chosen hyperparameter labmda
	//double objectValue;		//
	

	////each row index represents a eval index from EvalIndex::Name {accuracy, F1_score,...}
	////first column is the average of the eval evalues computed on the similar match,
	////second column to xth column, represent the assignment of indexes of h_ks to thoes of the truth 
	//arma::mat matches;

	//print time & duration
	//out << "--------------------------------------------------------------" << std::endl;
	//out << "time_start, t_gNum, AverEIs, lambda, ";
	//out << "dur_init, dur_iter, iterCT, ";
	//out << "datNM, " << "cluIM, ";
	//out << "objVal," << std::endl;

	out << "#groups: " << w_ks[0].dim() << ", ";
    out << "iterCount: " << IterativeCount << std::endl;
	out << "lambda: " << lambda << ", ";
	out << "beta: " << this->beta << ", " << std::endl;
	out << "objectVal: " << objectValue << ", " << std::endl;
	out << time_start << "," << std::endl << std::endl;

	//AverEIs
	unsigned int i = 0;
	unsigned int sz = EvalIndex::_SIZE;
	for (; i < sz; ++i) {
		out << EvalIndex::tostr(i) << ": " << matches(i, 0) << ", ";
	}
	//out << std::endl << std::endl << w_ks << std::endl;
	//out << std::endl << h_ks << std::endl;

    out << std::endl;

	//duration, iterative count
	out << duration_clustersInit << ", ";
	out << duration_clustersIter << ", ";

	//data norm method, cluster init method
	out << dataNormalizeMethod << ", ";
	out << clusterInitialMethods << ", ";


	out << std::endl;

}

void OnceRunResult::dumpSummaryInfo(std::ostream& out, EvalIndex::Name n) const {

	//
	// summary info
	////

	//ptime time_start;

	//time_duration duration_clustersInit;
	//time_duration duration_clustersIter;
	//unsigned int IterativeCount;

	//t_groupNum

	//std::string dataNormalizeMethod;
	//std::string initialMethods;	//initial methods of all clusters

	//double lambda;	//chosen hyperparameter labmda
	//double objectValue;		//


	////each row index represents a eval index from EvalIndex::Name {accuracy, F1_score,...}
	////first column is the average of the eval evalues computed on the similar match,
	////second column to xth column, represent the assignment of indexes of h_ks to thoes of the truth 
	//arma::mat matches;

	//print time & duration
	out << "time_start, t_gNum, AverEIs, lambda, ";
	out << "dur_init, dur_iter, iterCT, ";
	out << "datNM, " << "cluIM, ";
	out << "objVal," << std::endl;

	out << time_start << ",";
	out << w_ks[0].dim() << ", ";
	//AverEIs
	out << EvalIndex::tostr(n) << " " << matches(n, 0) << std::endl;
	out << h_ks << std::endl;

	//lambda
	out << lambda << ", ";
	//duration, iterative count
	out << duration_clustersInit << ", ";
	out << duration_clustersIter << ", ";
	out << IterativeCount << ", ";
	//data norm method, cluster init method
	out << dataNormalizeMethod << ", ";
	out << clusterInitialMethods << ", ";
	out << objectValue;

	out << std::endl;

}


void OnceRunResult::dumpDetailInfo(std::ostream& out) const {
	
	//Eval Indexes

	//ClusterMembershipSet h_ks;	//each element is corresponding to each computed cluster
	
	//RecordSet2 z_ks0;		//initial z_ks0
	//RecordSet2 z_ks;		//the centers for clusters
	
	//GAmatrixSet V_ks;		//the contributions of all attributes to the group variables Gs in this cluster
	//GAmatrixSet V_ks0;		//initial V_ks
	
	//RecordSet2 w_ks;		//the weight vector of group variables Gs
	//RecordSet2 w_ks0;		//initial w_ks

	//print eval indexes
	out << std::endl;

	unsigned int i = 0;
	unsigned int sz = EvalIndex::_SIZE;
	for (; i < sz; ++i) {
		out << EvalIndex::tostr(i) << "-" << matches(i, 0) << " :\t";
		for (unsigned int j = 1; j < matches.n_cols; ++j) {
			out << " " << matches(i, j);
		}
		out << std::endl;	//end of each row of eval index
	}

	
	//computed clusters
	out << h_ks << std::endl;
	
	//V_ks0, w_ks0, z_ks0
	unsigned int clusters = h_ks.size();
	out << "V0_1" << clusters << std::endl;
	out << V_ks0 << std::endl;
	out << "V_1:" << clusters << std::endl;
	out << V_ks << std::endl;


	out << "w0_1:" << clusters << std::endl;
	out << w_ks0 << std::endl;
	out << "w_1:" << clusters << std::endl;
	out << w_ks << std::endl;

	out << "z0_1:" << clusters << std::endl;
	out << z_ks0 << std::endl;
	out << "z_1:" << clusters << std::endl;
	out << z_ks << std::endl;

}
//////////////////////////////////////////////////////////////
SortByIndex::SortByIndex(EvalIndex::Name index): whichIndex(index){

}
bool SortByIndex::operator()(const OnceRunResult& a, const OnceRunResult& b) const {

	//bigger prefer
	return a.matches(whichIndex, 0) > b.matches(whichIndex, 0);
}

bool SortByAverageIndex::operator()(const OnceRunResult& a, const OnceRunResult& b) const {

	double av = 0;
	double bv = 0;
	unsigned int i = 0;
	unsigned int sz = a.matches.n_rows;
	for (; i < sz; ++i) {
		av += a.matches(i, 0);	//all values of eval indexes are stored in the 1st column 
		bv += b.matches(i, 0);
	}

	return av > bv;		//bigger perfer
}

bool SortByStartTime::operator()(const OnceRunResult& a, const OnceRunResult& b) const {
	return a.time_start < b.time_start;
}

bool SortByDuration::operator()(const OnceRunResult& a, const OnceRunResult& b) const {
	return a.duration_clustersInit + a.duration_clustersIter <
		   b.duration_clustersInit + b.duration_clustersIter;
}

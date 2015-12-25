#ifndef GROUPAVERRUNRESULT_H
#define GROUPAVERRUNRESULT_H


#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

using namespace boost::posix_time;

#include <string>
#include <ostream>

#include "EvalIndex.h"
#include "OnceRunResult.h"
#include <boost/ptr_container/ptr_vector.hpp>


struct GroupAveResult {

    time_duration aveDuration;
    double aveIterativeCount;
    int numGroups;

    double aveObjectValue;

    double aveEvalIndex[EvalIndex::_SIZE];

    void clear();
    void compAve(unsigned int count);
	
    void dumpBy(EvalIndex::Name n, std::ostream& out) const;
	
};
struct GARSortByIndex {
private:
    unsigned int whichIndex;	//can be EvalIndex::Name= {accuracy, F1_score,...}
public:

    GARSortByIndex(EvalIndex::Name index);
    bool operator()(const GroupAveResult& a, const GroupAveResult& b) const;
};

/////////////////////////////////////////////////////////////////////////////
class AveResult
{
private:

    void compAve();
    void sortByEvalIndex(EvalIndex::Name n);
    void compGroupAve(const boost::ptr_vector<OnceRunResult>& orrs);

public:
	
    boost::ptr_vector<GroupAveResult> results;

    //"t" means "total average"
    double tEvalIndex[EvalIndex::_SIZE];

    time_duration tDuration;
    double tIterativeCount;
    double tNumGroups;

    double tObjectValue;



	
public:
    AveResult();
    void printResults(const boost::ptr_vector<OnceRunResult>& orrs, const std::string& datasetName);
};

#endif // GROUPAVERRUNRESULT_H

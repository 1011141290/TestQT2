#include "AveResult.h"
#include "LogFile.h"

GARSortByIndex::GARSortByIndex(EvalIndex::Name index): whichIndex(index){

}
bool GARSortByIndex::operator()(const GroupAveResult& a, const GroupAveResult& b) const {

    //bigger prefer
    return a.aveEvalIndex[whichIndex] > b.aveEvalIndex[whichIndex];
}


void GroupAveResult::clear() {
    //aveDuration=0;
    aveIterativeCount=0;
    numGroups=-1;

    aveObjectValue=0;

    unsigned int i;
    for(i=0; i<EvalIndex::_SIZE; ++i) {
        aveEvalIndex[i] = 0;
    }

}

void GroupAveResult::compAve(unsigned int count) {
    aveDuration /=count;
    aveIterativeCount /= count;

    aveObjectValue /=count;

    unsigned int i;
    for(i=0; i<EvalIndex::_SIZE; ++i) {
        aveEvalIndex[i] /= count;
    }

}

void GroupAveResult::dumpBy(EvalIndex::Name n, std::ostream& out) const {
	
    out << EvalIndex::tostr(n) << ": " << aveEvalIndex[n] << "  #g: " << numGroups;
    out << "  ic: " << aveIterativeCount << "  ob: " << aveObjectValue << "  tm: " << aveDuration;
}


/////////////////////////////////////////////////////////////

AveResult::AveResult()
{
    unsigned int i;
    for(i=0; i< EvalIndex::_SIZE; ++i) {
        tEvalIndex[i] =0;
    }

    //tDuration=0;
    tIterativeCount=0;
    tNumGroups=0;

    tObjectValue=0;

}

void AveResult::compGroupAve(const boost::ptr_vector<OnceRunResult>& orrs) {

    if (orrs.size()==0) return;

    GroupAveResult arr;
    arr.clear();

    int count=0;

    for(const auto& i: orrs) {

        const OnceRunResult& j = i;

        if ((int) j.numGroups != arr.numGroups) {

            if (count !=0 ) { //previous #numGroups finished
                arr.compAve(count);
                results.push_back(new GroupAveResult(arr));
            }

            //new group's coming
            arr.numGroups = j.numGroups;
            count=1;

            unsigned int i;
            for(i=0; i<EvalIndex::_SIZE; ++i) {
                arr.aveEvalIndex[i] = j.matches(i,0);
            }

            //yjf.WARNING: to omit fault object value.
            if (j.objectValue > Constant::nearPosInfi)
                arr.aveObjectValue = 0;
            else
                arr.aveObjectValue = j.objectValue;

            arr.aveIterativeCount = j.IterativeCount;

            arr.aveDuration = j.duration_clustersInit + j.duration_clustersIter;
        }
        else {
            //old #numGroups
            ++count;
            unsigned int i;
            for(i=0; i<EvalIndex::_SIZE; ++i) {
                arr.aveEvalIndex[i] += j.matches(i,0);
            }

            arr.aveObjectValue += j.objectValue;
            arr.aveIterativeCount += j.IterativeCount;

            arr.aveDuration += j.duration_clustersInit + j.duration_clustersIter;

        }
    }

    //compute the last #numGroups
    if (count !=0) {
        arr.compAve(count);
        results.push_back(new GroupAveResult(arr));
    }

}

void AveResult::compAve() {

	unsigned int k = 0;
    for(const auto& r: results) {

        const GroupAveResult& j = r;

        unsigned int i;
        for(i=0; i< EvalIndex::_SIZE; ++i) {
            tEvalIndex[i] += j.aveEvalIndex[i];
        }

		if (k++ ==0 ) tDuration = j.aveDuration;
		else tDuration += j.aveDuration;
        tIterativeCount += j.aveIterativeCount;
        tNumGroups += j.numGroups;

        tObjectValue += j.aveObjectValue;

    }

    unsigned int count = results.size();

    unsigned int i;
    for(i=0; i< EvalIndex::_SIZE; ++i) {
        tEvalIndex[i] /= count;
    }

    tDuration /= count;
    tIterativeCount /= count;
    tNumGroups /= count;

    tObjectValue /= count;

}

void AveResult::sortByEvalIndex(EvalIndex::Name n) {
    results.sort(GARSortByIndex(n));
}

void AveResult::printResults(const boost::ptr_vector<OnceRunResult>& orrs,
                             const std::string& datasetName) {

	//
	//
	//compute average info by group.
	compGroupAve(orrs);
	//compute total average
    compAve();
	
	//
	// print
	//
    LogFile outSum;
    outSum.open(datasetName +"_aveResult_");

	//total average
	outSum << "NumGroups: " << tNumGroups << std::endl;
	outSum << "ObjectValue: " << tObjectValue << std::endl;
    int i = EvalIndex::_SIZE -1;
    int sz = 0;
    for (; i >= sz; --i) {
        outSum << EvalIndex::tostr(i) << ": " << tEvalIndex[i];
	}
	outSum << std::endl;
	outSum << "Duration: " << tDuration << std::endl;
	outSum << "IterativeCount: " << tIterativeCount << std::endl;
	
	outSum.flush();
    outSum.close();
    
	//group average detail
	i = EvalIndex::_SIZE -1;
    sz = 0;
    for (; i >= sz; --i) {
        LogFile ei;
        ei.open(datasetName + "_" + EvalIndex::tostr(i) + "_");
        results.sort(GARSortByIndex(( EvalIndex::Name) i));
        for(const auto j: results) {
            j.dumpBy(( EvalIndex::Name) i, ei);
			ei << std::endl;
		}
		ei.flush();
		ei.close();
	}
}



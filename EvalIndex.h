#pragma once

#include <string>

struct EvalIndex {
	//yjf.CAUTION. must not modify the order of following,
	//because we use them as the indexes to eval matrix.
	enum Name { 
		precision=0,
		recall,
		F1_score,
		G_measure,
		accuracy,
		NMI,
		CA,
	/*new index add just before here*/
	_SIZE };
	static std::string tostr(int evalIndex);
};

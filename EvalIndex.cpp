#include "stdafx.h"
#include "EvalIndex.h"

std::string EvalIndex::tostr(int evalIndex) {

	switch (evalIndex)
	{
	case EvalIndex::G_measure:
		return "G";

	case EvalIndex::accuracy:
		return "ac";

	case EvalIndex::F1_score:
		return "F1";

	case EvalIndex::NMI:
		return "NMI";

	case EvalIndex::precision:
		return "p";

	case EvalIndex::recall:
		return "r";

	case EvalIndex::CA:
		return "CA";

	}
	
	return "unknown";

}
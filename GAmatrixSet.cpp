#include "stdafx.h"
#include "GAmatrixSet.h"


std::ostream& operator<<(std::ostream& out, const GAmatrixSet& gs) {
	gs.dump(out);
	return out;
}

void GAmatrixSet::dump(std::ostream& out) const {
	for (const auto& i : (*this)) {
		i.dump(out);
		out << std::endl;
	}
}
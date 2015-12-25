#pragma once


#include "GAmatrix.h"
#include <iostream>
#include <boost/ptr_container/ptr_vector.hpp>

class GAmatrixSet: public boost::ptr_vector<GAmatrix> {

public:

	//dump
	void dump(std::ostream& out) const;
};

std::ostream& operator<<(std::ostream& out, const GAmatrixSet& gs);

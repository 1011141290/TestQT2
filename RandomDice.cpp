#include "stdafx.h"
#include "RandomDice.h"
#include <time.h>

Dist::UniformInt Dist::ui(int min, int max) {
	return Dist::UniformInt(min, max);
}
Dist::UniformDouble Dist::ud(double min, double max) {
	return Dist::UniformDouble(min, max);
}
Dist::NormalDouble Dist::nd(double mean, double stddev) {
	return Dist::NormalDouble(mean, stddev);
}
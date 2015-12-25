#pragma once

#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"



struct Dist {
	typedef boost::uniform_int<> UniformInt;
	typedef boost::normal_distribution<double> NormalDouble;
	typedef boost::uniform_real<double> UniformDouble;

	static UniformInt ui(int min, int max);
	static UniformDouble ud(double min, double max);
	static NormalDouble nd(double mean, double stddev);
};

template<class D>
class RandomDice
{
public:

	typedef boost::mt19937 RNGType;
	typedef boost::variate_generator<RNGType, D> GenType;
	typedef typename D::result_type result_type;

	GenType gen;
	
public:
	RandomDice(D dist) : gen(RNGType((unsigned int)time(0)), dist){
	}
	result_type next() {
		return gen();
	}
};

class DiceNormalDouble : public RandomDice<Dist::NormalDouble> {
public:
	DiceNormalDouble(double mean, double stddev): RandomDice(Dist::nd(mean, stddev)) {};
};

class DiceUniformDouble : public RandomDice<Dist::UniformDouble> {
public:
	DiceUniformDouble(double min, double max): RandomDice(Dist::ud(min, max)) {};
};

class DiceUniformInt : public RandomDice<Dist::UniformInt> {
public:
	DiceUniformInt(int min, int max): RandomDice(Dist::ui(min, max)) {};
};

#pragma once

#include "Runner.h"

#include <vector>
#include <string>

class RunnerTester
{
private:
	std::string dsDir;
	std::vector<std::string> dsNames;

public:
	RunnerTester();
	~RunnerTester();

	static void test_wine_dataset();
	static void test_batch1();

	static void test_batch1_wine();
    static void test_uminst();
    static void test_TOX171();

};


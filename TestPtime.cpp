#include "stdafx.h"
#include "TestPtime.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include <boost/thread/thread.hpp> 
#include <vector>
#include <algorithm>

using namespace boost::posix_time;
using namespace std;

TestPtime::TestPtime()
{
}


TestPtime::~TestPtime()
{
}

void TestPtime::testSortDuration() {

	std::vector<time_duration> ts(10);
	unsigned int i = 0;
	for (; i < 10; ++i) {
		ptime start(microsec_clock::local_time());
		boost::this_thread::sleep(boost::posix_time::seconds(2));
		ts[rand() % 10] = ptime(microsec_clock::local_time()) - start;

	}

	cout << "-------------before sort" << endl;
	unsigned int c = 0;
	for (auto& k : ts) {
		cout << k << endl;
		++c;
		if (c % 10 == 0)
			cout << endl;

	}

	//... execution goes here ...

	//ptime time_end(microsec_clock::local_time());
	//time_duration duration(time_end - time_start);

	sort(ts.begin(), ts.end());

	cout << "after sort----------------" << endl;
	c = 0;
	for (const auto& j : ts) {
		cout << j << ", ";
		if (++c % 10 == 0)
			cout << endl;
	}

	//cout << duration << '\n';

}

void TestPtime::testSort() {

	std::vector<ptime> ts(10);
	unsigned int i = 0;
	for (; i < 10; ++i) {
		boost::this_thread::sleep(boost::posix_time::seconds(2));
		ts[rand() % 10] = ptime(microsec_clock::local_time());

	}

	cout << "-------------before sort" << endl;
	unsigned int c = 0;
	for (auto& k : ts) {
		cout << k << endl;
		++c;
		if (c%10 == 0)
			cout << endl;

	}

	//... execution goes here ...

	//ptime time_end(microsec_clock::local_time());
	//time_duration duration(time_end - time_start);
	
	sort(ts.begin(), ts.end());

	cout << "after sort----------------" << endl;
	c = 0;
	for (const auto& j : ts) {
		cout << j << ", ";
		if (++c % 10 == 0)
			cout << endl;
	}
	
	//cout << duration << '\n';

}

void TestPtime::testDuration() {

	ptime time_start(microsec_clock::local_time());
	//... execution goes here ...

	boost::this_thread::sleep(boost::posix_time::seconds(70));


	ptime time_end(microsec_clock::local_time());
	time_duration duration(time_end - time_start);
	cout << duration << '\n';
	//output like: 00:01:10.005

}

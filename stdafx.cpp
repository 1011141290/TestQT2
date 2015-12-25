// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// TestingBoost.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"
#include <sstream>

double Constant::objectValueSmallest = 0.001;
double Constant::nearZero = 0.0001;
double Constant::nearPosInfi = 100000000;
double Constant::orthIndexSmallest = 0.01;
double Constant::sparseIndexSmallest = 0.80;
unsigned int Constant::cluMembQueueLen = 3;

//TODO.

void setLB(double& x, double lb /*= Constant::nearZero*/) {
	if (x < lb)
		x = lb;
}
void setUB(double& x, double ub /*= Constant::nearPosInfi*/) {
	if (x > ub)
		x = ub;
}
void iAppendString(double i, std::string& str) {
    std::stringstream ss;
    ss << i;
    std::string tmp = ss.str();
    
    unsigned int p = tmp.find_first_of(".");
    if (p == std::string::npos ) {
        str += tmp;
        return;
    }
    int n = tmp.size() - (p + 1);
    if (n <= 0 ) {
        str += tmp;
        return;
    }
    unsigned int q = tmp.find_first_of(".", p + 1, n);
    if (q == std::string::npos ) {
        str += tmp;
        return;
    }
    str += tmp.substr(0, q);
}

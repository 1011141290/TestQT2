// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

//#include "targetver.h"
//
//#include <stdio.h>
//#include <tchar.h>

#include <sstream>
#include <string>

#define ASSERT_WITH_MSG(cond, msg) do \
{ if (!(cond)) { std::ostringstream str; str << msg; std::cerr << str.str(); std::abort(); } \
} while (0)

struct Constant {
	static double objectValueSmallest;
    static double orthIndexSmallest;
    static double sparseIndexSmallest;
        
	static double nearZero;
	static double nearPosInfi;
    static unsigned int cluMembQueueLen;
};

void setLB(double& x, double lb = Constant::nearZero);
void setUB(double& x, double ub = Constant::nearPosInfi);

void iAppendString(double i, std::string& str);


//usage: ASSERT_MSG(length >= 0, "No positive length found! It is " << length)

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LogFile.cpp
 * Author: Admin
 * 
 * Created on 2015年11月30日, 上午9:06
 */

#include "LogFile.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/thread/thread.hpp>
#include <sstream>

using namespace boost::posix_time;

LogFile::LogFile() {
}

LogFile::LogFile(const LogFile& orig) {
}

LogFile::~LogFile() {
}

std::string LogFile::getFileName() const {
    return fileName;
}

bool LogFile::open(const std::string& file_name) {
    
    fileName = file_name;
    ptime start(microsec_clock::local_time());
    std::stringstream ss;
    ss << start;
	
    std::string tmp(ss.str());
    std::string wholeName = fileName;
    for (const auto& i : tmp) {
        if (i == ':' || i == ' ' || i == '-')
            wholeName += "_";
	else
            wholeName += i;
    }

    wholeName += ".txt";

    std::ofstream::open(wholeName.c_str());
    if (!this->is_open()) {
        std::cout << "LogFile::open..failed to open : " << wholeName << "to output the results" << std::endl;
        return false;
    }
    return true;
}
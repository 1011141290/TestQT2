/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LogFile.h
 * Author: Admin
 *
 * Created on 2015年11月30日, 上午9:06
 */

#ifndef LOGFILE_H
#define LOGFILE_H

#include <iostream>
#include <fstream>
#include <string>

class LogFile: public std::ofstream {
private:
    std::string fileName;
public:
    LogFile();
    LogFile(const LogFile& orig);
    virtual ~LogFile();
public:
    bool open(const std::string& file_name);
    std::string getFileName() const;
};

#endif /* LOGFILE_H */


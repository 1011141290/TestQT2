/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestPropertyTree.cpp
 * Author: Admin
 * 
 * Created on 2015年11月29日, 下午1:29
 */

#include "TestPropertyTree.h"
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

TestPropertyTree::TestPropertyTree() {
}

TestPropertyTree::TestPropertyTree(const TestPropertyTree& orig) {
}

TestPropertyTree::~TestPropertyTree() {
}

void TestPropertyTree::testSimple() {
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("config.txt", pt);
    std::cout << pt.get<int>("Section1.Value1") << std::endl;
    std::cout << pt.get<int>("Section1.Value2") << std::endl;
}


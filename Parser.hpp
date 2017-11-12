
#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector> 
#include <fstream>
#include <sstream>
#include <climits>

#include "Transistor.hpp"
#include "Restriction.hpp"

class Parser {
    public:
    static void FRangeParse(std::string path, std::vector<std::vector<int>>& results);

    static int RTParse(std::string path, std::vector<Restriction>& restrictions); 

    static int TParse(std::string path,
                      std::vector<std::vector<int>>* frecs, 
                      std::vector<Transistor>& result, int TNumber = INT_MAX);
};


#endif
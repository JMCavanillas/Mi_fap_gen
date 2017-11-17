
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

    static int RTParse(std::string path, std::vector<Restriction>& restrictions,
                        std::vector<int>& equivalenceIndex); 

    static int TParse(std::string path,
                      std::vector<std::vector<int>>* frecs, 
                      std::vector<Transistor>& result, std::vector<int>& equivalenceIndex,
                      int TNumber = INT_MAX);
    
    static void genIndexTransRestr(std::vector<Transistor>& transistors, std::vector<Restriction>& restrictions,
            std::vector<int>& result);
};


#endif
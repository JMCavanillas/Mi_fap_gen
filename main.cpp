/* 
 * File:   main.cpp
 * Author: javier
 *
 * Created on 10 de noviembre de 2017, 9:21
 */

#include <cstdlib>

#include "Parser.hpp"
#include "Restriction.hpp"
#include "Random.hpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    int seed = 687685;
    std::srand(seed);
    std::vector<Restriction> restrictions;
    std::vector<std::vector<int>> freqs;
    std::vector<Transistor> transistors;

    Parser::FRangeParse("instancias-modificadas/scen07/DOM.TXT", freqs);
    std::vector<int> equivalenceIndex;
    Parser::TParse("instancias-modificadas/scen07/VAR.TXT", &freqs, transistors, equivalenceIndex, 1000);
    Parser::RTParse("instancias-modificadas/scen07/CTR.TXT", restrictions, equivalenceIndex);
    
    for(int i = 0; i < restrictions.size(); ++i)
    {
        std::cout << restrictions[i].trans1 << " " << restrictions[i].trans2
                << " " << restrictions[i].bound << " " << restrictions[i].interference
                << std::endl;
        
    }

    return 0;
}


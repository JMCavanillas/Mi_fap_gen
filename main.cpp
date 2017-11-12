/* 
 * File:   main.cpp
 * Author: javier
 *
 * Created on 10 de noviembre de 2017, 9:21
 */

#include <cstdlib>

#include "Parser.hpp"
#include "Restriction.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    int seed = 0;
    std::srand(seed);
    std::vector<Restriction> restrictions; 
    
    Parser::RTParse("instancias-modificadas/graph05/ctr.txt", restrictions);
    
    for(int i = 0; i < restrictions.size(); ++i)
    {
        std::cout << restrictions[i].trans1 << " " << restrictions[i].trans2
                << " " << restrictions[i].bound << " " << restrictions[i].interference
                << std::endl;
        
    }

    return 0;
}


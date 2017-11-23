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
#include "Especimen.hpp"
#include "Poblacion.hpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    int seed = 11; // 687685
    std::srand(seed);
    std::vector<Restriction> restrictions;
    std::vector<std::vector<int>> freqs;
    std::vector<Transistor> transistors;

    Parser::FRangeParse("instancias-modificadas/scen08/DOM.TXT", freqs);
    std::vector<int> equivalenceIndex;
    Parser::TParse("instancias-modificadas/scen08/VAR.TXT", &freqs, transistors, equivalenceIndex, 1000);
    Parser::RTParse("instancias-modificadas/scen08/CTR.TXT", restrictions, equivalenceIndex);
    
    
    std::vector<int> indxTransRest;
    Parser::genIndexTransRestr(transistors, restrictions, indxTransRest);
    
    Poblacion poblacionActual(&transistors, &restrictions, &indxTransRest);
    poblacionActual.iniciarPoblacion(50);
    std::cout << poblacionActual.getMejor().getInterference() << endl;
    for (int i = 0; i < 1111; ++i)
    {
        poblacionActual.evolucionGeneracional(0.7, 0);
    }
    Especimen mejor = poblacionActual.getMejor();

    std::cout << mejor.getInterference();
//    Especimen greedy(&transistors, &restrictions, &indxTransRest);
//    
//    std::cout << greedy.getInterference();
    
//    for(int i = 0; i < restrictions.size(); ++i)
//    {
//        std::cout << i << " >> " << restrictions[i].trans1 << " " << restrictions[i].trans2
//                << " " << restrictions[i].bound << " " << restrictions[i].interference
//                << std::endl;
//        
//    }
//      for(int i = 0; i < indxTransRest.size(); ++i)
//    {
//        std::cout << i << " >> " << indxTransRest[i]
//                << std::endl;
//        
//    }
    
    
    return 0;
}


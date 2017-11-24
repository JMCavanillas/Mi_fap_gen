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
#include "AlgoritmosGeneticos.hpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    try{
        if (argc != 7)
            throw std::domain_error("Number of arguments is not correct");

        std::string dom_p, var_p, ctr_p;
        if(argv[2] == "-uc")
        {
            dom_p = "/DOM.TXT";
            var_p = "/VAR.TXT";
            ctr_p = "/CTR.TXT";
        } else if(argv[2] == "-lc")
        {
            dom_p = "/dom.txt";
            var_p = "/var.txt";
            ctr_p = "/ctr.txt";
        } else
            throw std::invalid_argument("El argumento no es correcto, los argumentos "
                "posibles son -uc para buscar archivos en mayúscula y -lc para buscar archivos"
                    " en minúscula");

        std::string path = argv[1];
        std::string GenMode = argv[4];
        int tipoCruce;
        if (argv[5] == "blx")
            tipoCruce = 0;
        else if (argv[5] == "2puntos")
            tipoCruce = 1;
        else
            throw std::invalid_argument("El argumento no es correcto, los argumentos "
                    "posibles son blx para el cruce blx y 2puntos para cruce en 2 puntos");

        std::string seedString = argv[3];
        int seed = std::stoi(seedString);

        std::srand(seed);
        std::vector<Restriction> restrictions;
        std::vector<std::vector<int>> freqs;
        std::vector<Transistor> transistors;

        Parser::FRangeParse(path + dom_p, freqs);
        std::vector<int> equivalenceIndex;
        Parser::TParse(path + var_p, &freqs, transistors, equivalenceIndex, 1200);
        Parser::RTParse(path + ctr_p, restrictions, equivalenceIndex);
        std::vector<int> indxTransRest;
        Parser::genIndexTransRestr(transistors, restrictions, indxTransRest);
        Poblacion poblacionActual(&transistors, &restrictions, &indxTransRest);
        poblacionActual.iniciarPoblacion(50);

        if (argv[6] == "-t")
            std::cout << "Interferencia Inicial Interferencia Final NumReinicios" << std::endl;
        else if (argv[6] != "-o")
            throw std::invalid_argument("El argumento no es correcto, los argumentos posibles son -t"
                    "para mostrar en terminal y -o para mostrar solucion optimizada para guardar en "
                    "un fichero de texto"
                   );

        std::cout << poblacionActual.getMejor().getInterference() << "  ";
        
        int mejor, numReinicios;
        if(argv[4] == "generacional")
            mejor = geneticoGeneracional(50, 20000, poblacionActual, 0.7, tipoCruce, 0.1, numReinicios);
        else if (argv[4] == "estacionario")
            mejor = geneticoEstacionario(50,20000,poblacionActual,1,1,0.1,numReinicios);
        else
            throw std::invalid_argument("El argumento no es correcto, los argumentos posibles son "
                "generacional para seguir un modelo de evolución generacional o estacionario para "
                "seguir un modelo de evolución estacionario"
               );
        
        std::cout << mejor << " " << numReinicios << std::endl;
    } catch (std::exception e) {
        std::cout << e.what();
    }
    
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


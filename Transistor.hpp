
#ifndef TRANSISTOR_HPP
#define TRANSISTOR_HPP

#include <vector>
#include <stdexcept>
#include "Random.hpp"


class Transistor{

    int numID_;                                     // Id del transistor
    int NRange_;                                    // Numero de rango
    std::vector<std::vector<int>>* frecs_;          // Vector de rangos de frecuencias
    
    public: 
    Transistor(int numID, int NRange, std::vector<std::vector<int>>* frecs);

    int getNRange(); 
    int getRandFrec();                           // Devuelve una frecuencia de su rango de frecuencias
    int getFreqRange();
    int getNumID();

    void setFrecs(std::vector<std::vector<int>>* frecs);

    int operator[](unsigned indx);

    virtual ~Transistor();
};

#endif
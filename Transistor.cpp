
#include "Transistor.hpp"

Transistor::Transistor(int numID, int NRange, std::vector<std::vector<int>>* freqs)
{
    this->numID_ = numID;
    this->NRange_ = NRange; 
    this->freqs_ = freqs;
}

int Transistor::getNRange()
{
    return NRange_;
}

/**
 * Se auto-asigna una frecuencia aleatoria dentro de su rango de frecuencias
 * @return 
 */
int Transistor::getRandFrec()
{   
    int frecuencia=getRandomInt(0,getFreqRange()-1);
    return (*freqs_)[NRange_][frecuencia];
}

void Transistor::setFrecs(std::vector<std::vector<int>>* freqs)
{
    this->freqs_ = freqs;
}

int Transistor::operator[](unsigned indx)
{
    return (*freqs_)[NRange_][indx];
}

int Transistor::getNumID()
{
    return numID_;
}

int Transistor::getFreqRange()
{
    return (*freqs_)[NRange_].size();
}


Transistor::~Transistor(){ }

#include "Transistor.hpp"

Transistor::Transistor(int numID, int NRange, std::vector<std::vector<int>>* frecs)
{
    this->numID_ = numID;
    this->NRange_ = NRange; 
    this->frecs_ = frecs;
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
    return (*frecs_)[NRange_][frecuencia];
}

void Transistor::setFrecs(std::vector<std::vector<int>>* frecs)
{
    this->frecs_ = frecs;
}

int Transistor::operator[](unsigned indx)
{
    return (*frecs_)[NRange_][indx];
}

int Transistor::getNumID()
{
    return numID_;
}

int Transistor::getFreqRange()
{
    return (*frecs_)[NRange_].size();
}


Transistor::~Transistor(){ }
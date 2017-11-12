/* 
 * File:   specimen.cpp
 * Author: javier
 * 
 * Created on 12 de noviembre de 2017, 21:02
 */

#include "specimen.hpp"

Specimen::Specimen(std::vector<Transistor>& transistors, std::vector<Restriction>& restrictions) :
                    transistors_(transistors), restrictions_(restrictions)
{
}

Specimen::Specimen(const Specimen& orig) :
                    transistors_(orig.transistors_), restrictions_(orig.restrictions_)
{
}

int Specimen::evaluate()
{
    // POR HACER
}

void Specimen::greedInit()
{
    // POR HACER
}

Specimen::~Specimen() 
{
}


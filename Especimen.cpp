/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Especimen.cpp
 * Author: sobremesa
 * 
 * Created on 13 de noviembre de 2017, 17:01
 */

#include "Especimen.hpp"


Especimen::Especimen(std::vector<Transistor>& transistors, std::vector<Restriction>& restrictions,
        std::vector<int>& indxTransRestr) :
                    transistors_(transistors), restrictions_(restrictions), 
                    indxTransRestr_(indxTransRestr)
{
}

Especimen::Especimen(const Especimen& orig) :
                    transistors_(orig.transistors_), restrictions_(orig.restrictions_),
                    indexes_(orig.indexes_), freqs_(orig.freqs_), indxTransRestr_(orig.indxTransRestr_)
{
}

int Especimen::evaluate()
{
    totalInterference_ = 0;
    for (int i = 0; i < restrictions_.size(); ++i)
        if ( restrictions_[i].bound < 
                std::abs(freqs_[restrictions_[i].trans1] - freqs_[restrictions_[i].trans2]) )
            totalInterference_ += restrictions_[i].interference;
    
}

void Especimen::greedInit()
{
    int k = 0;
    int limit = getRandomInt(transistors_.size()/3, transistors_.size()-1);
    freqs_.resize(transistors_.size());
    for(int i = transistors_.size()-1; i >= 0; --i )
    {
        if(k < limit)
        {
            indexes_[i] = transistors_[i].getRandFrec();
            freqs_[i] = transistors_[i][indexes_[i]];
        }
        else
            freqs_[i] = bestFreq(i);
        
        ++k;
    }
}

int Especimen::bestFreq(int trans)
{



}

int Especimen::calcCost(int trans, int freq)
{
    //    Calcula el coste de uno
    int k = indxTransRestr_[trans];
    int cost = 0;
    while (indxTransRestr_[trans+1] < indxTransRestr_.size() || k != indxTransRestr_[trans+1]) 
    {
        if( restrictions_[k].bound < std::abs(transistors_[trans][freq] -
                freqs_[restrictions_[k].trans2]) )
            cost += restrictions_[k].interference;
        ++k;
    }
    return cost;
}
Especimen::~Especimen() 
{
}

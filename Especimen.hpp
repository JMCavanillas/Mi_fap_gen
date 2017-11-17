/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Especimen.hpp
 * Author: sobremesa
 *
 * Created on 13 de noviembre de 2017, 17:01
 */

#ifndef ESPECIMEN_HPP
#define ESPECIMEN_HPP

#include "Restriction.hpp"
#include "Transistor.hpp"
#include "Random.hpp"
#include <climits>

class Especimen {
public:
    Especimen(std::vector<Transistor>& transistors, std::vector<Restriction>& restrictions
            , std::vector<int>& indxTransRestr);
    Especimen(const Especimen& orig);
    virtual ~Especimen();
    
    void greedInit();
    int evaluate();
    
    friend void cruce2Puntos(Especimen &padreA, Especimen &padreB,int minimo,int maximo);
    friend void cruceBlx(Especimen &padreA, Especimen &padreB,float alpha);
    friend void mutar(Especimen &individuo,int probabilidad);
private:
    std::vector<Transistor>& transistors_;
    std::vector<Restriction>& restrictions_;
    
   
    std::vector<int> freqs_;
    std::vector<int> indexes_;
    std::vector<int>& indxTransRestr_;
     
    int bestFreq(int trans);
    int calcCost(int trans, int freq);
    
    int totalInterference_;
};

#endif /* ESPECIMEN_HPP */


/* 
 * File:   Especimen.hpp
 * Author: Alberto Carrillo Ortega
 *         Javier Martínez Cavanillas
 * Created on 13 de noviembre de 2017, 17:01
 */

#ifndef ESPECIMEN_HPP
#define ESPECIMEN_HPP

#include "Restriction.hpp"
#include "Transistor.hpp"
#include "Random.hpp"
#include <vector>
#include <climits>

class Especimen {
public:
    Especimen( std::vector<Transistor>* transistors, 
            std::vector<Restriction>* restrictions,
            std::vector<int>* indxTransRestr );
    Especimen(const Especimen& orig);
    virtual ~Especimen();
    
    int getSize();
    int getFreqRange(int trans);
    
    int evaluate();
    
    int scanVal(int trans, int pos);
    void sigVal(int trans, int pos);
    
    bool operator== (const Especimen& otro);
    bool operator!= (const Especimen& otro);
    bool operator< (const Especimen& otro) const;
    
    int getInterference() const;
    
    friend void cruce2Puntos(Especimen &padreA, Especimen &padreB,int minimo = 1,int maximo = 0);
    friend void cruceBlx(Especimen &padreA, Especimen &padreB,float alpha = 0.1);
    friend void mutar(Especimen &individuo,double probabilidad = 0.1);
private:
    std::vector<Transistor>* transistors_;
    std::vector<Restriction>* restrictions_;
    
   
    std::vector<int> freqs_;
    std::vector<int> indexes_;
    std::vector<int>* indxTransRestr_;
    
    void greedInit();
    void randInit();
    void fullGreedInit();
    
    int bestFreq(int trans);
    int calcCost(int trans, int freq);
    
    int fullBestFreq(int trans, int cabecera, int cola);
    int fullCalcCost(int trans, int freq, int cabecera, int cola);
    
    int totalInterference_;
};

#endif /* ESPECIMEN_HPP */


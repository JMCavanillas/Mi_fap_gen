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


/**
 * Algoritmo de <b>cruce en 2 puntos</b>. Intercambia los fragmentos de vector comprendidos entre dos puntos aleatorios de
 * los vectores <b>transistor_</b> y <b>indexes</b>
 * @param padreA Especimen padreA
 * @param padreB Especimen padreB
 * @param minimo Numero minimo de elementos a intercambiar, 1 por defecto
 * @param maximo Numero maximo de elementos a intercambiar, 1/3 del vector por defecto
 */
void cruce2Puntos(Especimen &padreA, Especimen &padreB,int minimo=1,int maximo=0){
    if(maximo<=0)
        maximo=padreA.freqs_.size()/3;
    int puntoA=getRandomInt(0,padreA.freqs_.size()-1);  //posicion de inicio para los intercambios
    int volumen=getRandomInt(minimo,maximo);                  //numero de elementos a intercambiar
    
    int fAux,iAux,pos;
    for(int i = 0; i < volumen; i++){
        pos=(puntoA+i) % padreA.freqs_.size();
        fAux=padreA.freqs_[pos];
        iAux=padreA.indexes_[pos];
        
        padreA.freqs_[pos]=padreB.freqs_[pos];
        padreA.indexes_[pos]=padreB.indexes_[pos];
        
        padreB.freqs_[pos]=fAux;
        padreB.indexes_[pos]=iAux;
    }
}

/**
 * Algoritmo de <b>cruce BLX</b>. Intercambia la frecuencia de los individuos por un valor intermedio entre ellos con un factor de aleatoriedad
 * @param padreA Especimen padreA
 * @param padreB Especimen padreB
 * @param alpha Porcentaje de reducción del intervalo. 0,5 por defecto
 */
void cruceBlx(Especimen &padreA, Especimen &padreB,float alpha=0.5){
    int transistor=getRandomInt(0,padreA.freqs_.size());
    
    int intervalo;
    
    intervalo=abs(padreA.indexes_[transistor]-padreB.indexes_[transistor]);
    
    if(intervalo>=padreA.indexes_.size()/6)
        if(padreA.indexes_[transistor]<=padreB.indexes_[transistor]){
            padreA.indexes_[transistor]-=getRandomInt(0,intervalo*alpha);
            padreB.indexes_[transistor]+=getRandomInt(0,intervalo*alpha);
        }else{
            padreB.indexes_[transistor]-=getRandomInt(0,intervalo*alpha);
            padreA.indexes_[transistor]+=getRandomInt(0,intervalo*alpha);
        }
    padreA.freqs_[transistor]=padreA.transistors_[transistor][padreA.indexes_[transistor]];
    padreB.freqs_[transistor]=padreB.transistors_[transistor][padreB.indexes_[transistor]];
}

/**
 * Muta las frecuencias de un individuo de manera aleatoria
 * @param individuo
 * @param probabilidad probabilidad de mutacion. 0.1 por defecto (1 = 100%)
 */
void mutar(Especimen &individuo,int probabilidad=0.1){
    for(int i=0; i< individuo.freqs_.size();++i){
        if(getRandomInt(0,1)<= probabilidad){
            individuo.indexes_[i]=getRandomInt(0,individuo.indexes_.size()-1);
            individuo.freqs_[i]=individuo.transistors_[i][individuo.indexes_[i]];
        }
    }
}
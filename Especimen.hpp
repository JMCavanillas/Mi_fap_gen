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

class Especimen {
public:
    Especimen();
    Especimen(const Especimen& orig);
    virtual ~Especimen();
    friend void cruce2Puntos(Especimen &padreA, Especimen &padreB,int minimo,int maximo);
    friend void cruceBlx(Especimen &padreA, Especimen &padreB,float alpha);
    friend void mutar(Especimen &individuo,int probabilidad);
private:
    std::vector<Transistor>& transistors_;
    std::vector<Restriction>& restrictions_;
    std::vector<int> freqs_;
    std::vector<int> indexes_;
    
    int totalInterference_;
};





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
#endif /* ESPECIMEN_HPP */


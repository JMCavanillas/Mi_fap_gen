/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Poblacion.hpp
 * Author: sobremesa
 *
 * Created on 17 de noviembre de 2017, 17:56
 */

#ifndef POBLACION_HPP
#define POBLACION_HPP

#include "Especimen.hpp"
#include "AlgoritmosGeneticos.hpp"
#include "Random.hpp"
#include <vector>
#include <list>

class Poblacion {
public:
    Poblacion(
            std::vector<Transistor>& transistors, 
            std::vector<Restriction> restrictions, 
            std::vector<int> indxTransRestr
            );
    
    Poblacion(const Poblacion& orig);
    
    void iniciarPoblacion();
    void evolucionEstacionaria(int tipoCruce);
    void evolucionGeneracional(double probabilidad, int tipoCruce);
    
    double comprobarRepetidos();
    
    int getMejor();
    
    virtual ~Poblacion();
    
    
private:
    
    int mejor_;
    
    std::vector<Especimen>* mundo_;
    
    Transistor& transistors_;
    std::vector<Restriction>& restrictions_;
    std::vector<int>& indxTransRestr_;
    
};

#endif /* POBLACION_HPP */


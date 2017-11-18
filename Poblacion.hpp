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
#include <vector>
#include <list>

class Poblacion {
public:
    Poblacion();
    Poblacion(const Poblacion& orig);
    
    void iniciarPoblacion();
    
    virtual ~Poblacion();
    
    
private:
    std::vector<Especimen> Mundo;
    
    Transistor* 
};

#endif /* POBLACION_HPP */


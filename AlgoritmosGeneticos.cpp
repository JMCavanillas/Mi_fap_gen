/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AlgoritmosGeneticos.hpp"

int geneticoGeneracional(int nIndividuos,int evaluaciones,int generaciones,int cruce,int tipo,int mutacion){
    
    Poblacion entorno(nIndividuos);
    
    while(evaluaciones >= 0){
        
        entorno.cruzeGeneracional(cruce,tipo);
        entorno.mutar(mutacion);
        
        if(entorno.evaluar==1)
            entorno.reinicializar();
        
        evaluaciones-=nIndividuos*cruce;        
    }
    return entorno.getMejor().totalInterference_;
}

int geneticoEstacionario(int nIndividuos,int evaluaciones,int generaciones,int cruce,int tipo,int mutacion){
    
    Poblacion entorno(nIndividuos);
    
    while(evaluaciones >= 0){
        
        entorno.cruzeEstacionario(cruce,tipo);
        entorno.mutar(mutacion);
        
        if(entorno.evaluar==1)
            entorno.reinicializar();
        
        evaluaciones-=2;        
    }
    return entorno.getMejor().totalInterference_;
}
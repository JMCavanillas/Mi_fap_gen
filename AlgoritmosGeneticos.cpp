
#include "AlgoritmosGeneticos.hpp"
//
//int geneticoGeneracional(int nIndividuos,int evaluaciones,Poblacion& entorno,int cruce,int tipo,int mutacion){
//    
//
//    
//    while(evaluaciones >= 0){
//        
//        entorno.cruzeGeneracional(cruce,tipo);
//        entorno.mutar(mutacion);
//        
//        if(entorno.evaluar==1)
//            entorno.reinicializar();
//        
//        evaluaciones-=nIndividuos*cruce;        
//    }
//    return entorno.getMejor().totalInterference_;
//}
//
//int geneticoEstacionario(int nIndividuos,int evaluaciones,Poblacion& entornos,int cruce,int tipo,int mutacion){
//    
//
//    
//    while(evaluaciones >= 0){
//        
//        entorno.cruzeEstacionario(cruce,tipo);
//        entorno.mutar(mutacion);
//        
//        if(entorno.evaluar==1)
//            entorno.reinicializar();
//        
//        evaluaciones-=2;        
//    }
//    return entorno.getMejor().totalInterference_;
//}
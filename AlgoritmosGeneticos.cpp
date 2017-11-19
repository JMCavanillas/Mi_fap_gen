
#include "AlgoritmosGeneticos.hpp"

int geneticoGeneracional(int nIndividuos,int evaluaciones,Poblacion& entorno,double cruce,int tipo,double mutacion){
    

    entorno.iniciarPoblacion(nIndividuos);
    while(evaluaciones >= 0){
        
        entorno.evolucionGeneracional(cruce,tipo,mutacion);
        
        if(entorno.comprobarRepetidos()==1)
            entorno.reinicializar();
        
        evaluaciones-=nIndividuos*cruce;        
    }
    return entorno.getMejor().getInterference();
}

int geneticoEstacionario(int nIndividuos,int evaluaciones,Poblacion& entorno,int parejas,int tipo,double mutacion){
    
    if(parejas <= 0)
        parejas = 1;

    entorno.iniciarPoblacion(nIndividuos);
    while(evaluaciones >= 0){
        
        entorno.evolucionEstacionaria(tipo,mutacion,parejas);
        
        if(entorno.comprobarRepetidos()==1)
            entorno.reinicializar();
        
        evaluaciones-=parejas*2;        
    }
    return entorno.getMejor().getInterference();
}
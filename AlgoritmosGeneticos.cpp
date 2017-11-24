
#include "AlgoritmosGeneticos.hpp"

int geneticoGeneracional(int nIndividuos,int evaluaciones,Poblacion& entorno,double cruce,int tipo,double mutacion, int& numReinicios){
    
    numReinicios = 0;
    entorno.iniciarPoblacion(nIndividuos);
    while(evaluaciones >= 0){
        
        entorno.evolucionGeneracional(cruce,tipo,mutacion);
        
        if(entorno.comprobarRepetidos()){
            entorno.reinicializar();
            ++numReinicios;
        }
        
        evaluaciones-=nIndividuos*cruce;        
    }
    return entorno.getMejor().getInterference();
}

int geneticoEstacionario(int nIndividuos,int evaluaciones,Poblacion& entorno,int parejas,int tipo,double mutacion, int& numReinicios){
    
    numReinicios = 0;
    if(parejas <= 0)
        parejas = 1;

    entorno.iniciarPoblacion(nIndividuos);
    while(evaluaciones >= 0){
        
        entorno.evolucionEstacionaria(tipo,mutacion,parejas);
        
        if(entorno.comprobarRepetidos()){
            entorno.reinicializar();
            ++numReinicios;
        }
        
        evaluaciones-=parejas*2;        
    }
    return entorno.getMejor().getInterference();
}

#include "AlgoritmosGeneticos.hpp"

int geneticoGeneracional(int nIndividuos,int evaluaciones,Poblacion& entorno,double cruce,int tipo,double mutacion){
    
    entorno.iniciarPoblacion(nIndividuos);
    int generaciones= 20;
    auto guardia = entorno.getMejor();
    while(evaluaciones >= 0){
        
        entorno.evolucionGeneracional(cruce,tipo,mutacion);
        
        if(guardia != entorno.getMejor()){
            generaciones = 20;
            guardia=entorno.getMejor();
        }else{
            generaciones--;
            if(generaciones==0){
                entorno.reinicializar();
                evaluaciones-=nIndividuos;
                continue;
            }
        }
        if(entorno.comprobarRepetidos()){
            entorno.reinicializar();
            evaluaciones-=nIndividuos-1;
            continue;
        }
        
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
        
        if(entorno.comprobarRepetidos()){
            entorno.reinicializar();
            evaluaciones-=nIndividuos-1;
            continue;
        }
        
        evaluaciones-=parejas*2;        
    }
    return entorno.getMejor().getInterference();
}
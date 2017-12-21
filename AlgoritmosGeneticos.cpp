
#include "AlgoritmosGeneticos.hpp"

int geneticoGeneracional(int nIndividuos,int evaluaciones,Poblacion& entorno,double cruce,int tipo,double mutacion){
    
    int generaciones= 20;
    int guardia = entorno.getMejor().getInterference();
    while(evaluaciones >= 0){
        
        entorno.evolucionGeneracional(cruce,tipo,mutacion);
        
        if(guardia != entorno.getMejor().getInterference()){
            generaciones = 20;
            guardia=entorno.getMejor().getInterference();
        } else {
            --generaciones;
            if(!generaciones){
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

int busquedaLineal( Especimen& esp, int numEval)
{
    int tam = esp.getSize();
    int trans = getRandomInt(0,tam-1);
    for(int i = 0; i < numEval; ++i)
    {
        int freqCount = 0;
        while( freqCount < esp.getFreqRange(trans) && i < numEval)
        {
            if(esp.scanVal(trans, freqCount) < esp.getInterference())
            {
                esp.sigVal(trans, freqCount);
                esp.evaluate();
                break;
            }
            ++freqCount;
            ++i;
        }
        trans = (trans + 1)%tam;
        ++i;
    }
    
    return  esp.getInterference();
}

int am1010(int nIndividuos, int evaluaciones,Poblacion& entorno, double cruce, int tipo, double mutacion)
{
    while (evaluaciones >= 0)
    {
        geneticoGeneracional(20, 140, entorno, 0.7, tipo, 0.1);
//        std::cout << "Nuevas 10 Gen ------------" << std::endl;
        evaluaciones -= 140;
        
        for (int i = 0; i < entorno.mundo_->size(); ++i)
        {
//            std::cout << (*entorno.mundo_)[i].getInterference() << " --> ";
            busquedaLineal((*entorno.mundo_)[i], 200);
//            std::cout << (*entorno.mundo_)[i].getInterference() << std::endl;
            entorno.actualizarMejor();
            evaluaciones -= 200;
        }
    }
    return entorno.getMejor().getInterference();
}

int am1001(int nIndividuos, int evaluaciones,Poblacion& entorno, double cruce, int tipo, double mutacion)
{
    while (evaluaciones >= 0)
    {
        geneticoGeneracional(20, 140, entorno, 0.7, tipo, 0.1);
//        std::cout << "Nuevas 10 Gen ------------" << std::endl;
        evaluaciones -= 140;
        
        for (int i = 0; i < entorno.mundo_->size()*0.1; ++i)
        {
            int tamPoblacion = entorno.mundo_->size();
            int start = getRandomInt(0, tamPoblacion-1);
            
//            std::cout << (*entorno.mundo_)[i].getInterference() << " --> ";
            busquedaLineal((*entorno.mundo_)[(start+i)%tamPoblacion], 200);
//            std::cout << (*entorno.mundo_)[i].getInterference() << std::endl;
            
            entorno.actualizarMejor();
            evaluaciones -= 200;
        }
    }
    return entorno.getMejor().getInterference();
}

int am1001Mej(int nIndividuos, int evaluaciones,Poblacion& entorno, double cruce, int tipo, double mutacion)
{
    while (evaluaciones >= 0)
    {
        geneticoGeneracional(20, 140, entorno, 0.7, tipo, 0.1);
//        std::cout << "Nuevas 10 Gen ------------" << std::endl;
        evaluaciones -= 140;
        
        std::set<int> vistos;
        
        for (int i = 0; i < entorno.mundo_->size()*0.1; ++i)
        {
            int tamPoblacion = entorno.mundo_->size();
            
            int mejor = 0;
            int vMejor = INT_MAX;
            for(int j = 0; j < entorno.mundo_->size(); ++j)
                if( vMejor > (*entorno.mundo_)[j].getInterference() 
                        && vistos.find(j) == vistos.end())
                {
                    vMejor = (*entorno.mundo_)[j].getInterference();
                    mejor = j;
                }

            vistos.insert(mejor);

//            std::cout << (*entorno.mundo_)[mejor].getInterference() << " --> ";
            busquedaLineal((*entorno.mundo_)[mejor], 200);
//            std::cout << (*entorno.mundo_)[mejor].getInterference() << std::endl;
            
            entorno.actualizarMejor();
            evaluaciones -= 200;
        }
    }
    return entorno.getMejor().getInterference();
}
/* 
 * File:   Poblacion.hpp
 * Author: Alberto Carrillo Ortega
 *         Javier Martínez Cavanillas
 * Created on 17 de noviembre de 2017, 17:56
 */

#ifndef POBLACION_HPP
#define POBLACION_HPP

#include "Especimen.hpp"
#include "Random.hpp"
#include <vector>
#include <list>
#include <map>
#include <set>

class Poblacion {
public:
    Poblacion(
            std::vector<Transistor>* transistors, 
            std::vector<Restriction>* restrictions, 
            std::vector<int>* indxTransRestr
            );
    
    Poblacion(const Poblacion& orig);
    
    void iniciarPoblacion(int nIndividuos);
    void evolucionEstacionaria(int tipoCruce, double pMutacion = 0.1, int parejas = 1);
    void evolucionGeneracional(double probabilidad, int tipoCruce, double pMutacion = 0.1);
    
    friend int am1010(int nIndividuos, int evaluaciones,Poblacion& entorno, double cruce, int tipo, double mutacion);

    friend int am1001(int nIndividuos, int evaluaciones,Poblacion& entorno, double cruce, int tipo, double mutacion);

    friend int am1001Mej(int nIndividuos, int evaluaciones,Poblacion& entorno, double cruce, int tipo, double mutacion);
    
    bool comprobarRepetidos();
    
    void actualizarMejor();
    void reinicializar();
    
    Especimen getMejor();
    
    virtual ~Poblacion();
    
    
private:
    
    int mejor_;
    
    std::vector<Especimen>* mundo_;
    
    std::vector<Transistor>* transistors_;
    std::vector<Restriction>* restrictions_;
    std::vector<int>* indxTransRestr_;
    
};

#endif /* POBLACION_HPP */


/* 
 * File:   AlgoritmosGeneticos.hpp
 * Author: Alberto Carrillo Ortega
 *         Javier Martínez Cavanillas
 *
 * Created on 17 de noviembre de 2017, 18:18
 */

#ifndef ALGORITMOSGENETICOS_HPP
#define ALGORITMOSGENETICOS_HPP

#include "Poblacion.hpp"

//enum Cruce {
//    blx, en2Puntos
//};

/**
 * Algoritmo genético generacional con elitismo
 * @param nIndividuos       Numero de individuos de la poblacion con la que ejecutar el algoritmo
 * @param evaluciones       Numero de evaluaciones de los individuos
 * @param entorno           Poblacion sobre la que aplicar el algoritmo
 * @param cruce             Probabilidad de Cruce
 * @param tipo              Tipo de cruce, 0 = BLX 1 = 2 Puntos
 * @param mutacion          Probabilidad de mutación
 * @return 
 */
int geneticoGeneracional(int nIndividuos, int evaluaciones,Poblacion& entorno, double cruce, int tipo,double mutacion);

/**
 * Algoritmo genético estacionario
 * @param nIndividuos       Numero de individuos de la poblacion con la que ejecutar el algoritmo
 * @param evaluaciones      Numero de evaluaciones de los individuos
 * @param entorno           Poblacion sobre la que aplicar el algoritmo
 * @param parjas            Numero de parejas a cruzar
 * @param tipo              Tipo de cruce, 0 = BLX 1 = 2 Puntos
 * @param mutacion          Probabilidad de mutación
 * @return 
 */
int geneticoEstacionario(int nIndividuos, int evaluaciones,Poblacion& entorno, int parejas, int tipo, double mutacion);

#endif /* ALGORITMOSGENETICOS_HPP */


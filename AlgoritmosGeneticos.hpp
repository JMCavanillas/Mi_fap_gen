/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AlgoritmosGeneticos.hpp
 * Author: sobremesa
 *
 * Created on 17 de noviembre de 2017, 18:18
 */

#ifndef ALGORITMOSGENETICOS_HPP
#define ALGORITMOSGENETICOS_HPP

enum Cruce {
    blx, en2Puntos
};

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
int geneticoGeneracional(int nIndividuos,int evaluaciones,Poblacion& entorno,int cruce,int tipo,int mutacion);

/**
 * Algoritmo genético estacionario
 * @param nIndividuos       Numero de individuos de la poblacion con la que ejecutar el algoritmo
 * @param evaluaciones      Numero de evaluaciones de los individuos
 * @param entorno           Poblacion sobre la que aplicar el algoritmo
 * @param cruce             Probabilidad de Cruce
 * @param tipo              Tipo de cruce, 0 = BLX 1 = 2 Puntos
 * @param mutacion          Probabilidad de mutación
 * @return 
 */
int geneticoEstacionario(int nIndividuos,int evaluaciones,Poblacion& entorno,int cruce,int tipo,int mutacion);

#endif /* ALGORITMOSGENETICOS_HPP */


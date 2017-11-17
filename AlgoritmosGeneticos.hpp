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

#include "Poblacion.hpp"

/**
 * Algoritmo genético generacional con elitismo
 * @param poblacion         
 * @param evaluaciones
 * @param generaciones
 * @param cruce
 * @param mutacion
 * @return 
 */
int geneticoGeneracional(int poblacion,int evaluaciones,int generaciones,int cruce, int mutacion);

#endif /* ALGORITMOSGENETICOS_HPP */


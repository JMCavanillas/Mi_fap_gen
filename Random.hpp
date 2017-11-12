/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Random.hpp
 * Author: sobremesa
 *
 * Created on 12 de noviembre de 2017, 12:34
 */

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <iostream>
#include <stdlib.h>
#include <climits>


/**
 * Genera un numero <b>aleatorio</b> en el intervalo {inferior,superior}
 * @param inferior Limite inferior del intervalo en el que generar el <b>aleatorio</b>
 * @param superior Limite superior del intervalo en el que generar el <b>aleatorio</b>
 * @return 
 */
int getRandomInt(int inferior, int superior);


#endif /* RANDOM_HPP */


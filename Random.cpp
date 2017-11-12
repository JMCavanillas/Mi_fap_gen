/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Random.hpp"


int getRandomInt(int inferior, int superior){
    int aleatorio= inferior + rand()%(superior-inferior);
    return aleatorio;
};
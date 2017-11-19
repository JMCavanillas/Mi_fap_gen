
#include "Random.hpp"

/**
 * Genera un entero comprendido entre dos números, siendo ambos incluidos dentro del rango
 * @param inferior  Límite inferior (intervalo cerrado)
 * @param superior  Límite superior (intervalo cerrado)
 * @return int
 */
int getRandomInt(int inferior, int superior){
    int aleatorio= inferior + rand()%(superior-inferior);
    return aleatorio;
};
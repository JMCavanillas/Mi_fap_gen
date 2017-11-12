/* 
 * File:   MixOperator.hpp
 * Author: javier
 *
 * Created on 12 de noviembre de 2017, 21:29
 */

#ifndef MIXOPERATOR_HPP
#define MIXOPERATOR_HPP

#include "specimen.hpp"


class MixOperator 
{
public:
    virtual void mix(Specimen& parent1, Specimen& parent2) = 0;
};

#endif /* MIXOPERATOR_HPP */


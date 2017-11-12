/* 
 * File:   SelectionModel.hpp
 * Author: javier
 *
 * Created on 12 de noviembre de 2017, 21:36
 */

#ifndef SELECTIONMODEL_HPP
#define SELECTIONMODEL_HPP

#include <vector>

#include "specimen.hpp"


class SelectionModel
{
public:
    virtual void select(const std::vector<Specimen>& population, std::vector<Specimen>& candidates) = 0;
    virtual void replace(std::vector<Specimen>& population, const std::vector<Specimen>& candidates) = 0;
};

#endif /* SELECTIONMODEL_HPP */


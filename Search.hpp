/* 
 * File:   Search.hpp
 * Author: javier
 *
 * Created on 12 de noviembre de 2017, 22:00
 */

#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "Transistor.hpp"
#include "Restriction.hpp"
#include "specimen.hpp"
#include "SelectionModel.hpp"
#include "Population.hpp"

namespace Search
{
    Specimen genSearch(std::vector<Transistor> transistors, std::vector<Restriction> restrictions,
                        std::string selectionMode, std::string mixOperator);
    
    void genIndexTransRestr(std::vector<Transistor>& transistors, std::vector<Restriction>& restrictions,
            std::vector<int>& result);
}

#endif /* SEARCH_HPP */


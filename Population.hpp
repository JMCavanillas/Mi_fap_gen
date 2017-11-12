/* 
 * File:   Population.hpp
 * Author: javier
 *
 * Created on 12 de noviembre de 2017, 19:41
 */

#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>

#include "specimen.hpp"
#include "Restriction.hpp"
#include "Transistor.hpp"
#include "MixOperator.hpp"
#include "SelectionModel.hpp"


class Population {
private:
    
    int evalNum_;
    
    std::vector<Transistor>& transistors_;
    std::vector<Restriction>& restrictions_;
    
    std::vector<Specimen> population_;
    std::vector<Specimen> candidates_;
    
    SelectionModel* selectionModel_;
    MixOperator* mixOperator_;
    
public:
    Population(std::vector<Transistor>& transistors, 
                std::vector<Restriction>& restrictions,
                SelectionModel* selectionModel, MixOperator* mixOperator);
    Population(const Population& orig);
    virtual ~Population();
    
    void initPopulation(int size);
    void nextGen();
    bool checkEqualityLevel( double percentage );
    
    int getBestSpecimen();

};

#endif /* POPULATION_HPP */


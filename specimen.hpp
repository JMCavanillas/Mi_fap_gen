/* 
 * File:   specimen.hpp
 * Author: javier
 *
 * Created on 12 de noviembre de 2017, 21:02
 */

#ifndef SPECIMEN_HPP
#define SPECIMEN_HPP

#include <vector>

#include "Restriction.hpp"
#include "Transistor.hpp"
#include "Random.hpp"


class Specimen {
    
friend class Population;

private:
    std::vector<Transistor>& transistors_;
    std::vector<Restriction>& restrictions_;
    std::vector<int>& indxTransRestr_;
    
    std::vector<int> freqs_;
    std::vector<int> indexes_;
    
    int totalInterference_;
    
    int bestFreq(int trans);
    int calcCost(int trans, int freq);
    
public:
    Specimen(std::vector<Transistor>& transistors, std::vector<Restriction>& restrictions
            , std::vector<int>& indxTransRestr);
    Specimen(const Specimen& orig);
    virtual ~Specimen();
    
    void greedInit();
    int evaluate();

};

#endif /* SPECIMEN_HPP */


/* 
 * File:   Population.cpp
 * Author: javier
 * 
 * Created on 12 de noviembre de 2017, 19:41
 */

#include "Population.hpp"

Population::Population(std::vector<Transistor>& transistors,
        std::vector<Restriction>& restrictions, 
        std::vector<int>& indxTransRestr,
        SelectionModel* selectionModel, MixOperator* mixOperator) : 
        transistors_(transistors), restrictions_(restrictions), 
        selectionModel_(selectionModel), mixOperator_(mixOperator),
        indxTransRestr_(indxTransRestr), evalNum_(0)
{

}

Population::Population(const Population& orig) :         
        transistors_(orig.transistors_), restrictions_(orig.restrictions_), 
        population_(orig.population_), candidates_(orig.candidates_),
        selectionModel_(orig.selectionModel_), mixOperator_(orig.mixOperator_),
        indxTransRestr_(orig.indxTransRestr_), evalNum_(orig.evalNum_)
{
    
}

Population::~Population() 
{
}

void Population::initPopulation(int size)
{
    // POR HACER
}

void Population::nextGen()
{
    // POR HACER
}

bool Population::checkEqualityLevel(double percentage)
{
    // POR HACER
}

int Population::getBestSpecimen()
{
    // POR HACER
}


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Poblacion.cpp
 * Author: sobremesa
 * 
 * Created on 17 de noviembre de 2017, 17:56
 */

#include "Poblacion.hpp"

Poblacion::Poblacion(std::vector<Transistor>& transistors, 
        std::vector<Restriction> restrictions, 
        std::vector<int> indxTransRestr)    : transistors_(transistors), 
        restrictions_(restrictions), indxTransRestr_(indxTransRestr)
{
    mejor_ = 0;
    mundo_ = new std::vector<Especimen>;
}

Poblacion::Poblacion(const Poblacion& orig)     : transistors_(orig.transistors_),
        restrictions_(orig.transistors_), indxTransRestr_(orig.indxTransRestr_),
        mejor_(orig.mejor_)
{
    mundo_ = new std::vector<Especimen>;
    *mundo_ = *orig.mundo_;
}

Poblacion::~Poblacion() 
{
    delete mundo_;
}


void Poblacion::iniciarPoblacion(int nIndividuos)
{
    int vMejor = INT_MAX;
    for(int i = 0; i < nIndividuos; ++i)
    {
        Especimen nuevoEsp(transistors_, restrictions_, indxTransRestr_);
        (*mundo_).push_back(nuevoEsp);
        if(vMejor > nuevoEsp.getInterference())
        {
            mejor_ = i;
            vMejor = nuevoEsp.getInterference();
        }
    }
}

void Poblacion::evolucionGeneracional(double probabilidad, int tipoCruce)
{
    // Inicializamos hijos y lista de candidatos
    std::vector<Especimen>* hijos = new std::vector<Especimen>;
    *hijos = *mundo_;
    
    std::vector<int> candidatos;
    
    // Calculamos esperanza Matematica
    int numCandidatos = (int)(mundo_->size()*probabilidad);
    
    if(!numCandidatos)
        return; 
    
    if(numCandidatos%2 != 0) ++numCandidatos;
    
    // Seleccionamos por Torneo Binario
    candidatos.reserve(candidatos);
    for(int i = 0; i < numCandidatos; ++i)
    {
        int candidato1 = getRandomInt(0, mundo_->size()-1);
        int candidato2 = getRandomInt(0, mundo_->size()-1);
        
        if( (*mundo_)[candidato1].getInterference() < (*mundo_)[candidato2].getInterference() )
            candidatos.push_back( candidato1 );
        else
            candidatos.push_back( candidato2 );
    }
    
    // Cruzamos los candidatos
    for (int i = 0; i < numCandidatos; i +=2 )
        if(tipoCruce == 0)
            cruceBlx( (*hijos) [ candidatos[i] ] , (*hijos) [ candidatos[i+1] ] );
        else (tipoCruce == 1)
            cruce2Puntos( (*hijos) [ candidatos[i] ] , (*hijos) [ candidatos[i+1] ] );
    
    // Evaluamos los que Hayamos cruzado
    for(int i = 0; i < numCandidatos; ++i)
    {
        // Comprobamos que no lo hayamos evaluado antes ya que puede haberse cruzado 2 veces
        bool evaluado = false;
        for (int j = i-1; j >= 0; --j)
            if(candidatos[i] == candidatos[j])
            {
                evaluado = true;
                break;
            }
        
        if(!evaluado)
            (*hijos)[ candidatos[i] ].evaluate();
        
    }
    
    // Elitismo: Si el mejor ha sido reemplazado la sustituimos por el peor de los hijos
    if( (*mundo_)[mejor_] != (*hijos)[mejor_] ) 
    {
        int peor = 0;
        int vPeor = (*hijos)[0].getInterference();
        for(int i = 1; i < hijos->size(); ++i)
            if( vPeor < (*hijos)[i].getInterference() )
            {
                vPeor = (*hijos)[i].getInterference();
                peor = i;
            }
        
        (*hijos)[peor] = (*mundo_)[mejor_];
    }
    
    // Reemplazamos
    delete mundo_;
    mundo_ = hijos;
    
    // Calculamos y actualizamos el mejor
    int mejor = 0;
    int vMejor = (*mundo_)[0].getInterference();
    for(int i = 1; i < mundo_->size(); ++i)
        if( vMejor > (*mundo_)[i].getInterference() )
        {
            vMejor = (*mundo_)[i].getInterference();
            mejor = i;
        }
    
    mejor_ = mejor;
}

void Poblacion::evolucionEstacionaria(int tipoCruce, int parejas=1) 
{
    // Inicializamos hijos
    std::vector<Especimen> hijos;
    
    // Seleccionamos hijos al azar
    for(int i = 0; i < parejas*2; ++i)
    {
        int candidato = getRandomInt(0, mundo_->size()-1);
        hijos.push_back( (*mundo_)[candidato] );
    }
    
    // Cruzamos los candidatos
    for (int i = 0; i < hijos.size(); i +=2 )
        if(tipoCruce == 0)
            cruceBlx( hijos [i] , hijos [i+1] );
        else (tipoCruce == 1)
            cruce2Puntos( hijos [i] , hijos [i+1] );
    
    // Evaluamos
    for (int i = 0; i < hijos.size(); ++i)
        hijos[i].evaluate();
    
    // Buscamos los N peores y reemplazamos
    std::set<int> vistos;
    for(int i = 0; i < hijos.size(); ++i)
    { 
        int peor = 0;
        int vPeor = -1;
        for(int j = 0; j < mundo_->size(); ++j)
            if( vPeor < (*hijos)[j].getInterference() && vistos.find(j) == vistos.end())
            {
                vPeor = (*hijos)[j].getInterference();
                peor = j;
            }
        
        vistos.insert(peor);
        
        // Comprobamos si es el mejor hasta el momento y si lo es lo colocamos en
        // el sitio que este piensa ocupar. El del que antes era el peor
        if ( (*mundo_)[mejor_].getInterference() > hijos[i].getInterference())
            mejor_ = peor; 
        
        if((*mundo_)[peor].getInterference() > hijos[i].getInterference())
            (*mundo_)[peor] = hijos[i];
    }
    
}


Especimen Poblacion::getMejor()
{
    return (*mundo_)[mejor_];
}

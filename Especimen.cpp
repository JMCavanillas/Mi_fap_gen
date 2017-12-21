/* 
 * File:   Especimen.cpp
 * Author: Alberto Carrillo Ortega
 *         Javier Martínez Cavanillas
 * Created on 13 de noviembre de 2017, 17:01
 */

#include "Especimen.hpp"

/**
 * Constructor principal
 * Genera un Especimen inicando sus frecuencias con un algoritmo voraz
 * @param transistors   Vector de transistores sobre los que generar la poblacion
 * @param restrictions  Conjunto de restricciones que rigen la población
 * @param indxTransRestr    Indice que indica la posición de cada transistor en el conjunto de restricciones
 */
Especimen::Especimen(std::vector<Transistor>* transistors, std::vector<Restriction>* restrictions,
        std::vector<int>* indxTransRestr) :
                    transistors_(transistors), restrictions_(restrictions), 
                    indxTransRestr_(indxTransRestr)
{
    randInit();
    evaluate();
}

/**
 * Constructor copia
 * Genera una copia del Especimen
 * @param orig
 */
Especimen::Especimen(const Especimen& orig) :
                    transistors_(orig.transistors_), restrictions_(orig.restrictions_),
                    indexes_(orig.indexes_), freqs_(orig.freqs_), indxTransRestr_(orig.indxTransRestr_),
                    totalInterference_(orig.totalInterference_)
{
}

/**
 * Calcula la frecuencia total actual generada por su conjunto de frecuencias
 * @return 
 */
int Especimen::evaluate()
{
    totalInterference_ = 0;
    for (int i = 0; i < restrictions_->size(); ++i)
        if ( (*restrictions_)[i].bound < 
                std::abs(freqs_[ (*restrictions_)[i].trans1] - freqs_[ (*restrictions_)[i].trans2]) )
            totalInterference_ += (*restrictions_)[i].interference;
    
}

/**
 * Prevee la interferencia despues de cambios en frecuencia
 * @param trans
 */
int Especimen::scanVal(int trans, int pos)
{
    int prevision = 0;
    int rfreq = (*transistors_)[trans].getFreqRange();
    prevision = totalInterference_ - fullCalcCost(trans, indexes_[trans], 0, transistors_->size() );
    
    indexes_[trans] = (indexes_[trans] + pos)%rfreq;
    freqs_[trans] = (*transistors_)[trans][indexes_[trans]];
    
    prevision += fullCalcCost(trans, indexes_[trans], 0, transistors_->size() );
    
    indexes_[trans] = (rfreq + (indexes_[trans] - pos)%rfreq) % rfreq;
    freqs_[trans] = (*transistors_)[trans][indexes_[trans]];
    return prevision;
}

/**
 * Avanza pos frecuencias el transistor seleccionado
 * @param trans
 * @param pos
 */
void Especimen::sigVal(int trans, int pos)
{
    totalInterference_ -= fullCalcCost(trans, indexes_[trans], 0, transistors_->size()-1 );
    indexes_[trans] = (indexes_[trans] + pos)%(*transistors_)[trans].getFreqRange();
    freqs_[trans] = (*transistors_)[trans][indexes_[trans]];
    totalInterference_ += fullCalcCost(trans, indexes_[trans], 0, transistors_->size()-1 );
}

void Especimen::randInit()
{
    indexes_.resize(transistors_->size());
    freqs_.resize(transistors_->size());
    for (int i = 0; i < transistors_->size(); ++i)
    {
        indexes_[i] = (*transistors_)[i].getRandFrec();
        freqs_[i] = (*transistors_)[i][indexes_[i]];
    }

}


/**
 * Ejecuta algoritmo voraz de inicialización
 */
void Especimen::greedInit()
{
    int k = 0;
    int limit = getRandomInt(transistors_->size()/3, transistors_->size()-1);
    indexes_.resize(transistors_->size());
    freqs_.resize(transistors_->size());
    for(int i = transistors_->size()-1; i >= 0; --i )
    {
        if(k < limit)
        {
            indexes_[i] = (*transistors_)[i].getRandFrec();
            freqs_[i] = (*transistors_)[i][indexes_[i]];
        }
        else
        {
            indexes_[i] = bestFreq(i);
            freqs_[i] = (*transistors_)[i][indexes_[i]];
        }
            
        ++k;
    }
    
}


void Especimen::fullGreedInit() 
{
    int start = getRandomInt(0, transistors_->size()-1);
    indexes_.resize(transistors_->size());
    freqs_.resize(transistors_->size());
    
    indexes_[start] = (*transistors_)[start].getRandFrec();
    freqs_[start] = (*transistors_)[start][indexes_[start]];
    
    int cabecera = (start + 1)%transistors_->size();
    int cola = start;
    
    while ( cabecera != cola )
    {
        indexes_[cabecera] = fullBestFreq(cabecera, cabecera, cola);
        freqs_[cabecera] = (*transistors_)[cabecera][indexes_[cabecera]];
        
        cabecera = (cabecera + 1)%transistors_->size();
    }
}

int Especimen::fullBestFreq(int trans, int cabecera, int cola)
{
    int minimo=INT_MAX;
    int frecMin=-1;
    int rango = (*transistors_)[trans].getFreqRange();
    for(int i = 0; i < rango ; ++i)
    {
        int coste =fullCalcCost(trans,i, cabecera, cola);
        if(minimo > coste)
        {
            minimo = coste;
            frecMin=i;
        }
        if(!minimo)
            break;
    }
    return frecMin;
}

/**
 * Calcula el coste que añade un transistor a su configuracion de compañeros actual
 * @param trans Indice del transistor actual
 * @param freq Indice de la frecuencia actual
 * @param cabecera
 * @param cola
 * @return 
 */
int Especimen::fullCalcCost(int trans, int freq, int cabecera, int cola)
{
    //    Calcula el coste de uno
    int k = (*indxTransRestr_)[trans];
    int cost = 0;
    if ( trans+1 < (*indxTransRestr_).size())
    {
        if(cola < cabecera)
        {
            while (k != (*indxTransRestr_)[trans+1]) 
            {
                if( (*restrictions_)[k].trans2 > cola &&  (*restrictions_)[k].trans2 < cabecera)
                    if( (*restrictions_)[k].bound < std::abs((*transistors_)[trans][freq] -
                        freqs_[(*restrictions_)[k].trans2]) )
                    cost += (*restrictions_)[k].interference;

                ++k;
            }  
            
            k = (*indxTransRestr_)[trans];
            while(k >= 0 && k >= cola)
            {
                if ((*restrictions_)[k].trans2 == trans)
                    if( (*restrictions_)[k].bound < std::abs((*transistors_)[trans][freq] -
                        freqs_[(*restrictions_)[k].trans1]) )
                        cost += (*restrictions_)[k].interference;
                --k;
            }
        }
        else
        {
            while (k != (*indxTransRestr_)[trans+1]) 
            {
                if( !((*restrictions_)[k].trans2 > cola &&  (*restrictions_)[k].trans2 < cabecera) )
                    if( (*restrictions_)[k].bound < std::abs((*transistors_)[trans][freq] -
                        freqs_[(*restrictions_)[k].trans2]) )
                    cost += (*restrictions_)[k].interference;

                ++k;
            }
            
            k = (*indxTransRestr_)[trans];
            while(k >= 0)
            {
                if ((*restrictions_)[k].trans2 == trans)
                    if( (*restrictions_)[k].bound < std::abs((*transistors_)[trans][freq] -
                        freqs_[(*restrictions_)[k].trans1]) )
                        cost += (*restrictions_)[k].interference;
                --k;
            }
        }
    }

    return cost;
}

/**
 * Busca la mejor frecuencia teniendo en cuenta las restricciones con sus transistores
 * de la derecha
 * @param trans
 * @return 
 */
int Especimen::bestFreq(int trans)
{
    int minimo=INT_MAX;
    int frecMin=-1;
    int rango = (*transistors_)[trans].getFreqRange();
    for(int i = 0; i < rango ; ++i)
    {
        int coste =calcCost(trans,i);
        if(minimo > coste)
        {
            minimo = coste;
            frecMin=i;
        }
        if(!minimo)
            break;
    }
    return frecMin;
}

/**
 * Calcula el coste individual teniendo en cuenta las restricciones con sus
 * Transistores de la derecha
 * @param trans
 * @param freq
 * @return 
 */
int Especimen::calcCost(int trans, int freq)
{
    //    Calcula el coste de uno
    int k = (*indxTransRestr_)[trans];
    int cost = 0;
    if ( trans+1 < (*indxTransRestr_).size())
    {
        while (k != (*indxTransRestr_)[trans+1]) 
        {
            if( (*restrictions_)[k].bound < std::abs((*transistors_)[trans][freq] -
                    freqs_[(*restrictions_)[k].trans2]) )
                cost += (*restrictions_)[k].interference;
            ++k;
        }
    }
    return cost;
}

/**
 * Compara 2 Especimenes, 1º mira si tienen la misma interferencia y luego si tienen la mismas frecuencias
 * @param otro
 * @return 
 */
bool Especimen::operator==(const Especimen& otro) {
    
    if(this->totalInterference_==otro.totalInterference_){
        for(int i = 0; i< this->freqs_.size();++i)
            if(this->freqs_[i]!=otro.freqs_[i])
                return false;
    }else
        return false;
    
    return true;
}

bool Especimen::operator!=(const Especimen& otro)
{
    if(this->totalInterference_==otro.totalInterference_){
    for(int i = 0; i< this->freqs_.size();++i)
        if(this->freqs_[i]!=otro.freqs_[i])
            return true;
    }else
        return true;
    
    return false;
}

bool Especimen::operator<(const Especimen& otro) const{
    if(totalInterference_ < otro.totalInterference_)
        return true;
    
    if(totalInterference_ > otro.totalInterference_)
        return false;
    
    if (freqs_ < otro.freqs_)
        return true;
    
    return false;
}


/**
 * Retorna interferencia
 * @return int 
 */
int Especimen::getInterference() const
{
    return totalInterference_;
}

/**
 * Destructor
 */
Especimen::~Especimen() 
{
}


/**
 * Algoritmo de <b>cruce en 2 puntos</b>. Intercambia los fragmentos de vector comprendidos entre dos puntos aleatorios de
 * los vectores <b>transistor_</b> y <b>indexes</b>
 * @param padreA Especimen padreA
 * @param padreB Especimen padreB
 * @param minimo Numero minimo de elementos a intercambiar, 1 por defecto
 * @param maximo Numero maximo de elementos a intercambiar, 1/3 del vector por defecto
 */
void cruce2Puntos(Especimen &padreA, Especimen &padreB,int minimo,int maximo){
    if(maximo<=0)
        maximo=padreA.freqs_.size()/3;
    int puntoA=getRandomInt(0,padreA.freqs_.size()-1);  //posicion de inicio para los intercambios
    int volumen=getRandomInt(minimo,maximo);                  //numero de elementos a intercambiar
    
    int fAux,iAux,pos;
    for(int i = 0; i < volumen; i++){
        pos=(puntoA+i) % padreA.freqs_.size();
        fAux=padreA.freqs_[pos];
        iAux=padreA.indexes_[pos];
        
        padreA.freqs_[pos]=padreB.freqs_[pos];
        padreA.indexes_[pos]=padreB.indexes_[pos];
        
        padreB.freqs_[pos]=fAux;
        padreB.indexes_[pos]=iAux;
    }
}

/**
 * Algoritmo de <b>cruce BLX</b>. Intercambia la frecuencia de los individuos por un valor intermedio entre ellos con un factor de aleatoriedad
 * @param padreA Especimen padreA
 * @param padreB Especimen padreB
 * @param alpha Porcentaje de reducción del intervalo. 0,5 por defecto
 */

void cruceBlx(Especimen &padreA, Especimen &padreB,float alpha){
    
    for (int transistor = 0; transistor < padreA.freqs_.size(); ++transistor)
    {
        int max,min;
        
        float intervalo;
    
        intervalo=abs(padreA.indexes_[transistor]-padreB.indexes_[transistor])*alpha;
        max=std::max<int>( padreA.indexes_[transistor], padreB.indexes_[transistor]);
        min=std::min<int>( padreA.indexes_[transistor], padreB.indexes_[transistor]);
        max += intervalo;
        min -= intervalo;
        max=std::min<int>(max, padreA.indexes_.size()-1);
        min=std::max<int>(min,0);
        if(intervalo > 0)
        {
           
                padreA.indexes_[transistor]=getRandomInt(min,max);
                padreB.indexes_[transistor]=getRandomInt(min,max);
                padreA.freqs_[transistor]=(*padreA.transistors_) [transistor][padreA.indexes_[transistor]];
                padreB.freqs_[transistor]=(*padreB.transistors_) [transistor][padreB.indexes_[transistor]];
        }



    }
}

/**
 * Muta las frecuencias de un individuo de manera aleatoria
 * @param individuo
 * @param probabilidad probabilidad de mutacion. 0.1 por defecto (1 = 100%)
 */
void mutar(Especimen &individuo, double probabilidad){
    
    // Calculamos esperanza matematica
    int espMat = (int)(individuo.freqs_.size()-1)*probabilidad;
    
    // Si la esperanza matematica es 0, se opta por el metodo tradicional
    if (espMat == 0)
        for(int i=0; i< individuo.freqs_.size();++i){
            if( (double)( rand() / RAND_MAX) <= probabilidad){
                individuo.indexes_[i] = getRandomInt(0,individuo.indexes_.size()-1);
                individuo.freqs_[i] = (*individuo.transistors_) [i][individuo.indexes_[i]];
            }
        }
    else {
        for (int i = 0; i < espMat; ++i) {
            int mutado = getRandomInt(0, individuo.freqs_.size()-1);
            individuo.indexes_[mutado] = getRandomInt(0,individuo.indexes_.size()-1);
            individuo.freqs_[mutado] = (*individuo.transistors_) [i][individuo.indexes_[i]];
        }
    }
}

int Especimen::getFreqRange(int trans)
{
    return (*transistors_)[trans].getFreqRange();
}


int Especimen::getSize()
{
    return transistors_->size();
}
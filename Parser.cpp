
#include "Parser.hpp"

/**
 * Genera una matriz con los diferentes rangos de frecuencias proporcionados por
 * "dom.txt"
 * @param path
 * @param results
 */
void Parser::FRangeParse(std::string path,
                         std::vector<std::vector<int>>& results)
{
    std::ifstream input_file;
    input_file.open(path);
    if(!input_file.good())
        throw std::domain_error("File not found");

    std::string currentLine; 
    int indx_line = 0;
    while(std::getline(input_file, currentLine))
    {
        if(currentLine == " ")
            continue;
        std::string index, frec;
        std::stringstream iss(currentLine);
        iss >> index;
        
        results.push_back(*(new std::vector<int>()));
        do {
            iss >> frec;
            int frec_n = std::stoi(frec);
            results[indx_line].push_back(frec_n);

        }  while(iss);
        ++indx_line;
    }
}

/**
 * A partir del archivo "var.txt", genera un vector de transistores 
 * @param path
 * @param frecs
 * @param result
 * @param TNumber
 * @return El numero total de transistores generado
 */
int Parser::TParse(std::string path,
                   std::vector<std::vector<int>>* frecs,
                   std::vector<Transistor>& result, int TNumber)
{
    std::ifstream input_file;
    input_file.open(path);
    if(!input_file.good())
        throw std::domain_error("File not found");

    std::string currentLine;
    int indx_trans = 0;
    while(std::getline(input_file, currentLine) && indx_trans < TNumber)
    {
        int  trans, nRange;
        std::stringstream iss(currentLine);

        if(currentLine == " ")
            continue;

        iss >> trans;
        iss >> nRange;

        indx_trans = trans;

        Transistor aux(trans, nRange, frecs);
        result.push_back(aux);

    }

    if (indx_trans < TNumber)
        return indx_trans;
    return TNumber;
}

/**
 * Genera la lista de restricciones a partir del archivo "ctr.txt"
 * @param path
 * @param result
 * @param TNumber
 * @return El numero de transistores considerados
 */
int Parser::RTParse(std::string path, std::vector<Restriction>& restrictions)
{
    std::ifstream input_file;
    input_file.open(path);
    if(!input_file.good())
        throw std::domain_error("File not found");

    std::string currentLine;
    while(std::getline(input_file, currentLine))
    {
        int  trans1, trans2, bound, interference;
        std::string letter, mock;
        std::stringstream iss(currentLine), mockstream(currentLine);
        mockstream >> mock;
        mockstream >> mock;
        if(currentLine == " " || !mockstream)
            continue;

        iss >> trans1;
        iss >> trans2;
        
        iss >> letter;
        
        if(letter == "D")
            continue;
        
        iss >> letter;
        
        iss >> bound;
        iss >> interference;
        
        Restriction aux; aux.trans1 = trans1; aux.trans2 = trans2;
        aux.bound = bound; aux.interference = interference;
        
        restrictions.push_back(aux);
    }
}
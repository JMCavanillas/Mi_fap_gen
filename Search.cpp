#include "Search.hpp"

void Search::genIndexTransRestr(std::vector<Transistor>& transistors_, 
                std::vector<Restriction>& restrictions_, std::vector<int>& result)
{
    int k = 0;
    for(int i = 0; i < transistors_.size() && k <= restrictions_.size(); ++i)
    {
        result.push_back(k);
        while (restrictions_[k].trans1 == i)
            ++k;
        
    }
}


#include "Model.h"

Model::Model(const std::string &fileName){
    file = fileName;
    std::ifstream input_strem(fileName);
    if (!input_strem.is_open()){
        std::cout << "File " << file <<" not found!" << std::endl;
    }
    unsigned char c;
    while (input_strem.get(reinterpret_cast<char&>(c))){
        freq[(unsigned int)c]+=1;
    }
    input_strem.close();
    for(std::map<unsigned int,unsigned int>::iterator it = freq.begin(); it != freq.end(); ++it){
        keys.push_back(it->first);
    }
    unsigned sum = 1;
    unsigned sum_old = sum;
    for(auto k: keys){
        sum += freq[k];
        p[k].lower=sum_old;
        p[k].upper=sum;
        sum_old = sum;
    }
    size = sum;
}

void Model::print_intervals(){
    std::cout << "Intervals of Model: " << file << std::endl;
    std::cout << std::endl;
    std::cout << "key: lower, upper" << std::endl;
    for(auto k:keys){
        std::cout << (char)k << ": " << p[k].lower << ", " << p[k].upper << std::endl;
    }
    std::cout << std::endl;
}


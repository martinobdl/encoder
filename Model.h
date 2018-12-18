#ifndef MODEL_H_
#define MODEL_H_

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include "Interval.h"

class Model{
    private:
        std::string file;
        std::map<unsigned int,unsigned int> freq;
        std::map<unsigned int,Interval> p;
        std::vector<unsigned int> keys;
        size_t size;
    public:
        Model(const std::string &fileName);
        Interval get_interval(const unsigned char &c){
            return p[(unsigned int)c];
        }
        size_t get_count(){return size;}
        void print_intervals();
};

#endif

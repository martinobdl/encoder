#include "Decompressor.h"

unsigned char Decompressor::get_char(const unsigned long long int &low, const unsigned long long int &value, const unsigned long long int &high){
    std::vector<unsigned int> chars = model.get_keys();
    unsigned long long int l = high - low;
    for (auto c: chars){
        Interval p = model.get_interval(c);
        unsigned long long int high_tmp = low + (l * p.upper)/model.get_count();
        unsigned long long int low_tmp = low + (l * p.lower)/model.get_count();
        if(low_tmp <= value && value < high_tmp)
            return c;
    }
    return chars[0];
}

void Decompressor::decompress(){
    struct SP{
        unsigned long long int PRECISION;
        unsigned long long int HALF;
        unsigned long long int MAX;
        unsigned long long int QUARTER;
        unsigned long long int TQUARTER;
    };
    int p = 28;
    SP SPECS;
    SPECS.PRECISION = p;
    SPECS.MAX = pow(2,p);
    SPECS.HALF = pow(2,p-1);
    SPECS.QUARTER = pow(2,p-2);
    SPECS.TQUARTER = 3*pow(2,p-2);
    unsigned long long int high = SPECS.MAX;
    unsigned long long int low = 0;
    unsigned long long int value = 0;
    bool bit;
    // float f = 0xFFFFFFFFU;
    for(int i=0; i<SPECS.PRECISION; i++){
        read_stream >> bit;
        value<<=1;
        value += bit;
    }
    //std::cout << value << std::endl;
    for(int j=0; j<model.get_count()-1; j++){
        unsigned long long int l = high - low;
        unsigned int c = get_char(low,value,high);
        Interval p = model.get_interval(c);
        write_stream << (unsigned char)c;
        high = low + (l * p.upper)/model.get_count();
        low = low + (l * p.lower)/model.get_count();
        //std::cout << std::endl<< (unsigned char)c <<" - "<< j << std::endl;
        for( ; ; ){
            //std::cout << low << ", " << value << ", " << high << std::endl;
            if(high < SPECS.HALF){
                low <<=1;
                high <<=1;
                value <<=1;
                read_stream >> bit;
                value += bit;
            }
            else if(low >= SPECS.HALF){
                low = 2*(low-SPECS.HALF);
                high = 2*(high-SPECS.HALF);
                value = 2*(value-SPECS.HALF);
                read_stream >> bit;
                value += bit;
            }
            else if(low>SPECS.QUARTER && high<SPECS.TQUARTER){
                low = 2*(low-SPECS.QUARTER);
                high = 2*(high-SPECS.QUARTER);
                value = 2*(value-SPECS.QUARTER);
                read_stream >> bit;
                value += bit;
            }
            else{
                break;
            }
        }
    }
    write_stream << "\n";
    write_stream.close();
}

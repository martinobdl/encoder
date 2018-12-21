#include "Decompressor.h"

unsigned char Decompressor::get_char(const unsigned int &count){
    std::vector<unsigned int> chars = model.get_keys();
    for (auto i = chars.rbegin(); i != chars.rend(); ++i){
        unsigned int ll = model.get_interval(*i).lower;
        if(ll <= count){
            return *(i);
        }
    }
    return chars[0];
}

void Decompressor::decompress(){
    unsigned int high = 0xFFFFFFFFU;
    unsigned int low = 0;
    unsigned value = 0;
    bool bit;
    float f = 0xFFFFFFFFU;
    for(int i=0; i<32; i++){
        read_stream >> bit;
        value<<=1;
        value += bit;
    }
    std::cout << value << std::endl;
    for(int j=0; j<model.get_count(); j++){
        unsigned int l = high - low;
        unsigned int count = ((value - low) * model.get_count())/l;
        unsigned int c = get_char(count);
        Interval p = model.get_interval(c);
        write_stream << (unsigned char)c;
        high = low + (l/model.get_count())*p.upper-1;
        low = low + (l/model.get_count())*p.lower;
        std::cout << std::endl<< (unsigned char)c <<"-"<< j << std::endl;
        for( ; ; ){
            std::cout << low << ", " << value << ", " << high <<" --> "<< count << std::endl;
            if(high < 0x80000000U){
                low <<=1;
                high <<=1;
                high += 1;
                value <<=1;
                read_stream >> bit;
                value += bit;
            }
            else if(low >= 0x80000000U){
                low <<=1;
                high <<=1;
                high += 1;
                value <<=1;
                read_stream >> bit;
                value += bit;
            }
            else{
                break;
            }
        }
    }
}

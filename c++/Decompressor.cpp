#include "Decompressor.h"

unsigned char Decompressor::get_char(const unsigned int &count){
    std::vector<unsigned int> chars = model.get_keys();
    for (auto i = chars.rbegin(); i != chars.rend(); ++i){
        unsigned int ll = model.get_interval(*i).lower;
        if(ll < count){
            return *i;
        }
    }
}


void Decompressor::decompress(){
    unsigned int high = 0xFFFFFFFFU;
    unsigned int low = 0;
    unsigned char c;
    unsigned value = 0;
    bool bit;
    for(int i=0; i<32; i++){
        read_file >> bit;
        value<<=1;
        value += bit;
    }
    for(int j=0; j<model.get_count(); j++){
        unsigned int l = high - low;
        unsigned int count = ((value - low) * model.get_count() - 1)/l;
        unsigned int c = get_char(count);
        Interval p = model.get_interval(c);
        write_stream << (unsigned char)c;
        high = low + (l/model.get_count())*p.upper-1;
        low = low + (l/model.get_count())*p.lower;
        for( ; ; ){
            //std::cout << low/f << ", " << high/f << std::endl;
            if(high < 0x80000000U){
                low <<=1;
                high <<=1;
                high += 1;
                value <<=1;
                read_file >> bit;
                value += bit;
            }
            else if(low >= 0x80000000U){
                low <<=1;
                high <<=1;
                high += 1;
                value <<=1;
                read_file >> bit;
                value += bit;
            }
            // else if(low >= 0x40000000U && high < 0xC0000000U){
            //     pending_bits ++;
            //     low <<= 1;
            //     low &=0x7FFFFFFF;
            //     high <<=1;
            //     high|=0x80000001;
            // }
            else{
                break;
            }
        }
    }
}

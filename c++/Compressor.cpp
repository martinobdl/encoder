#include "Compressor.h"

void Compressor::output_bits(const bool &bit, int pending_bits){
    output_stream << bit;
    while(pending_bits--){
        output_stream << !bit;
    }
}

void Compressor::compress(){
    int pending_bits = 0;
    unsigned int high = 0xFFFFFFFFU;
    unsigned int low = 0;
    unsigned char c;
    int j=0;
    while (input_stream.get(reinterpret_cast<char&>(c))){
        unsigned int l = high - low;
        Interval p = model.get_interval(c);
        high = low + (l/model.get_count())*p.upper-1;
        low = low + (l/model.get_count())*p.lower;
        // bool check = true;
        std::cout << std::endl<< c <<"-"<< j << std::endl;
        j++;
        float f = 0xFFFFFFFFU;
        for( ; ; ){
            std::cout << low << ", " << high << std::endl;
            if(high < 0x80000000U){
                output_bits(0,pending_bits);
                low <<=1;
                high <<=1;
                high += 1;
            }
            else if(low >= 0x80000000U){
                output_bits(1,pending_bits);
                low <<=1;
                high <<=1;
                high += 1;
            }
            else{
                break;
            }
        }
    }
    output_bits(1,pending_bits);
    output_stream.close();
}

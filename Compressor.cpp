#include "Compressor.h"

void Compressor::output_bit(const bool &bit){
    std::cout << bit << std::endl;
    if (bit)
        bit_buffer |= (1<<bit_in_buffer);
    bit_in_buffer++;
    if (bit_in_buffer == 8){
        output_stream << bit_buffer;
        bit_in_buffer = 0;
        bit_buffer = 0;
    }
}

void Compressor::output_bits(const bool &bit, int pending_bits){
    output_bit(bit);
    while(pending_bits--){
        output_bit(!bit);
    }
}

void Compressor::compress(){
    int pending_bits = 0;
    unsigned int high = 0xFFFFFFFFU;
    unsigned int low = 0;
    unsigned char c;
    while (input_stream.get(reinterpret_cast<char&>(c))){
        unsigned int l = high - low;
        Interval p = model.get_interval(c);
        high = low + (l/model.get_count())*p.upper-1;
        low = low + (l/model.get_count())*p.lower;
        bool check = true;
        std::cout << std::endl<< c << std::endl;
        float f = 0xFFFFFFFF;
        for( ; ; ){
            std::cout << low/f << ", " << high/f << std::endl;
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
    output_bits(1,pending_bits);

}

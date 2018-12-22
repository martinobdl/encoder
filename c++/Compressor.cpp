#include "Compressor.h"

void Compressor::output_bits(const bool &bit, int pending_bits){
    output_stream << bit;
    while(pending_bits--){
        output_stream << !bit;
    }
}

void Compressor::compress(){
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
    int pending_bits = 0;
    unsigned long long int high = SPECS.MAX;
    unsigned long long int low = 0;
    unsigned char c;
    int j=0;
    while (input_stream.get(reinterpret_cast<char&>(c))){
        unsigned long long int l = high - low;
        Interval p = model.get_interval(c);
        high = low + (l * p.upper)/model.get_count();
        low = low + (l * p.lower)/model.get_count();
        // bool check = true;
        //std::cout << std::endl<< c <<" - "<< j << std::endl;
        j++;
        for( ; ; ){
            //std::cout << low << ", " << high << std::endl;
            if(high < SPECS.HALF){
                output_bits(0,pending_bits);
                low <<=1;
                high <<=1;
                pending_bits = 0;
            }
            else if(low >= SPECS.HALF){
                output_bits(1,pending_bits);
                low = 2*(low-SPECS.HALF);
                high = 2*(high-SPECS.HALF);
                pending_bits = 0;
            }
            else if(low>SPECS.QUARTER && high<SPECS.TQUARTER){
                pending_bits++;
                low = 2*(low-SPECS.QUARTER);
                high = 2*(high-SPECS.QUARTER);
            }
            else{
                break;
            }
        }
    }
    pending_bits ++;
    (high < SPECS.QUARTER) ? output_bits(0,pending_bits): output_bits(1,pending_bits);
    output_stream.close();
    input_stream.close();
}

#include "Read_bit.h"

Read_bit::Read_bit(const std::string &fileName){
    read_stream.open(fileName);
    if(!read_stream.is_open()){
        std::cerr << "No file found!" << std::endl;
    }
    buffer=0;
    bits_in_buffer=0;
}

void Read_bit::operator>>(bool &bit){
    bit=0;
    if(!read_stream.eof()){
        if(bits_in_buffer==0){
            c=read_stream.get();
            bits_in_buffer = 8;
        }
        bit = c >> (CHAR_BIT-1);
        bits_in_buffer--;
        c<<=1;
        c&=0xFF;
    }
    return;
}

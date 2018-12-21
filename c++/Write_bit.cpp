#include "Write_bit.h"

Write_bit::Write_bit(const std::string &fileName){
    write_stream.open(fileName);
    buffer=0;
    bits_in_buffer=0;
}

void Write_bit::operator<<(const bool &bit){
    if (bit)
        buffer |= (1<<(CHAR_BIT-(bits_in_buffer+1)));
    bits_in_buffer++;
    //std::cout << bit << "\t" << bits_in_buffer_in << std::endl;
    if (bits_in_buffer == CHAR_BIT){
        //std::cout << buffer_in << std::endl;
        write_stream << buffer;
        bits_in_buffer = 0;
        buffer = 0;
    }
    return;
}

void Write_bit::close(){
    for(int i=bits_in_buffer; i<CHAR_BIT;i++){
        this->operator<<(0);
    }
    write_stream<<"\x0a";
    write_stream.close();
    return;
}

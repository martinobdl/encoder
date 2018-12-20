#include "Bitio.h"

Bitio::Bitio(const std::string &fileName, const std::string &m){
    mode = m;
    if(mode!="w" && mode!="r"){
        std::cerr << "Mode is either write write ('w') or read ('r')." << std::endl;
        return;
    }
    (mode=="w") ? write_stream.open(fileName): read_stream.open(fileName);
    if(mode=="r" && !read_stream.is_open()){
        std::cerr << "File to read doesn't exist!" << std::endl;
        return;
    }
    buffer_in=0;
    bits_in_buffer_in=0;
    buffer_out=0;
    bits_in_buffer_out=0;
    c = 0;
}

void Bitio::operator<<(const bool &bit){
    if (bit)
        buffer_in |= (1<<(CHAR_BIT-(bits_in_buffer_in+1)));
    bits_in_buffer_in++;
    //std::cout << bit << "\t" << bits_in_buffer_in << std::endl;
    if (bits_in_buffer_in == CHAR_BIT){
        //std::cout << buffer_in << std::endl;
        write_stream << buffer_in;
        bits_in_buffer_in = 0;
        buffer_in = 0;
    }
    return;
}

void Bitio::operator>>(bool &bit){
    if(read_stream.is_open()){
        if (bits_in_buffer_out==0){
            c = read_stream.get();
            bits_in_buffer_out=CHAR_BIT;
        }
        bits_in_buffer_out--;
        bit = (c >> CHAR_BIT-1) & 1;
        //std::cout << (int)c << std::endl;
        c<<=1;
        c&=0XFF;
    }
    return;
}

void Bitio::close(){
    if(mode == "w"){
        for(int i=bits_in_buffer_in; i<CHAR_BIT;i++){
            this->operator<<(0);
        }
    }
    return;
}

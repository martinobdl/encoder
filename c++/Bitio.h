#ifndef BITIO_H_
#define BITIO_H_

#include <string>
#include <fstream>
#include <iostream>
#include <limits.h>

class Bitio{
private:
    std::string fileName;
    std::string mode;
    std::ofstream write_stream;
    std::ifstream read_stream;
    unsigned char c;
    unsigned char buffer_in;
    int bits_in_buffer_in;
    unsigned char buffer_out;
    int bits_in_buffer_out;
public:
    Bitio(const std::string &fileName, const std::string &mode);
    void operator<<(const bool &bit);
    void operator>>(bool &bit);
    void close();
};

#endif

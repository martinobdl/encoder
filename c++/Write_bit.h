#ifndef WRITE_BIT_H_
#define WRITE_BIT_H_

#include <string>
#include <fstream>
#include <iostream>
#include <limits.h>

class Write_bit{
private:
    std::string fileName;
    std::ofstream write_stream;
    unsigned char buffer;
    unsigned int bits_in_buffer;
public:
    Write_bit(const std::string &fileName);
    void operator<<(const bool &bit);
    void close();
};

#endif

#ifndef READ_BIT_H_
#define READ_BIT_H_

#include <string>
#include <fstream>
#include <iostream>
#include <limits.h>

class Read_bit{
private:
    std::string fileName;
    std::ifstream read_stream;
    char c;
    unsigned char buffer;
    unsigned short bits_in_buffer;
    bool finished;
public:
    Read_bit(const std::string &fileName);
    void operator>>(bool &bit);
    void close();
};

#endif

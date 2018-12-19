#ifndef DECOMPRESSOR_H_
#define DECOMPRESSOR_H_

#include "Model.h"
#include "Interval.h"

class Decompressor{
    private:
        std::string fileName;
        Model model;
        Bitio read_file;
        std::ofstream write_stream;
    public:
        Decompressor(const std::string &fileName, Model &m):
        fileName(fileName),
        model(m),
        read_file(fileName,"r"),
        write_stream(fileName.substr(0,fileName.find_last_of('.'))+".decoded")
        {};
        void decompress();
        unsigned char get_char(const unsigned int &count);
};

#endif

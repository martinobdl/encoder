#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_

#include "Model.h"

class Compressor{
    private:
        std::string fileName;
        Model model;
        std::ifstream input_stream;
        Bitio output_stream;
    public:
        Compressor(const std::string &fileName, const Model &model):
            fileName(fileName),
            model(model),
            input_stream(fileName),
            output_stream(fileName.substr(0,fileName.find_last_of('.'))+".code","w")
            {};
        void compress();
        void output_bit(const bool &);
        void output_bits(const bool &, int pending_bytes);
};

#endif

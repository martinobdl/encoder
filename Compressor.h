#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_

#include "Model.h"

class Compressor{
    private:
        std::string fileName;
        Model model;
        unsigned char bit_buffer;
        int bit_in_buffer;
        std::ifstream input_stream;
        std::ofstream output_stream;
    public:
        Compressor(const std::string &fileName):
            fileName(fileName),
            model(fileName),
            bit_buffer(0),
            bit_in_buffer(0),
            input_stream(fileName),
            output_stream(fileName+"ark")
            {};
        void compress();
        void output_bit(const bool &);
        void output_bits(const bool &, int pending_bytes);
};

#endif

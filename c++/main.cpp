#include "Model.h"
#include "Compressor.h"
#include "Decompressor.h"
#include "Bitio.h"

int main(){
    std::string fileName = "enwiki6.txt";
    Model m(fileName);
    //m.print_intervals();
    // Compressor c(fileName,m);
    // c.compress();
    std::string fileNameCompr = "enwiki6.code";
    Decompressor d(fileNameCompr,m);
    d.decompress();
    return 0;
}

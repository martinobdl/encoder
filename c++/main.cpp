#include "Model.h"
#include "Compressor.h"
#include "Decompressor.h"
#include "Write_bit.h"

int main(){
    std::cout << "------- compressing -------" << std::endl;
    std::string fileName = "MobyDick.txt";
    Model m(fileName);
    // m.print_intervals();
    Compressor c(fileName,m);
    c.compress();
    std::cout << "------ decompressing ------" << std::endl;
    std::string fileNameCompr = "MobyDick.code";
    Decompressor d(fileNameCompr,m);
    d.decompress();
    return 0;
}

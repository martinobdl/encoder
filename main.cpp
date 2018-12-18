#include "Model.h"
#include "Compressor.h"

int main(){
    std::string fileName = "enwiki6.txt";
    Model m(fileName);
    m.print_intervals();
    Compressor c(fileName);
    c.compress();
    return 0;
}

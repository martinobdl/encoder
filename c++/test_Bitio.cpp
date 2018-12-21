#include "Write_bit.h"
#include "Read_bit.h"

/*
Bitio_test.txt needs to exists. Change!
*/

int main(){
   // Write_bit write_stream("test.txt");
   // write_stream<<0;
   // write_stream<<1;
   // write_stream<<0;
   // write_stream.close();

    bool bit;
    Read_bit read_stream("test.txt");
    for(int i=0; i<40; i++){
        read_stream >> bit;
        std::cout << bit;
    }
    std::cout  << std::endl;
    return 0;
}

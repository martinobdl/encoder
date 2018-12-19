#include "Bitio.h"

/*
Bitio_test.txt needs to exists. Change!
*/

int main(){
    Bitio write_stream("Bitio_test_write.txt","w");
    write_stream<<0;
    write_stream<<1;
    write_stream<<0;
    write_stream.close();

    bool bit;
    Bitio read_stream("Bitio_test_read.txt","r");
    for(int i=0; i<8; i++){
        read_stream >> bit;
        std::cout << bit << std::endl;
    }
    read_stream.close();
    return 0;
}

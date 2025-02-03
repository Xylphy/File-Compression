#include <iostream>
#include "huffman_codes.h"

int main(){
    std::string text = "aaaaaaaaaaeeeeeeeeeeeeeeeiiiiiiiiiiiissstttt             \n";
    HuffmanCodes hc(text);
    hc.build();
    std::cout << hc << std::endl;
    return 0;
}
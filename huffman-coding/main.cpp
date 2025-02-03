#include <iostream>
#include <string>
#include "huffman_codes.h"

int main(){
    std::string text = "aaaaaaaaaaeeeeeeeeeeeeeeeiiiiiiiiiiiissstttt             \n";
    HuffmanCodes hc(text);
    hc.build();
    std::string encoded = hc.encode();
    std::cout << encoded << '\n';
    std::string decoded = hc.decode(encoded);
    std::cout << decoded << '\n';
    return 0;
}
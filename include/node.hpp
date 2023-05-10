#include <iostream>
#include <unordered_map>

class Node {
public:
    char caracter;
    int code;
    std::unordered_map<char, Node*> children; // Armazena os filhos de determinado nó

    Node(char caracter, int code) {
        this->caracter = caracter;
        this->code = code;
    }
};
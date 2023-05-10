#include <iostream>
#include <unordered_map>

#include "node.hpp"

class Trie {
public:
    Node* root;
    double nextCode;

    Trie() {
        root = new Node('\0', 0);
        nextCode = 1;
    }

    double insert(std::string word); // Insere uma nova palavra na árvore
    double find(std::string word); // Procura se a palavra passada  se encontra na ́arvore
};
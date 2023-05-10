#include "trie.hpp"

double Trie::insert(std::string word) {
    Node *node = root;
    int prefixCode = 0;

    for (char c : word)
    {
        if (node->children.find(c) != node->children.end())
        {
            node = node->children[c];
            prefixCode = node->code;
        }
        else
        {
            Node *newNode = new Node(c, nextCode);
            node->children[c] = newNode;
            nextCode++;
            return prefixCode;
        }
    }

    return prefixCode;
}

double Trie::find(std::string word) {
    Node *node = root;

    for (char c : word)
    {
        if (node->children.find(c) != node->children.end())
        {
            node = node->children[c];
        }
        else
        {
            return -1;
        }
    }

    return node->code;
}

#include <fstream>
#include <vector>
#include "trie.hpp"

using namespace std;

std::pair<double,double>compression(string filename, string output); // Função responsável pela compressão
void decompression(string filename, string output); // Função responsável pela descompressão
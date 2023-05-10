#include "lz78.hpp"

/*
Realiza a compressão e retorna uma tupla com os valores de referência para a criação
do relatório teórico de compressão. Utiliza a leitura e escrita nos arquivos de entrada
e algumas variáveis extras.
*/ 
std::pair<double,double>compression(string filename, string output) {
    Trie tree;
    double highestCode = 0;

    ifstream inputFile(filename);
    ofstream outputFile(output);

    string pattern = "";
    outputFile << '|';

    double prefixCode = 0;

    while (true)
    {
        char c;
        inputFile.get(c);

        pattern += c;
        prefixCode = tree.find(pattern);

        if (prefixCode != -1)
        {
            continue;
        }
        else
        {
            prefixCode = tree.insert(pattern);

            if (prefixCode > highestCode)
            {
                highestCode = prefixCode;
            }

            outputFile << prefixCode << '^' << c << '|';
            pattern = "";
        }

        if (inputFile.eof())
        {
            break;
        }
    }

    if (pattern != "")
    {
        if (prefixCode > highestCode)
        {
            highestCode = prefixCode;
        }
        outputFile << prefixCode << '^' << pattern.back() << '|';
    }

    inputFile.close();
    outputFile.close();
    return std::make_pair(tree.nextCode, highestCode);
}


/*
Realiza a descompressão do arquivo comprimido.
Utiliza a leitura e escrita nos arquivos de entrada
e algumas variáveis extras.
*/ 
void decompression(string filename, string output) {
    ifstream inputFile(filename);
    ofstream outputFile(output);

    string input((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));

    inputFile.close();

    vector<std::string> parts;
    double pos = 1;

    while (pos != string::npos)
    {
        double endPos = input.find('|', pos + 1);
        if (endPos == string::npos)
        {
            break;
        }
        string part = input.substr(pos, endPos - pos);
        parts.push_back(part);
        pos = endPos + 1;
    }

    vector<pair<int, char>> encodedData;

    for (auto &part : parts)
    {
        double separatorPos = part.find('^');
        if (separatorPos == string::npos)
        {
            continue;
        }
        int index = stoi(part.substr(0, separatorPos));
        char c = part[separatorPos + 1];
        encodedData.emplace_back(index, c);
    }

    vector<string> decodedData;
    decodedData.push_back("");

    for (auto &item : encodedData)
    {
        string str = decodedData[item.first] + item.second;
        decodedData.push_back(str);
        outputFile << str;
    }

    outputFile.close();
}
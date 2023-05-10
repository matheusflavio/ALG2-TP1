#include "lz78.hpp"
#include <filesystem>
#include <cmath>
#include <tuple>

/* Função que retorna uma menssagem de erro caso seja passada alguma opção inválida */
void opcaoInvalida() {
    std::cout << "Opção inválida" << std::endl;
}

// Função responsável por criar o relatório de compressão de imprimir no console
void compressionReport(string inputName, std::pair<double,double>values) {
    std::filesystem::path filePath(inputName);
    std::uintmax_t fileSize = std::filesystem::file_size(filePath);
    std::size_t fileSizeBits = fileSize * 8;
    
    double compressionSize = values.first * values.second * 8;

    std::cout << "O arquivo original tem tamanho em bits: " << fileSizeBits << std::endl;
    std::cout << "O arquivo comprimido tem tamanho em bits: " << compressionSize << std::endl;
    std::cout << "A taxa de compressão é de " << compressionSize/fileSizeBits*100 << "%" << std::endl;

}

int main(int argc, char *argv[]) {
    /* Declarando variáveis */
    std::string option = argv[1];
    std::string inputName = argv[2];
    std::string defineOutput = "";
    std::string outputName = "";

    /* Lidando com o nome do arquivo de saída */
    if (argc > 3) {
        defineOutput = argv[3];
        outputName = argv[4];
        if(outputName == "" || defineOutput != "-o") {
            opcaoInvalida();
            return -1;
        }
    }
    else {
        outputName = inputName.substr(0, inputName.size()-4) + ".z78";
    }

    if (option == "-c") {
        /* Compressão do arquivo de entrada */
        std::pair<double,double> values = compression(inputName, outputName);
        compressionReport(inputName, values);
    }
    else if (option == "-x") {
        /* Descompressão do arquivo de entrada */
        decompression(inputName, outputName);
    }
    else {
        opcaoInvalida();
    }

    return 0;
}
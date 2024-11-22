#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input.txt." << std::endl;
        return 1; // Exit with an error code
    }

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output.txt." << std::endl;
        return 1; // Exit with an error code
    }

    std::string line;
    int wordCount = 0;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            wordCount++;
        }
    }

    outputFile << "Word count: " << wordCount << std::endl;

    inputFile.close();
    outputFile.close();

    std::cout << "Word count: " << wordCount << " words written to output.txt." << std::endl;

    return 0;
}


#include <iostream>

#include <fstream>

#include <string>

 

int main() {

    std::ifstream file("sample.txt");

    if (!file.is_open()) {

        std::cerr << "Error: File not found!\n";

        return 1;

    }

 

    std::string line;

    while (std::getline(file, line)) {

        std::cout << line << "\n";

    }

 

    file.close();

    return 0;

}
/**
 * Jippitied from the original Go script.
 */
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

const int INDENT = 4;

void readMemory(std::istream &stream) {
  char buffer[4];

  while (stream.read(buffer, sizeof(buffer))) {
    std::ostringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    for (size_t i = 0; i < sizeof(buffer); ++i) {
      hexStream << std::setw(2)
                << static_cast<unsigned int>(
                       static_cast<unsigned char>(buffer[i]));
    }

    std::cout << std::setw(INDENT) << ""
              << "x\"" << hexStream.str() << "\",\n";
  }

  if (!stream.eof()) {
    std::cerr << "Error reading from input stream\n";
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    readMemory(std::cin);
  } else {
    std::ifstream inputFile(argv[1], std::ios::binary);
    if (!inputFile.is_open()) {
      std::cerr << "Error opening file for reading\n";
      return 1;
    }
    readMemory(inputFile);
  }
  return 0;
}

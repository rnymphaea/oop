#include "../include/File.h"

FileWriter::FileWriter(const std::string& filename) : filename(filename) {
    outfile.open(filename);
    if (!outfile.is_open()) {
        throw std::runtime_error("Невозможно открыть файл для записи: " + filename);
    }
}

FileWriter::~FileWriter() {
    if (outfile.is_open()) {
        outfile.close();
    }
}

std::ofstream& FileWriter::getOutfile() {
    return outfile;
}

FileReader::FileReader(const std::string& filename) : filename(filename) {
    infile.open(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Невозможно открыть файл для чтения: " + filename);
    }
}

FileReader::~FileReader() {
    if (infile.is_open()) {
        infile.close();
    }
}

std::ifstream& FileReader::getInfile() {
    return infile;
}

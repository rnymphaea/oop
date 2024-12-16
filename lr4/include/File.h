#ifndef LR3_FILE_H
#define LR3_FILE_H

#include <fstream>
#include <string>
#include <stdexcept>

class FileWriter {
private:
    std::string filename;
    std::ofstream outfile;
public:
    FileWriter(const std::string& filename);
    ~FileWriter();
    std::ofstream& getOutfile();
};

class FileReader {
private:
    std::string filename;
    std::ifstream infile;
public:
    FileReader(const std::string& filename);
    ~FileReader();
    std::ifstream& getInfile();
};

#endif //LR3_FILE_H

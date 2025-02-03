#ifndef __FILE_OPEN_HPP__
#define __FILE_OPEN_HPP__

#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <filesystem>
#include <iostream>

#include "debug.hpp"

class fileOpen{
private:
    std::string httpPathDir;
    std::unique_ptr<std::fstream> reader;
    std::vector<std::string> allFilesPathVec;

    void listPathFile(bool isIncludeDir=false);
    void listPathFile(const std::string &fileExtensionFilter);
    void readFileContent();

public:
    fileOpen(const std::string &httpPathDir);

    
    
    fileOpen* initLister(bool isIncludeDir=false);
    fileOpen* initLister(const std::string &fileExtensionFilter);
    
    void outputPaths();


    std::vector<std::string>& getAllFilesPathVec();
};


#endif 
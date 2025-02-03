#ifndef __FILE_OPEN_HPP__
#define __FILE_OPEN_HPP__

#include <string>
#include <memory>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "debug.hpp"

class fileOpen{
private:
    static int contentNo;
    
    std::string httpPathDir;
    
    std::unique_ptr<std::ifstream> p_reader;
    std::unique_ptr<std::vector<std::string>> p_contents; //content allfilespath'den sonra baslatilmali

    std::vector<std::string> allFilesPathVec;
    
    void listPathFile(const std::string f_ex = "",bool isIncludeDir=false);

public:
    fileOpen(const std::string &httpPathDir);
    
    fileOpen* initLister(const std::string &f_ex = "",bool isIncludeDir=false);
    
    void outputPaths();
    

    void readFileContent();
    void outputContents(int contentNo);

    std::vector<std::string>& getPathsVec();
    std::vector<std::string>* getContents();

    int getContentCount();
};


#endif 
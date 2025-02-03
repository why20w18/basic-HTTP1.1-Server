#include "../include/fileOpen.hpp"

fileOpen::fileOpen(const std::string &httpPathDir){
    this->httpPathDir  = httpPathDir;
    this->reader = std::make_unique<std::fstream>(httpPathDir,std::ios::in);
    LOG("fileOpen Constructor");
}



void fileOpen::readFileContent(){
}

void fileOpen::listPathFile(bool isIncludeDir){
    LOG("listPathFile Func : Directory Dahil mi = " << ((isIncludeDir) ? "Evet" : "Hayir"));
    namespace fs = std::filesystem; //namespace tanimi

    if(!isIncludeDir)
    for(const auto &record : fs::directory_iterator(this->httpPathDir)){
        if(fs::is_regular_file(record.status())){
            this->allFilesPathVec.push_back(record.path());
        }
    }
    
    else
    for(const auto &r : fs::directory_iterator(this->httpPathDir)){
        this->allFilesPathVec.push_back(r.path());
    }
}


void fileOpen::listPathFile(const std::string &fileExtensionFilter){


}


std::vector<std::string>& fileOpen::getAllFilesPathVec(){

}

void fileOpen::outputPaths(){
    for(auto x : allFilesPathVec)
        std::cout << x << "\n";
}

fileOpen* fileOpen::initLister(bool isIncludeDir){
    fileOpen::listPathFile(isIncludeDir);
    return this;
}
fileOpen* fileOpen::initLister(const std::string &fileExtensionFilter){
    fileOpen::listPathFile(fileExtensionFilter);
    return this;
}
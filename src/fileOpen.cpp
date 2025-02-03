#include "../include/fileOpen.hpp"

fileOpen::fileOpen(const std::string &httpPathDir){
    this->httpPathDir  = httpPathDir;
    
    
    LOG("fileOpen Constructor");
}


void fileOpen::readFileContent(){
    static int contentNo = 0;
    if(this->allFilesPathVec.empty()){
        LOG("readFileContent : ilk once initLister kullanarak dosya yollarini cikart");
        return;
    }

    this->reader = std::make_unique<std::ifstream>();
    contents = std::make_unique<std::vector<std::string>>(allFilesPathVec.size());

    for(const auto &filePath : allFilesPathVec){
        reader->open(filePath);
        
        if(!reader->is_open())
            LOG("readFileContent : dosya acilamadi !");
        
        std::string currentFileContent;
        while(getline(*reader,currentFileContent)){
            contents->at(contentNo).append(currentFileContent+"\n");
        }
        contentNo++;
        reader->close();
    }
    this->contents->shrink_to_fit();
}

void fileOpen::listPathFile(const std::string& f_ex,bool isIncludeDir){
    LOG("listPathFile Func : Directory Dahil mi = " << ((isIncludeDir) ? "Evet" : "Hayir ") 
    << "Uzanti : " << ( (f_ex == "") ? "Tum Uzantilar" : f_ex));
    
    namespace fs = std::filesystem; //namespace tanimi

    if(!isIncludeDir)
    for(const auto &record : fs::directory_iterator(this->httpPathDir)){
        if(fs::is_regular_file(record.status())){
            if(f_ex.empty())
                this->allFilesPathVec.push_back(record.path());
            else if(f_ex == record.path().extension())
                this->allFilesPathVec.push_back(record.path());
        }
    }
    
    else
    for(const auto &r : fs::directory_iterator(this->httpPathDir)){
        if(f_ex.empty())
            this->allFilesPathVec.push_back(r.path());
        else if(f_ex == r.path().extension())
            this->allFilesPathVec.push_back(r.path());
        else 
            this->allFilesPathVec.push_back(r.path());
    }
}

fileOpen* fileOpen::initLister(const std::string& f_ex,bool isIncludeDir){
    this->allFilesPathVec.clear();
    fileOpen::listPathFile(f_ex,isIncludeDir);
    return this;
}

void fileOpen::outputPaths(){
    for(auto x : allFilesPathVec)
        LOG(x);
}

std::vector<std::string>& fileOpen::getPathsVec(){
    return this->allFilesPathVec;
}

void fileOpen::outputContents(int contentNo){
    if(contents->size()-1 >= contentNo){
        LOG("\033[0;32m<---------------- File Content No : "<< contentNo << " --------------->\033[0m");
        LOG(this->contents->at(contentNo));
    }
    else 
        LOG("outputContents : HATALI ERISIM");
}
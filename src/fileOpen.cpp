#include "../include/fileOpen.hpp"
#include "../include/crossDefines.hpp"

int fileOpen::contentNo = 0;

fileOpen::fileOpen(const std::string &httpPathDir){
    this->httpPathDir  = httpPathDir;
    
    
    LOG("fileOpen Constructor");
}


void fileOpen::readFileContent(){
   
    if(this->allFilesPathVec.empty()){
        LOG("readFileContent : ilk once initLister kullanarak dosya yollarini cikart");
        return;
    }

    this->p_reader = std::make_unique<std::ifstream>();
    p_contents = std::make_unique<std::vector<std::string>>(allFilesPathVec.size());

    for(const auto &filePath : allFilesPathVec){
        p_reader->open(filePath);
        
        if(!p_reader->is_open())
            LOG("readFileContent : dosya acilamadi !");
        
        std::string currentFileContent;
        while(getline(*p_reader,currentFileContent)){
            p_contents->at(contentNo).append(currentFileContent+"\n");
        }
        //burada numara ve dosya adlarini mapte tutarsak hangi indexte hangi dosya var erisiriz 
        filenameIndexMap[getJustFilename(filePath)] = contentNo;
        contentNo++;

        p_reader->close();
    }
    this->p_contents->shrink_to_fit();
}

void fileOpen::listPathFile(const std::string f_ex,bool isIncludeDir){
    LOG("listPathFile Func : Directory Dahil mi = " << ((isIncludeDir) ? "Evet" : "Hayir ") 
    << "Uzanti : " << ( (f_ex == "") ? "Tum Uzantilar" : f_ex));
    FOLOG("  Dizinde yayinlacak dosyalari arama bilgisi:\n\t\tDirectory Dahil mi = " << ((isIncludeDir) ? "Evet\n" : "Hayir\n") 
    << "\t\tUzanti = " << ( (f_ex == "") ? "Tum Uzantilar\n" : f_ex+"\n"));
    
    namespace fs = std::filesystem; //namespace tanimi

    if(!isIncludeDir)
    for(const auto &record : fs::directory_iterator(this->httpPathDir)){
        if(fs::is_regular_file(record.status())){
            if(f_ex.empty())
                this->allFilesPathVec.push_back(record.path().string());
            else if(f_ex == record.path().extension())
                this->allFilesPathVec.push_back(record.path().string());
        }
    }
    
    else
    for(const auto &r : fs::directory_iterator(this->httpPathDir)){
        if(f_ex.empty())
            this->allFilesPathVec.push_back(r.path().string());
        else if(f_ex == r.path().extension())
            this->allFilesPathVec.push_back(r.path().string());
        else 
            this->allFilesPathVec.push_back(r.path().string());
    }

    if(this->allFilesPathVec.empty()){
        LOG("listPathFile : aranan dosya uzantisi bulunamadi !");
        FOLOG(this->httpPathDir << "dizininde aranan dosya uzantisi bulunamadi");
        allFilesPathVec.push_back("ARANAN DOSYA UZANTISI BULUNAMADI");
    }
}

fileOpen* fileOpen::initLister(const std::string &f_ex,bool isIncludeDir){
    this->allFilesPathVec.clear();
    fileOpen::listPathFile(f_ex,isIncludeDir);
    return this;
}

void fileOpen::outputPaths(){
    FOLOG(this->httpPathDir << " dizinindeki HTTP serverda yayinlanan dosyalariniz");
    for(auto x : allFilesPathVec)
        FOLOG(x);
}

std::vector<std::string>& fileOpen::getPathsVec(){
    return this->allFilesPathVec;
}

 std::vector<std::string>* fileOpen::getContents(){
    return p_contents.get();
}


void fileOpen::outputContents(int contentNo){
    if(p_contents->size()-1 >= contentNo){
        LOG("\033[0;32m<---------------- File Content No : "<< contentNo << " --------------->\033[0m");
        LOG(this->p_contents->at(contentNo));
    }
    else 
        LOG("outputContents : HATALI ERISIM");
}

int fileOpen::getContentCount(){
    return fileOpen::contentNo;
}

std::string fileOpen::getJustFilename(std::string filepath){
    int startIndex = filepath.find_last_of(DEFAULT_DELIMITER);
    
    if(DEFAULT_OPERATING_SYSTEM == 1) //linux
        filepath = filepath.substr(startIndex);

    else if(DEFAULT_OPERATING_SYSTEM == 2) //win32
        filepath = filepath.substr(++startIndex);

    LOG("FileOpen::getJustFilename Func : |" << filepath << "|");
    return filepath;
}
#include "../include/serverCommands.hpp"

serverCMD::serverCMD(std::string input){
    inputCommand = new std::string(input);
    LOG("serverCMD Constructor input val : " << inputCommand);

    if(setStandartCommand())    
        this->isCMD = isCommand();
    
    if(!isCMD && !inputCommand->empty())
        COLOG("Gecersiz komut girdiniz lutfen yardim icin !help komutunu girin");
}

serverCMD::~serverCMD(){
    delete inputCommand;
    LOG("serverCMD Destructor");
}

bool serverCMD::setStandartCommand(){
    if(inputCommand->empty()){
        COLOG("Bos komut girdiniz yardim icin !help komutu giriniz");
        return false;
    }
    //CASE SENSETIVE DISABLE//
    std::transform(inputCommand->begin(),inputCommand->end(),inputCommand->begin(),::tolower);
    LOG("setStandartCommand Func : " << inputCommand);
    //BOSLUKLARI KALDIRMA//
    trim();
    LOG("setStandartCommand Func trim sonrasi : " << inputCommand);

    return true;
}

bool serverCMD::isCommand(){
   if(inputCommand->at(0) != '!')
        return false;

   std::unordered_map<std::string,int> commandList;
   fillCommandMap(commandList);

   for(const auto &pair : commandList){
       if(pair.first == *inputCommand){
           return true;
       }
   }

    return false;
}

void serverCMD::trim(){
    *inputCommand = inputCommand->substr(inputCommand->find_first_not_of(' '));
    LOG("trim Func 1 : " << inputCommand);
    *inputCommand = inputCommand->substr(0,inputCommand->find_last_not_of(' ')+1);
    LOG("trim Func 2 : " << inputCommand);

}

std::string serverCMD::processCMD(){
    std::unordered_map<std::string,int> commandList;
    fillCommandMap(commandList);

    int value = commandList[*inputCommand];

    std::string responseCMD;
    switch(value){
        case IC_HELP:
            {
                std::string r1 = "\n<::::::::HTTP SERVER IC KOMUTLARI YARDIM SAYFASI::::::::>\n";
                std::string r2 = "!help   : mevcut yardim sayfasini baslatir\n";
                std::string r3 = "!exit   : serveri guvenli sekilde sonlandirir\n";
                std::string r4 = "!info   : mevcut oturum hakkinda bilgi verir\n";
                std::string r5 = "!ofsrc  : serverda yayinlanan mevcut dizin\n";
                std::string r6 = "!offiles: serverda yayinlanan mevcut uzanti ve dosyalar\n";
                std::string r7 = "\n[NOT]   : kullanici komutlari buyuk kucuk harf ve bosluk duyarsizdir\n";

                responseCMD = r1 + r2 + r3 + r4 + r5 + r6 + r7;
            }   
            break;

        case IC_EXIT:
            return "!exit";
        
        case IC_INFO:
        
            break;
        
        case IC_OPENFILE_SOURCE:
        
            break;
        
        case IC_OPENFILE_FILES:

            break;
    }

    return responseCMD;
}

void serverCMD::fillCommandMap(std::unordered_map<std::string,int> &commandList){
  
    commandList.emplace("!exit",IC_EXIT);
    commandList.emplace("!help",IC_HELP);
    commandList.emplace("!info",IC_INFO);
    commandList.emplace("!ofsrc",IC_OPENFILE_SOURCE);
    commandList.emplace("!offiles",IC_OPENFILE_FILES);

    /*
    help,exit,info
    openFile source , openFile files
    */
}

int serverCMD::commandLoop(){
    if(!isCMD){
        return -1;
    }

    std::string responseCMD = processCMD();
    COLOG("Komut ciktisi -> " << responseCMD);

    if(*inputCommand == "!exit"){
        return false;
    }

    return true;
}
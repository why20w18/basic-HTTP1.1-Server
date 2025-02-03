#include "../include/serverCommands.hpp"

serverCMD::serverCMD(std::string &input){
    inputCommand = new std::string(input);    
}

serverCMD::~serverCMD(){
    delete this->inputCommand;
}

std::string& serverCMD::setStandartCommand(){   
    //CASE SENSETIVE DISABLE//
    std::transform(inputCommand->begin(),inputCommand->end(),inputCommand->begin(),::tolower);

    //BOSLUKLARI KALDIRMA//
    trim();

    return *inputCommand;
}

bool serverCMD::isCommand(){
   if(inputCommand->at(0) != '!')
        return false;

    std::vector<std::string> *commandList = createCommandList();
   
   
   for(auto currentCMD : *commandList){
        if(currentCMD == *inputCommand){
            delete commandList;
            return true;
        }
   }
   
    delete commandList; 
    return false;
}

void serverCMD::trim(){
    *inputCommand = inputCommand->substr(inputCommand->find_first_not_of(' '));
    *inputCommand = inputCommand->substr(inputCommand->find_last_not_of(' ')+1);
}

std::string serverCMD::processCMD(){
    std::vector<std::string> *commandList = createCommandList();
    std::string responseCMD("YAZILMADI");

    if(commandList->at(0) == *inputCommand){
        responseCMD = "CIKIS YAPILIYOR";
        return responseCMD;
    }

    else if(commandList->at(1) == *inputCommand){
        return responseCMD;

    }

    else if(commandList->at(2) == *inputCommand){
        return responseCMD;

    }

    else if(commandList->at(3) == *inputCommand){
        return responseCMD;

    }

    else if(commandList->at(4) == *inputCommand){
        return responseCMD;

    }
    else{
        return responseCMD;

    }

    delete commandList;
}

std::vector<std::string>* serverCMD::createCommandList(){
    return new std::vector<std::string>{
        "!h","!e","!i",
        "!ofs","!off"  
        };

    /*
    help,exit,info
    openFile source , openFile files
    */
}

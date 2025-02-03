#ifndef __SERVER_COMMANDS_HPP__
#define __SERVER_COMMANDS_HPP__

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "debug.hpp"

class serverCMD{
private:
    std::string *inputCommand;        

    std::string& setStandartCommand();
    bool isCommand();
    void trim();
    std::string processCMD();

    std::vector<std::string>* createCommandList();

public:
    serverCMD(std::string &input);
    ~serverCMD();

};


#endif
#ifndef __SERVER_COMMANDS_HPP__
#define __SERVER_COMMANDS_HPP__

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "debug.hpp"

enum INPUT_CMD{
    IC_HELP,
    IC_EXIT,
    IC_INFO,
    IC_OPENFILE_SOURCE,
    IC_OPENFILE_FILES
};

class serverCMD{
private:
    std::string *inputCommand;
    bool isCMD;

    bool setStandartCommand();
    bool isCommand();
    void trim();
    std::string processCMD();

    void fillCommandMap(std::unordered_map<std::string,int> &commandList);

public:
    serverCMD(std::string input);
    int commandLoop();
    ~serverCMD();

};


#endif
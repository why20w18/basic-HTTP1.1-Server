#include <iostream>

#include "../include/httpServer.hpp"
#include "../include/serverCommands.hpp"

#include <thread>

using namespace std;

void commandProcessLoop(httpServer *httpServ){
    int commandLoopResponse = 1;
    while(commandLoopResponse){
        string input;
        cout << "[USER-COMMAND] ------->"; 
        getline(cin,input);
        serverCMD *commandP = new serverCMD(input);
        commandLoopResponse = commandP->commandLoop();
        LOG("commandProcessLoop Func is continue : " << ((commandLoopResponse) ? "evet" : "hayir"));
        delete commandP;
    }
    httpServ->httpRun(false);
}


int main(){

//TEST-0//
//    cout << "hello world" << endl;

/*  
    //TEST-1//
    fileOpen fop(".");
    fop.initLister(".sh")->outputPaths();
    cout << "\n\n";
    fop.initLister(".md",false)->outputPaths();
     cout << "\n\n";
    fop.initLister("",true)->outputPaths();
    
    auto pathVec = fop.getPathsVec();
    cout << "\n\nvec:" << pathVec.at(0) << endl;

    fop.getPathsVec().clear();
    fop.readFileContent();
*/

/*
    //TEST-2//
    fileOpen fop("src/http");
    //system("cd");
    fop.initLister()->outputPaths();
    fop.readFileContent();
    

    fop.outputContents(0); //test_bir icerigini bastirdi
    cout << endl;
    fop.outputContents(1); //hatali erisim

    cout << endl;
    fop.outputContents(2); //hatali erisim
    cout << "content count : " << fop.getContentCount() << endl;
*/

/*
    //TEST-3//SERVERI CALISTIRMA YONLENDIRMESIZ//
    fileOpen fop("src/http");
    fop.initLister()->outputPaths();
    fop.readFileContent();

    std::vector<std::string> *contents = fop.getContents();
    int contents_size = fop.getContentCount();
    httpServer httpServer(8090,*contents,contents_size);
    httpServer.httpRun();
*/

    //TEST-4//THREAD//
    httpServer *httpServ = new httpServer(8080,".html");

    std::thread httpServerThread([&httpServ](){
        httpServ->httpRun();
    });

    commandProcessLoop(httpServ);
    httpServerThread.join();
    
    delete httpServ;

    return 0x0;
}
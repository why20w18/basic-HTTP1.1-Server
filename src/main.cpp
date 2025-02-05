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
    
    char userReq;
    SLOGN("Mevcut ayarlarla HTTP Server baslatilsin mi (y/n) :");
    cin >> userReq;

    if(userReq == 'y'){
        fileOpen *fop = new fileOpen(DEFAULT_DIRECTORY);
        fop->initLister()->outputPaths();
        fop->readFileContent();   

        std::vector<std::string> *contents = fop->getContents();
        int contents_size = fop->getContentCount();
        
        httpServer *httpServ = new httpServer(8080,*contents,contents_size,fop->getPathsVec(),fop->filenameIndexMap);
        delete fop;

        std::thread httpServerThread([&httpServ](){
            httpServ->httpRun();
        });
        commandProcessLoop(httpServ);
        httpServerThread.join();
        delete httpServ;
    }
    
    else if(userReq == 'n'){
        unsigned int userDefPort = 8080;
        bool isIncludeDir;

        std::string userDefDirectory;
        std::string userDefFileExtension;
        std::string userDefIncludeDir;
        std::string userDefPortStr;


        SLOGN("(varsayilan olarak kullanmak istediginiz alanlar icin d giriniz)")
        SLOGN("HTTP Serverda yayinlanacak dosyalarin bulundugu dizinin tam konumu (src/http ~ d) =>");
        cin >> userDefDirectory;
        if(userDefDirectory.at(0) == 'd'){
            userDefDirectory = DEFAULT_DIRECTORY;
            SLOGN("HTTP Serverda yayinlanacak dosyalarin bulundugu dizin DEFAULT olarak baslatildi : " << DEFAULT_DIRECTORY);
        }
        
        SLOGN("HTTP Serverda sadece dosyalar mi yayinlanacak (y ~ n ~ d) =>");
        cin >> userDefIncludeDir;
        if(userDefIncludeDir.at(0) == 'd' || userDefIncludeDir.at(0) == 'n')
            isIncludeDir = false;
        else 
            isIncludeDir = true;
        

        SLOGN("HTTP Serverda yayinlanacak dosyalari filtrelemek istiyorsaniz .uzanti seklinde girin (.html ~ d) =>");
        cin >> userDefFileExtension;
        if(userDefFileExtension.at(0) == 'd'){
            userDefFileExtension = "";
            SLOGN("HTTP Serverda yayinlanacak dosyalarin turu DEFAULT tum uzantilar icin baslatildi : " << "tum uzantilar icin baslatildi");
        }

        SLOGN("HTTP Server hangi port uzerinde calissin (8080 ~ d) =>");
        cin >> userDefPortStr;
        if(userDefPortStr.at(0) == 'd'){
            userDefPort = 8080;
            SLOGN("HTTP Server portu DEFAULT olarak baslatildi : " << userDefPort);
        }
        else{
            try{
                userDefPort = std::stoi(userDefPortStr);
            } 
            catch(const std::exception &e){
                SLOGN("Gecersiz port numarasi girildi ! Varsayilan (8080) kullaniliyor : " << e.what());
            }
        }
       
        fileOpen *fop = new fileOpen(userDefDirectory);
        fop->initLister(userDefFileExtension,isIncludeDir)->outputPaths();
        fop->readFileContent();   

        std::vector<std::string> *contents = fop->getContents();
        int contents_size = fop->getContentCount();
        
        httpServer *httpServ = new httpServer(userDefPort,*contents,contents_size,fop->getPathsVec(),fop->filenameIndexMap);
        delete fop;

        std::thread httpServerThread([&httpServ](){
            httpServ->httpRun();
        });
        commandProcessLoop(httpServ);
        httpServerThread.join();
        delete httpServ;
    }

    return 0x0;
}
#include <iostream>

#include "../include/httpServer.hpp"

using namespace std;

int main(){

    cout << "hello world" << endl;
    //system("pwd");
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

    //TEST-3//SERVERI CALISTIRMA YONLENDIRMESIZ//
    fileOpen fop("src/http");
    fop.initLister()->outputPaths();
    fop.readFileContent();

    std::vector<std::string> *contents = fop.getContents();
    int contents_size = fop.getContentCount();
    httpServer httpServer(8090,*contents,contents_size);
    httpServer.httpRun();

    return 0x0;
}
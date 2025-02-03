#include <iostream>
#include <boost/asio.hpp>

#include "../include/fileOpen.hpp"

using namespace std;

int main(){

    cout << "hello world" << endl;

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

    //TEST-2//
    fileOpen fop("src/http");
    fop.initLister()->outputPaths();
    fop.readFileContent();
    fop.outputContents(0); //test_bir icerigini bastirdi
    cout << endl;
    fop.outputContents(1); //hatali erisim

    cout << endl;
    fop.outputContents(2); //hatali erisim



    return 0x0;
}
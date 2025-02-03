#include <iostream>
#include <boost/asio.hpp>

#include "../include/fileOpen.hpp"

using namespace std;

int main(){

    cout << "hello world" << endl;

    fileOpen fop(".");
    fop.initLister()->outputPaths();

    return 0x0;
}
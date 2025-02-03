#ifndef __HTTP_SERVER_HPP__
#define __HTTP_SERVER_HPP__

#include <boost/asio.hpp>
#include <unordered_map>
#include "fileOpen.hpp"

#define SLOG(x) std::cout << "\033[0;32m[HTTP-SERVER-LOG] : \033[0m" << x << "\n";

using namespace boost::asio;

class httpServer{
private:
    uint32_t portNo;
    uint32_t contentSize;

    std::vector<std::string> contents;
    
    std::unique_ptr<boost::asio::io_context> p_io;
    boost::asio::ip::tcp::socket *p_socket;

    //YONLENDIRME KISMI YAZILIRSA KULLANILACAK//
    //std::unique_ptr<std::unordered_map<std::string , std::string>> p_map;


    std::string createResponsePacket(int callContentNo);
    std::string recvRequestPacket();

public:
    httpServer(uint32_t portNo,std::vector<std::string>& contents,uint32_t contentSize);
    ~httpServer();

    void httpRun();

    //YONLENDIRME ISLEMLERI//
    //std::string& mappingRedirectURL();
    //std::string& handleRequestSubstr();



};
#endif 

/*
1-servera soket uzerinden endpoint istek gelir
2-server kabul eder 
3-gelen istegi alir
4-gelen istege uygun yaniti cevirir
*/
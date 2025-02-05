#ifndef __HTTP_SERVER_HPP__
#define __HTTP_SERVER_HPP__

#include <boost/asio.hpp>
#include <unordered_map>

#include "fileOpen.hpp"
#include "crossDefines.hpp"

using namespace boost::asio;

class httpServer{
private:
    uint32_t portNo;
    uint32_t contentSize;

    std::string m_gelenRequest;
    std::vector<std::string> contents;
    std::vector<std::string> fileNamesInDirectory;
    std::unordered_map<std::string,int> filenameIndexMap;


    std::unique_ptr<ip::tcp::acceptor> httpAccept;
    std::unique_ptr<boost::asio::io_context> p_io;
    
    boost::asio::ip::tcp::socket *p_socket;
    
    

    //YONLENDIRME ISLEMLERI//
    std::string& mappingRedirectURL();
    std::string getRequestPage();
    /*
    [HTTP-SERVER-LOG] : Gelen paket icerigi : 
    GET /test_bir.html HTTP/1.1             ---> sadece ilk satiri okuyup hangi sayfaya gidecegini cikartabiliriz
    Host: 127.0.0.1:8080                    ---> src/http/test_bir.html => sondaki kisimla gelen istek paketini kiyaslayip yonlendirecegiz
    Connection: keep-alive                  ---> mevcutun contenti uzerinden cevap gonderecegiz
    */
    //YONLENDIRME ISLEMLERI//



    std::string createResponsePacket();
    std::string recvRequestPacket();
    std::string getJustFilename(std::string filepath);

public:
    //fileOpeni otomatik konfigure etmek icin
    httpServer(uint32_t portNo,const std::string &specialExtension="",bool isIncludeDir=false,
    const std::string &httpPathDirectory=DEFAULT_DIRECTORY);

    //fileOpeni elle konfigure etmek icin
    httpServer(uint32_t portNo,std::vector<std::string>& contents,uint32_t contentSize,
    std::vector<std::string> fileNamesInDirectory,std::unordered_map<std::string,int> filenameIndexMap);
    
    
    void httpRun(bool isStart=true);

};
#endif 

/*
1-servera soket uzerinden endpoint istek gelir
2-server kabul eder 
3-gelen istegi alir
4-gelen istege uygun yaniti cevirir
*/
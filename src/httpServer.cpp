#include "../include/httpServer.hpp"

httpServer::httpServer(uint32_t portNo,std::vector<std::string>& contents,uint32_t contentSize)
:portNo(portNo){
    this->contents = contents;
    this->contentSize = contentSize;
 
    this->p_io = std::make_unique<boost::asio::io_context>();
   //this->p_socket = std::make_unique<boost::asio::ip::tcp::socket>(*p_io);
}

httpServer::~httpServer(){
    p_socket->close();
}


std::string httpServer::createResponsePacket(int callContentNo){
    /*
    RESPONSE PACKET ALANLARI: 
    STATUS          => HTTP/1.1 200 OK\r\n
    TYPE            => Content-Type: text/plain\r\n
    LENGTH          => Content-Length: 15\r\n
    HEAD/BODY AYRIM => \r\n
    DATA            => "hello world !"
    */

    std::string response;
    std::string content = contents.at(callContentNo);
    uint32_t length = content.length();
    std::string byte_rn = "\r\n";

    std::string status = "HTTP/1.1 200 OK" + byte_rn;
    std::string content_type = "Content-Type: text/html" +byte_rn;
    std::string content_length = "Content-Length: "+std::to_string(length) + byte_rn;
    //byte_rn
    //content=data

    response = status + content_type + content_length + byte_rn + content;

    //HAZIRLANAN YANITI SOKETE YAZMA//
    boost::asio::write(*p_socket,buffer(response));

    return response;
}

void httpServer::httpRun(){
    try{
        ip::tcp::acceptor httpAccept(*p_io,ip::tcp::endpoint(ip::tcp::v4(),this->portNo));
        SLOG(std::to_string(portNo)+" portunda calisiyor");
    
        while(1){
            p_socket = new ip::tcp::socket(*p_io);
            httpAccept.accept(*p_socket);
            
            //gelen istek paketini alma
            recvRequestPacket();
            //yaniti hazirlayip gonderme
            createResponsePacket(0);
            
            p_socket->close();
            delete p_socket;

        }

    }
    catch(std::exception &e){
        LOG("httpRun Func Exception: " << e.what());
    }
    
}

std::string httpServer::recvRequestPacket(){
    try{
        char requestPacket[1024];
        memset(requestPacket,0,sizeof(requestPacket)); //bellek blogunu sifirladik
        
        //gelen verinin ne kadarini okuyabiliyorsak anlik okumamiz gerekiyor
        //http serverinda asio::read mantiksizdir cunku verilen boyut dolana kadar blocklar

        boost::system::error_code asio_err_code;
        int recvLength = p_socket->read_some(buffer(requestPacket),asio_err_code);
        SLOG("istek paketinin boyutu --> " << recvLength);

        if(asio_err_code){
            SLOG("paket okunamadi !");
            LOG("recvRequestPacket Func : paket okumada hata");
            return "";
        }

        //gelen paketin sadece okunan uzunlugunu loglama
        std::string gelenRequest(requestPacket,recvLength);
        SLOG("gelen paket icerigi : \n" << gelenRequest);

        return gelenRequest;
    }
    catch(std::exception &e){
        LOG("recvRequestPacket Func Exception: " << e.what());
    }
}

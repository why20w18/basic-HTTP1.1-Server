#include "../include/httpServer.hpp"

httpServer::httpServer(uint32_t portNo ,const std::string &specialExtension,bool isIncludeDir,const std::string &httpPathDirectory)
:portNo(portNo){
    fileOpen *fop = new fileOpen(httpPathDirectory);
    fop->initLister(specialExtension,isIncludeDir)->outputPaths();
    fop->readFileContent();
    
    this->contents = *(fop->getContents());
    this->contentSize = fop->getContentCount();
    this->fileNamesInDirectory = std::move(fop->getPathsVec());
    this->filenameIndexMap = std::move(fop->filenameIndexMap);

    delete fop;

    this->p_io = std::make_unique<boost::asio::io_context>();
    httpAccept = std::make_unique<ip::tcp::acceptor>(*p_io,ip::tcp::endpoint(ip::tcp::v4(),this->portNo));

}



httpServer::httpServer(uint32_t portNo,std::vector<std::string>& contents,uint32_t contentSize,
std::vector<std::string> fileNamesInDirectory,std::unordered_map<std::string,int> filenameIndexMap)
:portNo(portNo){
    this->contents = contents;
    this->contentSize = contentSize;
    this->fileNamesInDirectory = std::move(fileNamesInDirectory);
    this->filenameIndexMap = std::move(filenameIndexMap);

    this->p_io = std::make_unique<boost::asio::io_context>();
    httpAccept = std::make_unique<ip::tcp::acceptor>(*p_io,ip::tcp::endpoint(ip::tcp::v4(),this->portNo));
}


std::string httpServer::createResponsePacket(){

try{

    /*
    RESPONSE PACKET ALANLARI: 
    STATUS          => HTTP/1.1 200 OK\r\n
    TYPE            => Content-Type: text/plain\r\n
    LENGTH          => Content-Length: 15\r\n
    HEAD/BODY AYRIM => \r\n
    DATA            => "hello world !"
    */
    int callContentNo = 0;
    //ARTIK YANIT ISTENEN SAYFAYA GORE HAZIRLANACAK//
    std::string requestFile = getRequestPage().substr(1);
    bool isFileExist = false;

    //dosya dizinde var mi
    for(const auto &x : this->fileNamesInDirectory){
        std::string y = getJustFilename(x);
        if(y == requestFile){
            isFileExist = true;
            LOG("createResponsePacket Func : ARANAN DOSYA BULUNDU ----> " << requestFile << " DIZINI ----->" << x );
            SLOG("Client tarafindan istenen sayfa bulundu : " << requestFile << " || sayfa dizini : " << x);
        }
        LOG("createResponsePacket Func : ARANAN DOSYA ----> " << requestFile << " BAKILAN DIZIN ---->" << x);         
    }

    if(requestFile == "favicon.ico")
        isFileExist = true;

    if(isFileExist)
        callContentNo = filenameIndexMap[DEFAULT_REQUEST+requestFile];
    
    if(!isFileExist)
        SLOG("Client tarafindan istekte bulunulan sayfa bulunamadi !");

    
    LOG("createResponsePacket Func : cagirlacak content no " << callContentNo << "   : cagrilan dosya adi : " << requestFile);         

    std::string response;
    std::string content;

    if(isFileExist)
        content = contents.at(callContentNo);
    else 
        content = "[404 NOT FOUND ERROR] <-> ULASILMAK ISTENEN SAYFAYA YONLENDIRILEMIYORSUNUZ !";
    
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
    catch(std::exception &ex){
        LOG("createResponsePacket Func Exception : " << ex.what());
        std::cerr << "createResponsePacket Func Exception : " << ex.what() << "\n";
    }

}

void httpServer::httpRun(bool isStart){
    try{
        if(isStart){
        SLOG(std::to_string(portNo)+" portunda calismaya basladi");
        
        while(httpAccept->is_open()){
            LOG("httpRun Func : acceptAciktir");

            p_socket = new ip::tcp::socket(*p_io);
            httpAccept->accept(*p_socket);
            
            //gelen istek paketini alma
            recvRequestPacket();
            
            //yaniti hazirlayip gonderme
            createResponsePacket();
            
            p_socket->close();
            delete p_socket;
            LOG("httpRun Func : p_socket deleted");
        }
    }
    else{
        this->httpAccept->close();
        SLOG("Yayin yapilan sayfayi yenilediginizde HTTP Server otomatik sonlanacaktir")
    } 
        
    }
    catch(std::exception &e){
        LOG("httpRun Func Exception: " << e.what());
        std::cerr << "httpRun Func Exception: " << e.what() << "\n";
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
        SLOG("Istek paketinin boyutu = " << recvLength);

        if(asio_err_code){
            SLOG("paket okunamadi !");
            LOG("recvRequestPacket Func : paket okumada hata");
            std::cerr << "recvRequestPacket Func : paket okumada hata" << "\n"; 
            return "";
        }

        //gelen paketin sadece okunan uzunlugunu loglama
        std::string gelenRequest(requestPacket,recvLength);
        SLOG("Gelen paket icerigi : \n" << gelenRequest);
        this->m_gelenRequest = gelenRequest;
        return gelenRequest;
    }
    catch(std::exception &e){
        LOG("recvRequestPacket Func Exception: " << e.what());
        std::cerr << "recvRequestPacket Func Exception: " << e.what() << "\n"; 
    }
}

std::string httpServer::getRequestPage(){
    //GET /test_bir.html HTTP/1.1 => substring haline getirelecek kisim
    std::string requestPacket = m_gelenRequest;
    int pathStartIndex = requestPacket.find_first_of('/');
    std::string ilkSatir = requestPacket.substr(pathStartIndex);
    int pathLastIndex = ilkSatir.find(" HTTP/1.1");
    ilkSatir = ilkSatir.substr(0,pathLastIndex);

    LOG("CLIENT TARAFINDAN TALEP EDILEN SAYFA:|"<<ilkSatir<<"|");
    
    return ilkSatir;
}


std::string httpServer::getJustFilename(std::string filepath){
    int startIndex = filepath.find_last_of(DEFAULT_DELIMITER);
    if(DEFAULT_OPERATING_SYSTEM == 1) //linux
        filepath = filepath.substr(++startIndex);

    else if(DEFAULT_OPERATING_SYSTEM == 2) //win32
        filepath = filepath.substr(++startIndex);

    LOG("getJustFilename Func : |" << filepath << "|");
    return filepath;
}
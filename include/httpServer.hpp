#ifndef __HTTP_SERVER_HPP__
#define __HTTP_SERVER_HPP__

#include <boost/asio.hpp>
#include "fileOpen.hpp"

using namespace boost::asio;

class httpServer{
private:
    uint32_t portNo;
    std::unique_ptr<io_context> p_io;
    std::unique_ptr<ip::tcp::socket> p_socket;
    std::unique_ptr<fileOpen> p_fop;

public:
    httpServer(uint32_t portNo);
    void createResponsePacket(char *packet);
    


};


#endif 
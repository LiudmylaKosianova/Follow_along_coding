#include <iostream>
#include <chrono>
#include <thread>

#define ASIO_STANDALONE //it is probably extra, since my asio dir comes withour boost
#include "libs/asio-1.30.2/include/asio.hpp"
#include "libs/asio-1.30.2/include/asio/ts/buffer.hpp"
#include "libs/asio-1.30.2/include/asio/ts/internet.hpp"

 
 
std::vector<char> vBuffer(20 * 1024);
void GramTheData(asio::ip::tcp::socket& socket)
{
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if(!ec)
            {
                std::cout << "\nRead " << length << "bytes\n";

                for (int i = 0; i < length; i++){
                    std::cout << vBuffer[i];
                }
                GramTheData(socket);
            }
        }
    );
}

int main(){
  

    asio::io_context context; //platform specific interface 
    std::cout << "ASIO setup works!" << std::endl;

    //idle work for context so that it won't finish too early
    asio::io_context::work idleWork(context);

    //start the context thread
    std::thread thrContext = std::thread([&]() {context.run();});

    asio::error_code ec;
    //endpoint (address) where to connect to
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);

    //create a socket
    asio::ip::tcp::socket socket(context);

    //socket will try to connect
    socket.connect(endpoint, ec);

    //check for problems
    if(!ec){
        std::cout << "Connected" << std::endl;
    }else{
        std::cout << "Failed to connect" << ec.message() << std::endl;
    }

    //check if the connection is alive
    if(socket.is_open()){
        
        GramTheData(socket);
        
        //createing the request to send
        std::string sRequest = "GET /index.html HTTP/1.1\r\n"
                                "Host: example.com\r\n"
                                "Connection: close\r\n\r\n";
        
        //sending the request
        socket.write_some(asio::buffer(sRequest.data(),sRequest.size()), ec);

        //program is busy with something else, while asio transfers data in the background
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2000ms);

        context.stop();
        if(thrContext.joinable()) thrContext.join();
        

    }
    
     

    return 0;
}
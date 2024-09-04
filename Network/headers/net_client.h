#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"
#include "net_connection.h"

namespace olc
{
    namespace net
    {
        template <typename T>
        class client_interface
        {
            client_interface() : m_socket(m_context)
            {
                //initialise the socket with the io contex, so it can do something
            }

            virtual ~client_interface()
            {
                //if the client is destroyed, disconnect from server
                Disconnect();
            }

        public:
            //connect to server tiwht hostname/ip and port
            bool Connect(const std::string& host, const uint16_t port)
            {
                try
                {
                    //create connection
                    m_connection = std::make_unique<connection<T>>();

                    //resolve hostname/io into tangiable physical address
                    asio::ip::tcp::resolver resolver(m_context);
                    m_endpoints = resolver.resolve(host, std::to_string(port));

                    //tell the connection object to connect to server
                    m_connection -> ConnectToSever(m_endpoints);

                    //start Context thread
                    thrContext = std::thread([this](){m_context.run();});

                }
                catch(const std::exception& e)
                {
                    std::cerr<< "Client exception: " << e.what() << '\n';
                    return false;
                }
                
            }

            void Disconnect()
            {
                if(IsConnected)
                {
                    m_connection->Disconnect();
                }

                m_context.stop();
                if(thrContext.joinable())
                    thrContext.join();
                
                m_connection.release();

            }

            //check if the client is actually connected to a server
            bool IsConnected()
            {
                if (m_connection)
                    return m_connection -> IsConnected();
                else
                    return false;
            }

            //retrieve queue of messages from server
            tsqueue<owned_message<T>>& Incomming()
            {
                return m_qMessagesIn;
            }

        protected:
            //asio context handles the data transfer, but needs a thread to execute its own commands
            asio::io_context m_context;
            std::thread thrContext;
            //the hardware socket that is connected to the server
            asio::ip::tcp::socket m_socket;
            //the client has a single instance of a "connection" object
            std::unique_ptr<connection<T>> m_connection;
        private:
            //this is thread safe queue of incoming messages from server
            tsqueue<owned_message<T>> m_qMessagesIn;
        };
    }
}
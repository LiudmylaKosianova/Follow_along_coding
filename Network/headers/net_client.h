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
                return false;
            }

            void Disconnect()
            {

            }

            //check if the client is actually connected to a server
            bool IsConnected()
            {
                return false
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
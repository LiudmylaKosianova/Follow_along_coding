#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"

namespace olc
{
    namespace net
    {
        template<typename T>
        class connection : public std::enable_shared_from_this<connection<T>>
        {
        public:
            connection()
            {}

            virtual ~connection()

        public:
            bool ConnectionToServer();
            bool Disconnect();
            bool IsConnected() const;

        public:
            bool Send(const message<T>& msg);

            
        };
    }
}
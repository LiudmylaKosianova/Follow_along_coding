#pragma once

#include "net_common.h"

namespace olc
{
    namespace net
    {
        //Message Header is sent at start of all messages.
        //The template helps to use "enum class" to ensure that the messages are valid at compile time
        template <typename T>
        struct message_header
        {
            T id{};
            uint32_t size = 0;
        };
        template <typename T>
        struct message
        {
            message_header<T> header {};
            std::vector<uint8_t> body;

            //returns size of entire message packet in bytes
            size_t size() const
            {
                return sizeof(message_header<T>) + body.size();
            }
        };
    }
}
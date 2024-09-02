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

            //override for std::cout compatability - produces friendly description of the message
            friend std::ostream& operator << (std::ostream& os, const message<T>& msg)
            {
                os << "ID" << int(msg.header.id) << " Size:" << mst.header.size;
                return os;
            }

            //Pushes any data into the message buffer
            template<typename DataType>
            friend message<T>& operator << (message<T>& msg, const DataType& data)
            {
                //check if the type of data being pushed is trivially copyable
                static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

                //cahse current size of vector
                size_t i = msg.body.size();

                //resize the vector by the size of the data being pushed
                msg.body.resize(msg.body.size() + sizeof(DataType));

                //copy the data into the newly allocated vector space
                std::memspy(msg.body.data() + i, &data, sizeof(DataType));

                //calculate the message size again
                msg.header.size = msg.size();

                //return the target message
                return msg;
    
            }
        };
    }
}
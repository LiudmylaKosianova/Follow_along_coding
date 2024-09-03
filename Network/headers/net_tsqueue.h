#pragma once

#include "net_common.h"

namespace olc
{
    namespace net
    {
        template<typename T>
        class tsqueue
        {
        public:
            tsqueue() = default;
            tsuque(const tsqueue<T>&) = delete;

            //returns and maintains item at the front of Queue
            const T& front()
            {
                std::scoped_lock lock(muxQueue);
                return deqQueue.front();
            }

            //returns and maintains item at the back of Queue
            const T& back()
            {
                std::scoped_lock lock(muxQueue);
                return deqQueue.back();
            }

            //adds an item to the back of Queue
            void push_back(const T& item)
            {
                std::scoped_lock lock(muxQueue);
                deqQueue.emplace_back(std::move(item));
            }

            //adds an item to the front of Queue
            void push_back(const T& item)
            {
                std::scoped_lock lock(muxQueue);
                deqQueue.emplace_front(std::move(item));
            }


        protected:
            std::mutex muxQueue;
            std::deque<T> deqQueue;
        };
    }
}
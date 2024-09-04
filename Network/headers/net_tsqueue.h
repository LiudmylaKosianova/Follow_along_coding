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
            virtual ~tsqueue(){ clear();}

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

            //return true if Queue has no items
            bool empty()
            {
                std::scoped_lock lock(muxQueue);
                return deqQueue.empty();
            }

            //return the number of items in Queue
            size_t count()
            {
                std::scoped_lock lock(muxQueue);
                return deqQueue.size();
            }

            //erase all items in Queue
            void clear()
            {
                std::scoped_lock lock(muxQueue);
                deqQueue.clear();
            }

            //romoves and returns item from the front of Queue
            T pop_front()
            {
                std::scoped_lock lock(muxQueue);
                auto t = std::move(deqQueue.front());
                deqQueue.pop_front();
                return t;
            }

            //romoves and returns item from the back of Queue
            T pop_back()
            {
                std::scoped_lock lock(muxQueue);
                auto t = std::move(deqQueue.back());
                deqQueue.pop_back();
                return t;
            }



        protected:
            std::mutex muxQueue;
            std::deque<T> deqQueue;
        };
    }
}
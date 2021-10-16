//
// Created by Benjam on 06-03-21.
//

#ifndef SECMONCLIENT_MESSAGEQUEUE_H
#define SECMONCLIENT_MESSAGEQUEUE_H


#include <mutex>
#include <deque>
#include <condition_variable>

namespace Math4BG
{
    template<typename T>
    class CircularQueue
    {
    public:
        CircularQueue() = default;

        explicit CircularQueue(unsigned int maxSize) :
        m_maxSize(maxSize)
        {

        }

        CircularQueue(const CircularQueue &) = delete;

        ~CircularQueue()
        {
            clear();
        }

        size_t count()
        {
            std::scoped_lock lock(m_mutex);
            return m_deque.size();
        }

        const T &front()
        {
            std::scoped_lock lock(m_mutex);
            return m_deque.front();
        }

        const T &back()
        {
            std::scoped_lock lock(m_mutex);
            return m_deque.back();
        }

        T pop_front()
        {
            std::scoped_lock lock(m_mutex);
            T t = std::move(m_deque.front());
            m_deque.pop_front();
            return t;
        }

        T pop_back()
        {
            std::scoped_lock lock(m_mutex);
            T t = std::move(m_deque.back());
            m_deque.pop_back();
            return t;
        }

        void push_back(const T &item)
        {
            std::scoped_lock lock(m_mutex);
            m_deque.emplace_back(std::move(item));

            if(m_deque.size() > m_maxSize)
                m_deque.pop_front();

            std::unique_lock<std::mutex> ul(m_mutexBlocking);
            m_blocking.notify_one();
        }

        void push_front(const T &item)
        {
            std::scoped_lock lock(m_mutex);
            m_deque.emplace_front(std::move(item));

            if(m_deque.size() > m_maxSize)
                m_deque.pop_back();

            std::unique_lock<std::mutex> ul(m_mutexBlocking);
            m_blocking.notify_one();
        }

        bool empty()
        {
            std::scoped_lock lock(m_mutex);
            return m_deque.empty();
        }

        void clear()
        {
            std::scoped_lock lock(m_mutex);
            m_deque.clear();
        }

        void wait()
        {
            while (empty())
            {
                std::unique_lock<std::mutex> ul(m_mutexBlocking);
                m_blocking.wait(ul);
            }
        }

        T operator[](int i)
        {
            std::scoped_lock lock(m_mutex);
            return m_deque[i];
        }

    private:
        std::mutex m_mutex;
        std::mutex m_mutexBlocking;
        std::deque<T> m_deque;
        std::condition_variable m_blocking;
        unsigned int m_maxSize {10};
    };
}

#endif //SECMONCLIENT_MESSAGEQUEUE_H

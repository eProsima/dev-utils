// Copyright 2024 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file DBQueue.hpp
 */

#ifndef DBQUEUE_HPP
#define DBQUEUE_HPP

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

namespace eprosima {
namespace utils {
namespace event {

/**
 * Double buffered, threadsafe queue for MPSC (multi-producer, single-consumer) comms.
 */
template<class T>
class DBQueue
{

public:

    DBQueue()
        : m_foreground_queue(&m_queue_alpha)
        , m_background_queue(&m_queue_beta)
    {
    }

    //! Clears foreground queue and swaps queues.
    void swap()
    {
        std::unique_lock<std::mutex> fg_guard(m_foreground_mutex);
        std::unique_lock<std::mutex> bg_guard(m_background_mutex);

        // Clear the foreground queue.
        std::queue<T>().swap(*m_foreground_queue);

        auto* swap       = m_background_queue;
        m_background_queue = m_foreground_queue;
        m_foreground_queue = swap;
    }

    //! Pushes to the background queue. Copy constructor.
    void push(
            const T& item)
    {
        std::unique_lock<std::mutex> guard(m_background_mutex);
        m_background_queue->push(item);
    }

    //! Pushes to the background queue. Move constructor.
    void push(
            T&& item)
    {
        std::unique_lock<std::mutex> guard(m_background_mutex);
        m_background_queue->push(std::move(item));
    }

    //! Returns a reference to the front element
    //! in the foregrund queue.
    T& front()
    {
        std::unique_lock<std::mutex> guard(m_foreground_mutex);
        return m_foreground_queue->front();
    }

    const T& front() const
    {
        std::unique_lock<std::mutex> guard(m_foreground_mutex);
        return m_foreground_queue->front();
    }

    //! Pops from the foreground queue.
    void pop()
    {
        std::unique_lock<std::mutex> guard(m_foreground_mutex);
        m_foreground_queue->pop();
    }

    //! Return the front element in the foreground queue by moving it and erase it from the queue.
    T front_and_pop()
    {
        std::unique_lock<std::mutex> guard(m_foreground_mutex);

        // Get value by moving the internal queue reference to a new value
        T value = std::move(m_foreground_queue->front());
        // At this point m_foreground_queue contains a non valid element, but mutex is taken and next instruction erase it

        // Pop value from queue
        m_foreground_queue->pop();

        // Return value (as it has been created in this scope, it will not be copied but moved or directly forwarded)
        return value;
    }

    //! Reports whether the foreground queue is empty.
    bool empty() const
    {
        std::unique_lock<std::mutex> guard(m_foreground_mutex);
        return m_foreground_queue->empty();
    }

    //! Reports whether the both queues are empty.
    bool both_empty() const
    {
        std::unique_lock<std::mutex> guard(m_foreground_mutex);
        std::unique_lock<std::mutex> bg_guard(m_background_mutex);
        return m_foreground_queue->empty() && m_background_queue->empty();
    }

    //! Reports the size of the foreground queue.
    size_t size() const
    {
        std::unique_lock<std::mutex> guard(m_foreground_mutex);
        return m_foreground_queue->size();
    }

    //! Clears foreground and background.
    void clear()
    {
        std::unique_lock<std::mutex> fg_guard(m_foreground_mutex);
        std::unique_lock<std::mutex> bg_guard(m_background_mutex);
        std::queue<T>().swap(*m_foreground_queue);
        std::queue<T>().swap(*m_background_queue);
    }

private:

    // Underlying queues
    std::queue<T> m_queue_alpha;
    std::queue<T> m_queue_beta;

    // Front and background queue references (double buffering)
    std::queue<T>* m_foreground_queue;
    std::queue<T>* m_background_queue;

    mutable std::mutex m_foreground_mutex;
    mutable std::mutex m_background_mutex;
};

} /* namespace event */
} /* namespace utils */
} /* namespace eprosima */

#endif // ifndef DBQUEUE_H

#include "buffer_queue.hpp"

buffer_queue::buffer_queue() {
            lock_empty.lock(); //Na poczatku wszystko jest puste

}

std::string buffer_queue::pop() {
            std::string result;
            lock_empty.lock();
            safe.lock();
            result = messages.front();
            messages.pop();
            if (!messages.empty()) { //Nie doszlismy do 0 to odblokowuje
                lock_empty.unlock();
            }
            safe.unlock();
            return result;

}

void buffer_queue::push(std::string message) {
            safe.lock();
            if (messages.empty()) { //Jesli 0 to odblokuj bo ktos wisi na popie
                lock_empty.unlock();
            }
            messages.push(message);
            safe.unlock();
}

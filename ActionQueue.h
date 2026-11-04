#pragma once
#include <cstddef>
#include <string>
#include <vector>

class ActionQueue {
public:
    explicit ActionQueue(std::size_t capacity);
    bool empty() const;
    bool full() const;
    std::size_t size() const;
    bool enqueue(const std::string& action);
    std::string dequeue();
    std::string peek() const;
private:
    std::vector<std::string> items_;
    std::size_t frontIndex_ = 0;
    std::size_t count_ = 0;
};

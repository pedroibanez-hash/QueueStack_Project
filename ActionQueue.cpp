#include "ActionQueue.h"
#include <stdexcept>

ActionQueue::ActionQueue(std::size_t capacity) : items_(capacity) {}
bool ActionQueue::empty() const { return count_ == 0; }
bool ActionQueue::full() const { return count_ == items_.size(); }
std::size_t ActionQueue::size() const { return count_; }

bool ActionQueue::enqueue(const std::string& action) {
    if (full()) return false;
    const std::size_t back = (frontIndex_ + count_) % items_.size();
    items_[back] = action;
    ++count_;
    return true;
}
std::string ActionQueue::dequeue() {
    if (empty()) throw std::out_of_range("queue is empty");
    std::string action = items_[frontIndex_];
    frontIndex_ = (frontIndex_ + 1) % items_.size();
    --count_;
    return action;
}
std::string ActionQueue::peek() const {
    if (empty()) throw std::out_of_range("queue is empty");
    return items_[frontIndex_];
}

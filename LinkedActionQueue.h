#pragma once
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

// Optional challenge: unbounded queue. Capacity argument is accepted
// for source compatibility, but does not limit the number of nodes.
class LinkedActionQueue {
    struct Node {
        std::string action;
        std::unique_ptr<Node> next;
        explicit Node(const std::string& value) : action(value) {}
    };
    std::unique_ptr<Node> front_;
    Node* back_ = nullptr; // Non-owning pointer.
    std::size_t count_ = 0;
public:
    explicit LinkedActionQueue(std::size_t = 0) {}
    LinkedActionQueue(const LinkedActionQueue&) = delete;
    LinkedActionQueue& operator=(const LinkedActionQueue&) = delete;
    ~LinkedActionQueue() {
        // Iterative destruction avoids recursive deletion of long chains.
        while (front_) {
            auto old = std::move(front_);
            front_ = std::move(old->next);
        }
    }
    bool empty() const { return count_ == 0; }
    bool full() const { return false; }
    std::size_t size() const { return count_; }
    bool enqueue(const std::string& action) {
        auto node = std::make_unique<Node>(action);
        Node* tail = node.get();
        if (back_) back_->next = std::move(node);
        else front_ = std::move(node);
        back_ = tail;
        ++count_;
        return true;
    }
    std::string dequeue() {
        if (empty()) throw std::out_of_range("queue is empty");
        std::string action = front_->action;
        auto old = std::move(front_);
        front_ = std::move(old->next);
        --count_;
        if (!front_) back_ = nullptr;
        return action;
    }
    std::string peek() const {
        if (empty()) throw std::out_of_range("queue is empty");
        return front_->action;
    }
};

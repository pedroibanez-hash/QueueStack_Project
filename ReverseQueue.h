#pragma once
#include "ActionQueue.h"
#include "UndoStack.h"

// Remove each queue item, push it, then pop back into the queue.
inline void reverseQueue(ActionQueue& queue) {
    UndoStack stack;
    while (!queue.empty()) stack.push(queue.dequeue());
    while (!stack.empty()) queue.enqueue(stack.pop());
}

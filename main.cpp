// Keep assignment assertions active even in Release builds.
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "ActionQueue.h"
#include "UndoStack.h"
#include "ReverseQueue.h"
#include "LinkedActionQueue.h"

void undoLast(UndoStack& history) {
    if (history.empty()) std::cout << "Nothing to undo\n";
    else std::cout << "Undoing: " << history.pop() << '\n';
}

template<class Function>
void expectOutOfRange(Function function) {
    bool threw = false;
    try { function(); }
    catch (const std::out_of_range&) { threw = true; }
    assert(threw);
}

// Reused unchanged for both queue implementations.
template<class Queue>
void testQueueOrder() {
    Queue q(3);
    assert(q.empty());
    q.enqueue("Fade In");
    q.enqueue("Move Character");
    q.enqueue("Play Sound");
    auto first = q.dequeue();
    assert(first == "Fade In");
    q.enqueue("Rotate Character");
    auto second = q.dequeue();
    assert(second == "Move Character");
    assert(q.size() == 2);
    q.enqueue("Fade Out");
    assert(q.peek() == "Play Sound");
    for (const auto& expected : {"Play Sound", "Rotate Character", "Fade Out"}) {
        auto action = q.dequeue();
        assert(action == expected);
    }
    assert(q.empty());
    expectOutOfRange([&] { q.dequeue(); });
    expectOutOfRange([&] { q.peek(); });
    q.enqueue("Reuse");
    auto reused = q.dequeue();
    assert(reused == "Reuse");
}

int main() {
    testQueueOrder<ActionQueue>();
    ActionQueue bounded(3);
    for (const auto& value : {"A", "B", "C"}) bounded.enqueue(value);
    assert(bounded.full());
    bool accepted = bounded.enqueue("Too Many");
    assert(!accepted);
    assert(bounded.peek() == "A");
    ActionQueue zero(0);
    assert(zero.empty() && zero.full());
    accepted = zero.enqueue("Rejected");
    assert(!accepted);
    expectOutOfRange([&] { zero.dequeue(); });
    std::cout << "All queue tests passed!\n";

    // Part 5, question 2: push three, pop, push, pop.
    UndoStack history;
    history.push("Fade In");
    history.push("Move Character");
    history.push("Play Sound");
    std::string first = history.pop();
    assert(first == "Play Sound");
    history.push("Rotate Character");
    std::string second = history.pop();
    assert(second == "Rotate Character");
    assert(history.size() == 2);
    assert(history.peek() == "Move Character");

    // Verify the exact output and the modification of the original stack.
    std::ostringstream captured;
    auto* previous = std::cout.rdbuf(captured.rdbuf());
    undoLast(history);
    undoLast(history);
    undoLast(history);
    std::cout.rdbuf(previous);
    assert(captured.str() ==
        "Undoing: Move Character\nUndoing: Fade In\nNothing to undo\n");
    assert(history.empty());
    expectOutOfRange([&] { history.pop(); });
    expectOutOfRange([&] { history.peek(); });
    std::cout << captured.str();
    std::cout << "All stack tests passed!\n";

    // Reversal: full queue, empty queue, one item, and wrapped queue.
    reverseQueue(bounded);
    for (const auto& expected : {"C", "B", "A"}) {
        auto value = bounded.dequeue();
        assert(value == expected);
    }
    reverseQueue(bounded);
    assert(bounded.empty());
    bounded.enqueue("Only");
    reverseQueue(bounded);
    assert(bounded.peek() == "Only");
    bounded.dequeue();
    bounded.enqueue("A");
    bounded.enqueue("B");
    bounded.enqueue("C");
    bounded.dequeue();
    bounded.enqueue("D");
    reverseQueue(bounded);
    for (const auto& expected : {"D", "C", "B"}) {
        auto value = bounded.dequeue();
        assert(value == expected);
    }
    std::cout << "All reverse queue tests passed!\n";

    testQueueOrder<LinkedActionQueue>();
    LinkedActionQueue linked(3);
    for (int i = 0; i < 100; ++i) linked.enqueue(std::to_string(i));
    assert(linked.size() == 100 && !linked.full());
    for (int i = 0; i < 100; ++i) {
        auto value = linked.dequeue();
        assert(value == std::to_string(i));
    }
    std::cout << "All linked queue tests passed!\n";
}

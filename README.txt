QUEUE AND STACK PROJECT

CLion:
1. Extract the ZIP.
2. Open the extracted QueueStack_Project folder as a project.
3. Let CLion load CMakeLists.txt.
4. Run QueueStackProject.

Files:
ActionQueue.h / ActionQueue.cpp: fixed-capacity circular queue.
UndoStack.h: completed vector-based stack.
main.cpp: queue, stack, undoLast, reversal and optional linked queue tests.
ReverseQueue.h: final exercise, reversing a queue using a stack.
LinkedActionQueue.h: optional unbounded linked queue using unique_ptr.

The stack test uses Fade In, Move Character, Play Sound, then Rotate Character.
If Part 1 question 6 uses different names, replace them accordingly.

Optional challenge inconsistency:
An unbounded linked queue cannot pass fixed-capacity rejection tests unchanged.
This project reuses the same order/empty tests for both implementations and tests
their different capacity behavior separately. The linked constructor accepts a
capacity argument for compatibility but intentionally ignores it.

GitHub:
Upload the source files and CMakeLists.txt, commit and push.
Submit YOUR actual repository URL. This project has not been uploaded to GitHub.

Command line:
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure

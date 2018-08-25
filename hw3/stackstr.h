#ifndef STACKSTR_H
#define STACKSTR_H
#include "lliststr.h"

class StackStr {
 public:
  StackStr();
  ~StackStr();

  /**
   * Returns true if the stack is empty, false otherwise
   */
  bool empty() const;

  /**
   * Returns the number of elements in the stack.
   */
  int size() const;

  /**
   * Pushes a new value, str, onto the top of the stack
   */
  void push(const std::string &str);

  /**
   * Returns the top value on the stack.
   * If the stack is empty, return the empty string.
   */
  std::string top() const;

  /**
   * Removes the top element on the stack.
   * Should do nothing if the stack is empty.
   */
  void pop();

 private:
  /** 
   * Single data member of the Stack.
   * We use composition to implement this Stack 
   */
  LListStr list_;
};
#endif

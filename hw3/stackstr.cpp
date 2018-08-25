#include <iostream>
#include <cmath>
#include "stackstr.h"

  StackStr::StackStr(){
    
  }
  StackStr::~StackStr(){
  	
  }

  bool  StackStr::empty() const{
  	if(list_.empty())
  		return true;
  	else 
  		return false;
  }

  /**
   * Returns the number of elements in the stack.
   */
  int  StackStr::size() const{
  	return list_.size();
  }


  /**
   * Pushes a new value, str, onto the top of the stack
   */
  void  StackStr::push(const std::string &str){
  	list_.insert(0, str);
  }

  /**
   * Returns the top value on the stack.
   * If the stack is empty, return the empty string.
   */
  std::string StackStr::top() const{
  	return list_.get(0);
  }

  /**
   * Removes the top element on the stack.
   * Should do nothing if the stack is empty.
   */
  void  StackStr::pop(){
  	list_.remove(0);
  }
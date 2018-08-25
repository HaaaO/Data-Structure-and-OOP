#ifndef LLISTSTR_H
#define LLISTSTR_H

#include <string>

class LListStr {
 public:
  /**
   * Default constructor
   */
  LListStr();

  /**
   * Destructor
   */
  ~LListStr();

  /**
   * Returns the current number of items in the list
   */
  int size() const;

  /**
   * Returns true if the list is empty, false otherwise
   */
  bool empty() const;

  /**
   * Inserts val so it appears at the index given as pos. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void insert(int pos, const std::string &val);

  /**
   * Removes the value at the index given by pos. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void remove(int pos);

  /**
   * Overwrites the old value at the index given by pos with val. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void set(int pos, const std::string &val);

  /**
   * Returns the value at the index given by pos.  If the index pos is invalid,
   * then you should return the empty string.
   */
  std::string get(int pos) const;

 private:
  struct Item {
    std::string val;
    Item *prev;
    Item *next;
  };

  // Feel free to add private helper functions if you desire.
 
  /**
   * Data members
   */
  Item* head_;
  Item* tail_;
  int size_;
};

#endif

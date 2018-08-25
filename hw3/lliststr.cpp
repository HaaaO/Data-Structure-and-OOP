#include <iostream>
#include <cmath>
#include "lliststr.h"

/**
   * Default constructor
   */
  LListStr::LListStr(){
   	size_ = 0;
  }


/**
   * Destructor
   */
  LListStr::~LListStr(){
     while(!empty()){
  		remove(0);
  	}
  }

  /**
   * Returns the current number of items in the list
   */
  int LListStr::size() const { 
  	return size_;
  }
  /**
   * Returns true if the list is empty, false otherwise
   */
  bool  LListStr::empty() const {
  	if (size_ ==0)
  		return true;
  	else
  		return false;
  }
  /**
   * Inserts val so it appears at the index given as pos. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */

  void  LListStr::insert(int pos, const std::string &val){

    // return nothing when pos is invalid
  	if((pos < 0)||(pos > size_))
  	{
  		return;
  	}
  	else{

    // initalise a new item
  	Item* newItem = new Item;
  	newItem->val = val;
  	newItem->prev= NULL;
  	newItem->next= NULL;
  	Item* temp = head_;

    // add when the list was empty
  	if(size_ == 0){

  		head_ = newItem;
  		tail_ = newItem;
  		head_ -> prev = tail_;
  		tail_ -> next = head_;
  	}
  	else{
      // add the new item in the front
  		if ((pos > 0)&&(pos < size_)){
  			for (int i = 0; i < pos-1; i++){
                temp = temp->next;
  			}
  			newItem-> prev = temp;
  			newItem-> next = temp->next;
  			temp-> next-> prev = newItem;
  			temp-> next = newItem ;
  		}

      // add the new item at the back
  		else if(pos == size_){
  			newItem -> prev = tail_;
  			tail_ -> next = newItem;
  			tail_ = newItem;
  			tail_ -> next = head_;
  		}

      //add the new item in the middle
  		else if (pos == 0){
  			newItem -> next = head_;
  			head_ -> prev = newItem;
  			head_ = newItem;
  			head_ -> prev = tail_;
  		}
  		else {
  			return;
  		}
  	}
     size_++;
 }
 }
  /**
   * Removes the value at the index given by pos. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */

  void  LListStr::remove(int pos){
    // check whether the list is empty
  	if(!empty()){
      // delete the list if size is 1
  		if(size_ == 1)
  		{
  			delete tail_;
  			tail_= NULL;
  			head_= NULL;
  			size_--;
  		}
  		else 
  		{
        // pop from the front when the pos = 0
  			if ((pos < size_-1)&&(pos > 0)){
  				Item* temp1 = head_;
  				Item* temp2;
  				Item* target;
  				for (int i = 0; i < pos-1; i++){
                temp1 = temp1->next;
  			    }
  			    target = temp1 -> next;
  			    temp2 = target -> next;
  			    temp1 -> next = temp2;
  			    temp2 -> prev = temp1;
  			    delete target;
  			    size_--;
  			}
        // pop from the back when the pos = size-1
  			else if(pos == size_-1)
  			{
  				Item* temp = tail_;
  				tail_ = tail_ -> prev;
  				tail_ ->next = head_;
  				delete temp;
  				size_--;
  			}
        // pop from the middle
  			else if (pos == 0){
  				Item* temp = head_;
  				head_ = head_->next;
  				head_ ->prev = tail_;
  				delete temp;
  				size_--;
  			}
  			else{

  				return;
  			}
  		}
  	}
  }

  /**
   * Overwrites the old value at the index given by pos with val. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void  LListStr::set(int pos, const std::string &val){
    // check whether the list is empty
  	if(!empty()){

      // if pos = 0, change the val for the head
  		if ((pos <= size_-1)&&(pos >= 0))
  		{
  			Item* temp = head_;
  			for (int i = 0; i < pos; i++){
                temp = temp->next;
  			    }
  			 temp -> val = val;
  		}
  		else {
  			return;
  		}
  	}

  }
  /**
   * Returns the value at the index given by pos.  If the index pos is invalid,
   * then you should return the empty string.
   */
  std::string  LListStr::get(int pos) const{
  	std::string str = "";
  	if(!empty()){
      // get from the head
  		if ((pos <= size_-1)&&(pos >= 0))
  		{
  			Item* temp = head_;
  			for (int i = 0; i < pos; i++){
                temp = temp->next;
  			    }
  			 return temp -> val;
  		}
  		else {
  			return str;
  		}
  	}
  	return str;
  }





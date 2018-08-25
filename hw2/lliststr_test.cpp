#include "lliststr.h"
#include <iostream>
#include <string>

using namespace std;

void checkEmpty(LListStr *list, bool expEmpty) {
	if (list->empty() == expEmpty) {
		cout << "SUCCESS: List is ";
		if (!expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
	else {
		cout << "FAIL: List is ";
		if (expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
}

void checkSize(LListStr *list, int expSize) {
	int size = list->size();
	if (size == expSize) {
		cout << "SUCCESS: List has size " << size << endl;
	}
	else {
		cout << "FAIL: List has size " << size;
		cout << " but expected " << expSize << endl;
	}
}

void checkGet(LListStr *list, int pos, const string &expStr) {
	string str = list->get(pos);
	if (str == expStr) {
		cout << "SUCCESS: String at index " << pos << " is \'" << expStr << "\'" << endl;
	} 
	else {
		cout << "FAIL: String at index " << pos << " is \'" << str << "\'";
		cout << " but expected \'" << expStr << "\'" << endl;
	}
}

int main() {
	LListStr* list = new LListStr();

//---------------Checking <emtpy() function> 
	// Check if the list is initially empty.
	checkEmpty(list, true);
	checkSize(list, 0);


//---------------Checking <insert in the front> 
	std::cout << "------Checking <insert in the front> " << std::endl;
	// Insert an item at the head.

	for (int i = 0; i < 20; i++){

	 list->insert(0, std::to_string(i));
	}

	// Verify the list is not empty
	 checkEmpty(list, false);
	 checkSize(list, 20);


	// Check if the value is correct.

	 for(int i = 19; i >=0; i--){
	 	checkGet(list, (19-i), std::to_string(i));
	 }

//---------------Checking <remove from the front> 
	 std::cout << "------Checking <remove from the front> " << std::endl;
	 // remove all items from the head

	 for(int i = 0; i < 20; i++){
	 	list->remove(0);
	 	 checkSize(list, 19-i );
	 }

	 // check if the value is correct


	 checkEmpty(list, true);
	 checkSize(list, 0);

//---------------Checking <insert at the back> 
	std::cout << "------Checking <insert at the back>  " << std::endl;

    // insert all items from the back

	for (int i = 0; i < 20; i++){

	 list->insert(list->size(), std::to_string(i));
	}

	// Verify the list is not empty
	 checkEmpty(list, false);
	 checkSize(list, 20);


	// Check if the value is correct.

	 for(int i = 0; i < 20; i++){
	 	checkGet(list, i, std::to_string(i));
	 }
//---------------Checking <remove in the front> 
     std::cout << "------Checking <remove in the front>  " << std::endl;

	 // remove all items from the back

	 for(int i = 0; i < 20; i++){
	 	list->remove(list->size()-1);
	 	checkSize(list, 19-i );
	 }

	 // check if the value is correct

	 checkEmpty(list, true);
	 checkSize(list, 0);


//---------------Checking <insert in the middle> 

	 std::cout << "------Checking <insert in the middle>   " << std::endl;
	 // insert values in the middle


	 list->insert(0,"0");
	 list->insert(list->size(),"19");


	 for (int i = 1; i < 19; i++){

	 list->insert(list->size()-1, std::to_string(i));
	}

	// Verify the list is not empty
	 checkEmpty(list, false);
	 checkSize(list, 20);
  
    // check the value is correct

	 for(int i = 0; i < 20; i++){
	 	checkGet(list, i, std::to_string(i));
	 }
//---------------Checking <remove in the middle> 
	 std::cout << "------Checking <remove in the middle>  " << std::endl;

	 // remove 18 items in the middle

	 for(int i = 0; i < 18; i++){
	 	list->remove(1);
	 	checkSize(list, 19-i );
	 }
	 list->remove(0);
	 list->remove(0);


	 checkEmpty(list, true);
	 checkSize(list, 0);


//---------------Checking <insert in the wrong pos> 

std::cout << "------Checking <insert in the wrong pos>   " << std::endl;


for (int i = 0; i < 20; i++){

	 list->insert(list->size(), std::to_string(i));
	}

	// Verify the list is not empty
	 checkEmpty(list, false);
	 checkSize(list, 20);


	// Check if the value is correct.

	 for(int i = 0; i < 20; i++){
	 	checkGet(list, i, std::to_string(i));
	 }

	 // check wrong insert


	 list->insert(-1, "1");

	 checkSize(list, 20);

	 
	
	 list->insert(23,"1");
	 list->insert(21, "1");
     list->insert(-4, "1");

     // check whether everything is still fine

     for(int i = 0; i < 20; i++){
	 	checkGet(list, i, std::to_string(i));
	 }


//---------------Checking <remove from the wrong pos> 

std::cout << "------Checking <remove from the wrong pos>    " << std::endl;


	 list->remove(-1);
	 list->remove(23);
	 list->remove(21);
	 list->remove(-4);
	 list->remove(-6);

	 for(int i = 0; i < 20; i++){
	 	checkGet(list, i, std::to_string(i));
	 }

	 // check whether everything is still fine

     for(int i = 0; i < 20; i++){
	 	checkGet(list, i, std::to_string(i));
	 }
//---------------Checking <set function>

std::cout << "------Checking <set function>    " << std::endl;


   for(int i = 0; i <20; i++){
   	list->set(i, std::to_string(i+10) );
   }


    for(int i = 0; i < 20; i++){
	 	checkGet(list, i, std::to_string(i+10));
	 }

std::cout << "------Extra test   " << std::endl;


 for(int i = 0; i < 20; i++){
	 	list->remove(0);
	 }

	checkSize(list, 0 );

	list->insert(0,"1");
	list->insert(1,"2");
	list->insert(2,"3");

    checkSize(list, 3 );
    checkGet(list, 0, "1");
    checkGet(list, 1, "2");
    checkGet(list, 2, "3");
    list->set(0,"3");
    list->set(1,"2");
    list->set(2,"1");
    checkSize(list, 3 );
    checkGet(list, 0, "3");
    checkGet(list, 1, "2");
    checkGet(list, 2, "1");











	// Clean up memory.
	delete list;
}

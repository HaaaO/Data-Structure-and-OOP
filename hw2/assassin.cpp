#include "lliststr.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]){

	// create a new list
	LListStr* list = new LListStr();
	ifstream infile;
	//open the file 
	infile.open(argv[1]);
	// keep readin the file until the end of file
	while(!infile.fail()){
	string line;
	getline(infile, line);
	stringstream ss(line);
	string decision;
	//parse value in the variables
	ss >> decision;

	//add person in the list
	if(decision == "ADD"){
	 int posi;
	 string name;
	 ss >> posi >> name;
	 list->insert(posi,name);
	}
	// replace value in the list
	else if (decision =="REPLACE")
	{
     int posi;
	 string name;
	 ss >> posi >> name;

	 list->set(posi, name);
	}

	// assasin someone behind
	else if (decision =="ACT" && list->size() > 1)
	{
	  int posi;
	  ss >> posi;
	  int size;
	  size = list->size()-1;

	  // make sure the posi is only valid when its from 0 to size-1
	  if (posi < size && posi >= 0){
	  	cout << "Assassinated: " << list->get(posi+1) << endl;
	  	list->remove(posi+1);
	  }
	  else if(posi == size)
	  {
	    cout << "Assassinated: " << list->get(0) << endl;
	  	list->remove(0);
	  }
	}
	}

	// print out the results
	if(list->size() == 1){
		cout << "Winner: " << list->get(0) << endl;
	}
	else 
	{
		cout << "Remaining Players:" << list -> size() << endl;
		for (int i = 0; i < list->size(); i++){
			cout << list->get(i)<<endl;
		}
	}

	delete list;
}
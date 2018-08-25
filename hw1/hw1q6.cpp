#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>


void reverse(std::ifstream &input){
	std::string word;
	//  read into word first and cout them recursively
	  if (input >> word){
    reverse(input);
	  std::cout << word << " ";
}
}

int main(int argc, char* argv[]){

   // read in the first number and push the rest in recursive function
   std::ifstream ifile(argv[1]);
   int count = 0;
   ifile >> count;
   reverse(ifile);
}

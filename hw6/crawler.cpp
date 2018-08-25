
#include <iostream>
#include <string>  
#include <map>
#include <set>
#include <list>
#include <stack>
#include <vector>
#include <fstream>
#include <sstream>
#include<stdlib.h>
#include<stdio.h>
#include <algorithm>

using namespace std;


// the character checker for the page rank
bool char_checker(char word){

	if((word <=57 && word >= 48 ) || (word <=90 && word >= 65 ) || (word <=122 && word >= 97 )
		|| word ==  91 || word == 93 || word == 40 || word == 41
		){
		return true;
	}
	else{
		return false;
	}

}

// the parser to parse the one line of string
void string_parser(std::string sentence,std::vector<std::string>& link){

	std::list<int> pos;
	int counter = 0;
	std::string sentence_link = sentence;

	for (unsigned int i = 0; i < sentence.size(); i ++){
			
			if (sentence[i] == 41){
				sentence[i] = ' ';
				counter = 0;
			}
			else if (counter == 1){
				sentence[i] = ' ';
			}
			else if(sentence[i] == 91 || sentence[i] == 93)
			{
				sentence[i] = ' ';
			}
			else if (sentence[i] == 40){
				sentence[i] = ' ';
				counter = 1;
			}
			else if (!char_checker(sentence[i])){
				sentence[i] = ' ';
			}

			if(counter == 0 || sentence_link[i] == 40 || sentence_link[i] == 41){
					sentence_link[i] = ' ';
				
			}
		}
		std::stringstream sss2(sentence_link);
		std::string insert_link;
		while(sss2 >> insert_link){
			link.push_back(insert_link);
		}
}

// parse the webapapge
void file_parser(std::string filepath, std::vector<std::string> &outgoing_link){

		std::ifstream webpage_ifile;
		webpage_ifile.open(filepath);
		std::string content;
		while(getline(webpage_ifile,content)){
			string_parser(content, outgoing_link);
		}

}

// reversely push the vector to the stack
void stack_pusher(std::stack<std::string> &stack_link, std::vector<std::string> &vector_link, std::set<std::string> &set_link){
	int size = vector_link.size();
	for (int i = size-1; i >= 0; i--){

		std::set<std::string>::const_iterator it1;
  		it1 = find(set_link.begin(), set_link.end(), vector_link[i]);
  		if(it1 == set_link.end()){
  				stack_link.push(vector_link[i]);
  		}
	}
}



// the main function to realise the DFS on the webpages to output the right index file

int main(int argc, char *argv[]){

	map<string,set<string>> string_map;

	std::string index;
	std::string query;
	std::string output;

	if(argc > 2){
		cerr << "The input arguments are not correct";
	}
	else{
	
		std::ifstream ifile;
		if(argc == 1){
			ifile.open("config.txt");
		}
		else if(argc == 2){
			ifile.open(argv[1]);
		}
		std::string content;
		while(getline(ifile,content)){
			std::stringstream ss(content);
			std::string name_of;
			std::string final="";
			while(ss >> name_of){
				if(name_of == "#" || name_of[0] =='#'){
					break;
				}
				else if (name_of[name_of.size()-1] == '#'){
					name_of[name_of.size()-1] = ' ';
					final += name_of;
				}
				else{
					final += name_of;
				}
			}	
			for (unsigned int i = 0; i < final.size(); i++){
				if(final[i] == '='){
					final[i] = ' ';
				}
			}
			std::string first;
			std::string second;
			std::stringstream sss(final);
			sss >> first;
			sss >> second;
			if(first == "INDEX_FILE"){
				index = second;
			}
			else if (first == "QUERY_FILE"){
				query = second;

			}
			else if (first == "OUTPUT_FILE"){
				output = second;
			}
		}


		std::ofstream index_ofile;
		index_ofile.open(output);

		std::stack <std::string> stack_page;
		std::set <std::string> visited_page;

		std::vector<std::string> vec;

		std::ifstream index_ifile;
		index_ifile.open(index);
		std::string con;

		// DFS search through the webpages
		while(getline(index_ifile,con)){
		std::stringstream ssss(con);
		std::string name;
			while(ssss >> name ){
				vec.push_back(name);
			}	
		}
		stack_pusher(stack_page,vec,visited_page);


		while (!stack_page.empty()){
			std::string v = stack_page.top();
		
			stack_page.pop();


			std::set <std::string>::const_iterator it;
			it = find(visited_page.begin(),visited_page.end(),v);
			if(it == visited_page.end()){
				ifstream myFile(v);
    				if(!myFile.fail()){
    					index_ofile << v << std::endl;
    			}
				
				visited_page.insert(v);
			}
			std::vector<std::string> vector_l;
			file_parser(v,vector_l);
			stack_pusher(stack_page,vector_l,visited_page);
		}
		


	}
}









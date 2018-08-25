
//#ifndef WEBPAGE.H
//#define WEBPAGE.H



#include <iostream>
#include <string>  
#include <map>
#include <set>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include<stdlib.h>
#include<stdio.h>

class WebPage{
public:

	WebPage();


	~WebPage();
	bool char_checker(char);
	void set_name(std::string name);
	std::string get_name();
	void string_parser(std::string sentence, std::set<std::string> & word,
		std::vector<std::string>& link,std::set<WebPage*> &webpage ,std::string filepath,std::set<std::string> &all_word);
	void file_parser(std::string filepath,std::set<WebPage*> &webpage,std::set<std::string> &all_word);


	std::set<std::string> get_word();
	std::vector<std::string> get_outgoing_link();
	std::vector<std::string> get_incoming_link();
	std::string to_lower(std::string st);

	bool word_finder(std::string);

	//void set_incoming_link(string );
private:
	std::string web_name;
	std::set<std::string> parsed_word;
    std::vector<std::string> incoming_link;
    std::vector<std::string> outgoing_link;

};

//#endif
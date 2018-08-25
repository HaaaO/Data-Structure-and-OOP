//#ifndef DATABASE.H
//#define DATABASE.H

#include "webpage.h"




class DataBase{

public:
	DataBase(std::string);
	~DataBase();

	void set_filename(std::string );
	std::string  get_filename();

	void parse(std::string input_file);
	//void query(std::string query_file, std::string output_file);

	std::set<WebPage*> get_webpage();
	std::set<std::string> get_all_word();
	std::map<std::string,std::set<std::string>> get_string_map();
	std::map<std::string, WebPage*> get_webpage_map();
	bool word_finder(std::string wor);
	bool webpage_finder(std::string pag);
	std::set<std::string> string_intersect(std::set<std::string> set1, std::set<std::string> set2);
	std::set<std::string> string_union(std::set<std::string> set1, std::set<std::string> set2);
	void page_print(WebPage* page);
	bool print_checker(std::string sentence);
	void print_page(std::string name_page, std::ofstream &out);
	void query(std::string query_file, std::string output_file);
	std::string to_lower(std::string st);





private:
	std::string index_file_name;
	std::map<std::string,std::set<std::string>> string_map;
	std::map<std::string, WebPage*> webpage_map;
	std::set<std::string> all_word;
	std::set<WebPage*> all_webpage;

};


//#endif
#include "database.h"



DataBase::DataBase(std::string file_name){
	index_file_name= file_name;
}



DataBase::~DataBase(){


}



void DataBase::set_filename(std::string name){
	index_file_name = name;


}
std::string  DataBase::get_filename(){
	return index_file_name;
}

std::string DataBase::to_lower(std::string st){
	for(unsigned int i = 0; i < st.size(); i++){
		if(st[i] <= 90 && st[i] >=65){
			st[i] += 32;
		}
	}
return st;
}

void DataBase::parse(std::string input_file){

	std::ifstream database_ifile;
	database_ifile.open(input_file);
	std::string content;
	while(getline(database_ifile,content)){
		std::stringstream ssss(content);
		std::string name_of;
			while(ssss >> name_of ){
				WebPage* page = new WebPage;
				page->set_name(name_of);
				all_webpage.insert(page);
			}	
	}

	std::set<WebPage*>::const_iterator it;

	for (it = all_webpage.begin(); it != all_webpage.end(); ++it) {
    	(*it)->file_parser((*it)->get_name(), all_webpage , all_word);
  	}

  	std::set<std::string>::const_iterator it1;

  	for (it1 = all_word.begin(); it1 != all_word.end(); ++it1) {
  		std::string word_name;
  		word_name = *it1;
  		std::set<std::string> mySet;

  		std::set<WebPage*>::const_iterator it2;
  		for (it2 = all_webpage.begin(); it2 != all_webpage.end(); ++it2) {
  			if((*it2)->word_finder(word_name)){
  				mySet.insert((*it2)->get_name());
  			}
  		}

  		string_map.insert(std::pair<std::string,std::set<std::string>>(word_name, mySet));
  	}

  	std::set<WebPage*>::const_iterator it2;
  	for (it2 = all_webpage.begin(); it2 != all_webpage.end(); ++it2) {

  		webpage_map.insert(std::pair<std::string, WebPage*>((*it2)->get_name(), *it2));
  	}




}

std::set<WebPage*> DataBase::get_webpage(){
	return all_webpage;
}

std::set<std::string>  DataBase::get_all_word(){
	return all_word;
}

std::map<std::string,std::set<std::string>> DataBase::get_string_map(){
	return string_map;

}

std::map<std::string, WebPage*> DataBase::get_webpage_map(){
	return webpage_map;
}

bool DataBase::word_finder(std::string wor){
	bool result = false;
	std::set<std::string>::const_iterator it1;

  	for (it1 = all_word.begin(); it1 != all_word.end(); ++it1) {
  		if((*it1) == wor){
  			result = true;
  		}
  	}
  	return result;
}


bool DataBase::webpage_finder(std::string pag){
	bool result = false;
	std::set<WebPage*>::const_iterator it1;
  	for (it1 = all_webpage.begin(); it1 != all_webpage.end(); ++it1) {
  		if((*it1)->get_name() == pag){
  			result = true;
  		}
  	}
  	return result;
}


std::set<std::string> DataBase::string_intersect(std::set<std::string> set1, std::set<std::string> set2){

	std::set<std::string> result;

	std::set<std::string>::const_iterator it1;
  	for (it1 = set1.begin(); it1 != set1.end(); ++it1) {

  		std::set<std::string>::const_iterator it2;
  		it2 = set2.find(*it1);

  		if(it2 != set2.end()){
  			result.insert(*(it1));
  		}

	}
	return result;
}



std::set<std::string> DataBase::string_union(std::set<std::string> set1, std::set<std::string> set2){

	std::set<std::string> result;

	std::set<std::string>::const_iterator it1;
  	for (it1 = set1.begin(); it1 != set1.end(); ++it1) {
  		result.insert(*(it1));
	}

	std::set<std::string>::const_iterator it2;
  	for (it2 = set2.begin(); it2 != set2.end(); ++it2) {
  		result.insert(*(it2));
	}

	return result;
}
void DataBase::query(std::string query_file, std::string output_file){

	std::ifstream database_ifile;
	std::ofstream database_ofile;
	database_ifile.open(query_file);
	database_ofile.open(output_file);
	std::string request;
	while(getline(database_ifile,request)){
		std::stringstream sss(request);
		std::stringstream sss1(request);
		int co=0;
		std::string wor;
		while(sss1 >> wor){
			co++;
		}
		std::string order="";
		sss >> order;

		if(co == 0){
			database_ofile << "Invalid query" << std::endl;
		}
		else if(order == "AND" && co > 1){
			std::set<std::string> i1;
			std::set<std::string> i2;
			std::string word;
			sss >> word; 
			word = to_lower(word);
			i1 = string_map[word];
			while(sss >> word){

				i2 = string_map[to_lower(word)];
				i1 = string_intersect(i1,i2);
			}

			database_ofile << i1.size() << std::endl;

			std::set<std::string>::const_iterator it;

			for (it = i1.begin(); it != i1.end(); ++it) {
    			database_ofile << (*it) << std::endl;
			}
		}
		else if(order == "OR"&& co > 1){
			std::set<std::string> i1;
			std::set<std::string> i2;
			std::string word;
			sss >> word; 
			word = to_lower(word);
			i1 = string_map[word];
			while(sss >> word){
				
				i2 = string_map[to_lower(word)];
				i1 = string_union(i1,i2);
			
			}

			database_ofile << i1.size() << std::endl;

			std::set<std::string>::const_iterator it;

			for (it = i1.begin(); it != i1.end(); ++it) {
    			database_ofile << (*it) << std::endl;
			}
		}
		else if (order == "PRINT"	&& co > 1){
			std::string pag;
			sss >> pag;
			if(webpage_finder(pag)){
				database_ofile << pag << std::endl;
				print_page(pag,database_ofile);

			}
			else{
				database_ofile << "Invalid query" << std::endl;
			}
		}
		else if (order == "INCOMING"&& co > 1){
			std::string pag;
			sss >> pag;
			if(webpage_finder(pag)){

			WebPage* page = webpage_map[pag];
			std::vector<std::string> i_link;
			i_link = page->get_incoming_link();

			database_ofile << i_link.size() << std::endl;

			std::vector<std::string>::const_iterator itt;

			for (itt = i_link.begin(); itt != i_link.end(); ++itt) {
    			database_ofile << (*itt) << std::endl;
			}

			}
			else{
				database_ofile << "Invalid query" << std::endl;
			}


		}
		else if (order == "OUTGOING"&& co > 1){
			std::string pag;
			sss >> pag;
			if(webpage_finder(pag)){
			WebPage* page = webpage_map[pag];
			std::vector<std::string> i_link;
			i_link = page->get_outgoing_link();

			database_ofile << i_link.size() << std::endl;

			std::vector<std::string>::const_iterator itt;

			for (itt = i_link.begin(); itt != i_link.end(); ++itt) {
    			database_ofile << (*itt) << std::endl;
			}
			}
			else{
				database_ofile << "Invalid query" << std::endl;

			}
		}
		else{
			int count=0;
			std::string new_word;
			while(sss >> new_word){
				count++;
			}

			if(count == 0){
				std::set<std::string> i1;
				order = to_lower(order);
				i1 = string_map[order];
				database_ofile << i1.size() << std::endl;
				std::set<std::string>::const_iterator it;

				for (it = i1.begin(); it != i1.end(); ++it) {
    				database_ofile << (*it) << std::endl;
				}	


				
			}
			else{
				database_ofile << "Invalid query" << std::endl;
			}





		}

	}
}



bool DataBase::print_checker(std::string sentence){
	bool result = false;
	for(unsigned int i = 0; i < sentence.size(); i++){
		if(sentence[i] == 40 || sentence[i] == 41){
			result = true;
		}
	}
	return result;
}



void DataBase::print_page(std::string name_page, std::ofstream &out){
	std::ifstream print_ifile;
	print_ifile.open(name_page);
	std::string content="";
	while(getline(print_ifile,content)){
		while(print_checker(content)){
			int pos1 = -1;
			int pos2 = -1;
			for(unsigned int i = 0; i < content.size(); i++){
				if(content[i] == 40){
					pos1 = i;
				}
				else if (content[i] == 41){
					pos2 = i;
				}

				if(pos1 != -1 && pos2 != -1){
					content.erase(pos1, pos2 - pos1 +1);
					
					break;
				}
			}
		}
		out<< content << std::endl;

	}

}

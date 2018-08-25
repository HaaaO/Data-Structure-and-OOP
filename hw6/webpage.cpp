
#include "webpage.h"



WebPage::WebPage(){
	web_name = "";

}

WebPage::~WebPage(){

}

bool WebPage::char_checker(char word){

	if((word <=57 && word >= 48 ) || (word <=90 && word >= 65 ) || (word <=122 && word >= 97 )
		|| word ==  91 || word == 93 || word == 40 || word == 41
		){
		return true;
	}
	else{
		return false;
	}

}


void WebPage::set_name(std::string name){
	web_name = name;
}


std::string WebPage::get_name(){
	return web_name;
}

std::string WebPage::to_lower(std::string st){
	for(unsigned int i = 0; i < st.size(); i++){
		if(st[i] <= 90 && st[i] >=65){
			st[i] += 32;
		}
	}
return st;
}
void WebPage::string_parser(std::string sentence, std::set<std::string> & word,std::vector<std::string>& link,std::set<WebPage*> &webpage ,std::string filepath,std::set<std::string> &all_word ){

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
		std::stringstream sss(sentence);
		std::stringstream sss2(sentence_link);

		std::string insert_word;
		while(sss >> insert_word){
		insert_word = to_lower(insert_word);
		word.insert(insert_word);
		all_word.insert(insert_word);
		}

		std::string insert_link;
		while(sss2 >> insert_link){
			link.push_back(insert_link);
			std::set<WebPage*>::const_iterator it_web;

			for (it_web = webpage.begin(); it_web != webpage.end(); ++it_web) {

				if((*it_web)->get_name() == insert_link){
					
					(*it_web)->incoming_link.push_back(filepath);
				}

  				}


		}

}

void WebPage::file_parser(std::string filepath, std::set<WebPage*> &webpage , std::set<std::string>& all_word){

		std::ifstream webpage_ifile;
		webpage_ifile.open(filepath);
		std::string content;
		while(getline(webpage_ifile,content)){
			string_parser(content, parsed_word,outgoing_link, webpage, filepath, all_word);
		}

}

std::set<std::string> WebPage::get_word(){
	return parsed_word;


}


std::vector<std::string> WebPage::get_outgoing_link(){
	return outgoing_link;


}

std::vector<std::string> WebPage::get_incoming_link(){
	return incoming_link;
}

bool WebPage::word_finder(std::string target){

	bool answer = false;
	std::set<std::string>::const_iterator iterator;
	for (iterator = parsed_word.begin(); iterator != parsed_word.end(); ++iterator) {
    	if(*iterator == target){
    		answer = true;
    	}
  
	}
	return answer;
}











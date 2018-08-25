
#include "database.h"



using namespace std;


int main(int argc, char *argv[]){

	map<string,set<string>> string_map;

	if(argc > 2){
		cerr << "The input arguments are not correct";
	}
	else{
		std::ifstream ifile;
		if(argc ==2){
			ifile.open(argv[1]);
		}
		else if (argc == 1){
			ifile.open("config.txt");
		}

		std::string content;
		std::string index;
		std::string query;
		std::string output;
		int t;
		double theta;
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
			else if (first == "RESTART_PROBABILITY"){
				stringstream chan(second);
				chan >> theta;
			}
			else if (first == "STEP_NUMBER"){
				stringstream chan(second);
				chan >> t;
			}
		}

		
	DataBase* new_database = new DataBase(index);

	new_database->parse(index);
	new_database->query(query,output,t,theta);

//--------------------------valgrind clear-----------------------------------

		std::set<WebPage*> ak = new_database->get_webpage();

		std::set<WebPage*>::const_iterator it6;
		for (it6 = ak.begin(); it6 != ak.end(); ++it6) {

			delete (*it6);
    		
  
		}

		delete new_database;

	}
}









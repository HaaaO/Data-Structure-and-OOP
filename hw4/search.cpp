
#include "database.h"



using namespace std;


int main(int argc, char *argv[]){

	map<string,set<string>> string_map;

	if(argc > 4){
		cerr << "The input arguments are not correct";
	}
	else{

		DataBase* new_database = new DataBase(argv[1]);

		new_database->parse(argv[1]);
		new_database->query(argv[2],argv[3]);

//--------------------------valgrind clear-----------------------------------

		std::set<WebPage*> ak = new_database->get_webpage();

		std::set<WebPage*>::const_iterator it6;
		for (it6 = ak.begin(); it6 != ak.end(); ++it6) {

			delete (*it6);
    		
  
		}

		delete new_database;

	}
}









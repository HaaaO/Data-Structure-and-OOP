all: search crawler

search: search.cpp webpage.cpp webpage.h database.cpp database.h  setutility.h
	g++ -g -Wall -std=c++11 search.cpp webpage.cpp webpage.h database.cpp database.h setutility.h -o search

crawler:  crawler.cpp
	 g++ -g -Wall -std=c++11 crawler.cpp -o crawler

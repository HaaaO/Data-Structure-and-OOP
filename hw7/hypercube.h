#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional> 
#include <queue>
#include <sstream>

class Node 
{
public:
	Node(std::string val, int h);
	Node();
	 ~Node();
	int f_value;
	int g_value;
	int h_value;
	std::string predecessor;
	std::string value;
};


Node::Node(std::string val,int h){

	value = val;
	h_value = h;
	g_value = 0;
	f_value = 0;
}

Node::Node(){
	
}


Node::~Node(){

}
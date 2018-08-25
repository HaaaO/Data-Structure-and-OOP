
#include "compare.h"


bool visit(std::set<std::string> &visited, std::string &node){
	std::set<std::string>::iterator i1;
	i1 = visited.find(node);
	if(i1 != visited.end()){
		return true;
	}
	else{
		return false;
	}

}

bool available(std::set<std::string> &available, std::string &node){
	std::set<std::string>::iterator i1;
	i1 = available.find(node);
	if(i1 != available.end()){
		return true;
	}
	else{
		return false;
	}
}

int main(int argc, char *argv[]){

	std::priority_queue<Node, std::vector<Node>, Compare> pq;

	std::set<std::string> in_vec;
	std::set<std::string> visited;
	std::vector<Node> out_vec;

	std::string start = argv[1];
	std::string end = argv[1];

	for (unsigned int i = 0; i < end.size();i++){
		end[i]= '1';
	}

	int total_num;
	int expansion = 0;

	std::ifstream infile;
	infile.open(argv[2]);
	std::string line;
	getline(infile, line);
	std::stringstream first_line(line);
	first_line >> total_num;

	while(getline(infile, line)){
		std::stringstream ss(line);
		std::string node;
		ss >> node;

		in_vec.insert(node);	
	}

	Node start_node;

	int h = 0;
	for(unsigned int j = 0; j < start.size(); j++){
	if(start[j] == '0'){
		h++;
		}
	}

	start_node.value = start;
	start_node.h_value = h;
	start_node.g_value = 0;
	start_node.f_value = start_node.g_value + start_node.h_value;
	start_node.predecessor = start_node.value;

	pq.push(start_node);
	bool final_checker = false;

	while(!pq.empty()){
		Node top = pq.top();

		out_vec.push_back(top);

		if(top.value == end){
			final_checker = true;
			break;
		}
		
		pq.pop();


		if(!visit(visited, top.value)){
			expansion++;

			visited.insert(top.value);
	

		for (unsigned int k = 0; k < top.value.size(); k++){
			std::string new_value = top.value;
			if(new_value[k] == '0'){
				new_value[k] = '1';
			}
			else{
				new_value[k] = '0';
			}

			if(available(in_vec, new_value)){
				int h = 0;
				for(unsigned int j = 0; j < new_value.size(); j++){
					if(new_value[j] == '0')
						{
							h++;
						}
				}
				Node new_node(new_value,h);
				new_node.g_value= top.g_value +1;
				new_node.f_value = new_node.g_value +new_node.h_value;
				new_node.predecessor = top.value;
				pq.push(new_node);

			}

			}

		}

	}

	if(final_checker){
		int size_vec = out_vec.size();
	Node output_node = out_vec[size_vec-1];
	std::vector<std::string> final_vec;

	while(output_node.predecessor != output_node.value){
		final_vec.push_back(output_node.value);
		for(int n =0; n < size_vec; n++){
			if(out_vec[n].value == output_node.predecessor){
				output_node = out_vec[n];
				break;
			}

		}
	}
	final_vec.push_back(output_node.value);

	for (int i = final_vec.size()-1; i >= 0 ; i--){
		std::cout << final_vec[i]  << std::endl;
	}
	std::cout << "expansions = "<<expansion<< std::endl;

	}
	else{
		std::cout << "No transformation" << std::endl;
		std::cout << "expansions = "<<expansion<< std::endl;
	}
	








}





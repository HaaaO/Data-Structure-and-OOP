#include "lliststr.h"
#include "stackstr.h"
#include <iostream>
#include <string>  
#include <fstream>
#include <sstream>
#include<bits/stdc++.h>

using namespace std;


// checker for chekcing whether the character is valid
bool char_checker(char word){
	if((word <=122 && word >= 97 ) || word == 43 || word == 45 
		|| word ==  40 || word == 41 || word == 60 || word == 62
		){
		return true;
	}
	else{
		return false;
	}
}

// when it only has the string with'<' or ">"
// evaluate it in this function
// mal_ch is to check whther it's malformed
string stack_last_evaluate(string in, bool &mal_ch){
	string result= "";
	bool ch_operator = false;
	bool ch_variable = false;
	for (unsigned int i = 0; i < in.size(); i++)
	{
		if(in[i] == '<')
		{	
			ch_operator = true;
			if(result.size() > 1)
			{
				result.erase(0,1);
			}
			if (ch_variable == false){
				mal_ch = true;
			}
		}
		else if (in[i] == '>'){
			ch_operator = true;
			if(result.size() > 1)
			{
				result.erase(result.size()-1,1);
			}
			if (ch_variable == false){
				mal_ch = true;
			}
		}
		else {
			result += in[i];
			ch_variable = true;
			if (ch_operator == true){
				mal_ch = true;
			}
		}
	}
	return result;
}

// the main evluation function to pop the string out
// when it detect a "()"
string stack_evaluate(StackStr &st, bool &mal_ch){
	string final_evaluated_str = "";
	string str_eva = "";
	while(st.top() != "("){
		str_eva += st.top();
		st.pop();
	}
	int counter_minus = 0;
	for (unsigned int k = 0; k < str_eva.size(); k++ ){
		if(str_eva[k] == '-')
			counter_minus++;
		}


	if(counter_minus > 1){
		mal_ch = true;
		return "";

	}

	if((str_eva.find("+") != std::string::npos) && 
		(str_eva.find("-") != std::string::npos)){
		mal_ch = true;
		return "";
	}



	if((str_eva.find("+") == std::string::npos) &&
	 (str_eva.find("-") == std::string::npos)){
		mal_ch = true;
		return "";
	}

	if(str_eva[0] == '+' || str_eva[str_eva.size()-1] == '+'){
		mal_ch = true;
		return "";
	}

	if(str_eva[0] == '-' || str_eva[str_eva.size()-1] == '-'){
		mal_ch = true;
		return "";
	}

	if (str_eva.find("+") != std::string::npos){
		int num_pluse = 0;
		for (unsigned int j = 0; j < str_eva.size(); j++){
			if(str_eva[j] == '+')
			{
				num_pluse++;
			}
		}

		for (unsigned int j = 0; j < str_eva.size(); j++){
			if(str_eva[j] == '+')
			{
				if(str_eva[j-1] =='+' || str_eva[j+1] =='+'){
					mal_ch = true;
					return "";


				}
			}
		}

		
		string* arr = new string[num_pluse+1];
		stringstream sss(str_eva);
		int chk = 0;
		while(sss){
			if(!getline(sss,arr[chk],'+'))
				break;
			chk++;
		}

		for (int i = 0; i < num_pluse+1; i++){
			arr[i] = stack_last_evaluate(arr[i],mal_ch);
		}
		string final= "";
		
		for (int i = 0; i < num_pluse+1; i++){
			final += arr[i];
		}

		delete [] arr;

		final_evaluated_str = final;
		
	}
	else if (str_eva.find("-") != std::string::npos){

		string arr[2];
		stringstream sss(str_eva);
		int chk = 0;
		while(sss){
			if(!getline(sss,arr[chk],'-'))
				break;
			chk++;
		}
		arr[0] = stack_last_evaluate(arr[0],mal_ch);
		arr[1] = stack_last_evaluate(arr[1],mal_ch);

		reverse(arr[0].begin(), arr[0].end());
		reverse(arr[1].begin(), arr[1].end());


		std::size_t found = arr[1].find(arr[0]);

		if (arr[0] == arr[1]){
			mal_ch = true;
			return "";
		}

		if ((found != std::string::npos) )
		{
			arr[1].erase(found,arr[0].size());
		}
		reverse(arr[1].begin(), arr[1].end());
		final_evaluated_str = arr[1];
	}
	return final_evaluated_str;
	
}

// an outside malformed checker to check prevdious
// unvalid cases
bool mal_checking (string str_ch){
	StackStr stack;
	int add_count = 0;
	int minus_count = 0;
	int left_count = 0;
	int right_count = 0;
    bool return_mal = false;
	for (unsigned int i = 0; i < str_ch.size(); i ++){
		if(str_ch[i] == '('){
			left_count ++;
		}
		else if (str_ch[i] == ')')
		{
			right_count ++;
		}
		else if (str_ch[i] == '+'){
			add_count++;
		}
		else if (str_ch[i] =='-'){
			minus_count--;
		}
		if (!char_checker(str_ch[i]))
		{
			return_mal = true;
		}

		if(left_count == 0 && right_count > 0){
			return_mal = true;
		}


	}

	if(str_ch.size() > 1){

	for(unsigned int p = 1; p < str_ch.size()-1;  p++ ){
		if(str_ch[p] == '('){
			if(str_ch[p-1] <= 122 && str_ch[p-1] >=97){
				return_mal= true;
			}
			if(str_ch[p-1] == ')' || str_ch[p+1] == ')')
			{
				return_mal =true;
			}

		}

		if( str_ch[p]== ')'){
			
			if(str_ch[p+1] <= 122 && str_ch[p+1] >=97){
				return_mal= true;
			}
			if(str_ch[p+1] == '(' || str_ch[p-1] == '(')
			{
				return_mal =true;
			}

		}
	}
}
		if(right_count != left_count){
		return_mal = true;
		}

		if (right_count == 0 && left_count == 0 &&
		 (add_count!=0 || add_count!=0))
		{
			return_mal = true;
		}
	  return return_mal;
}

// the main function to do the read and write 
// call stack_evaluate or stack_last_evaluate when
//necessary

int main(int argc, char *argv[]){
	StackStr string_stack;

	ifstream infile;
	ofstream outfile;
	infile.open(argv[1]);
	outfile.open(argv[2]);
	string line;
	while(getline(infile, line)){
	
		
		stringstream ss(line);

		int left_count = 0;
		int right_count = 0;
		bool mal_checker = false;

		string str_for_stack = "";
		string temp = "";
		while (	ss >> temp){
		str_for_stack += temp;
		}

		if(mal_checking(str_for_stack))
		{
			outfile << "Malformed" << endl;
			continue;
		}

		int stack_size = int(str_for_stack.size());

		if(stack_size == 0){
			outfile << "Malformed" << endl;
			continue;
		}

	
		for (int i = 0; i < stack_size; i++){
			stringstream ss1;
			string str_cha;
			ss1 << str_for_stack[i];
			ss1 >> str_cha;
			if(char_checker(str_for_stack[i])){
				if(str_cha == "(")
				{
					left_count++;
					string_stack.push(str_cha);
				}
				else if (str_cha == ")")
				{
					right_count++;
					string s;
			    	s = stack_evaluate(string_stack,mal_checker);
			    	string_stack.pop();
			    	for (int j = int(s.size()) -1; j >= 0; j--){
			    	stringstream ss2;
					string str_cha2;
					ss2 << s[j];
					ss2 >> str_cha2;
					string_stack.push(str_cha2);
					}		

				}
				else{
					string_stack.push(str_cha);
				}
		
			}
			else{
				mal_checker = true;
			}

		}
		if (left_count!=right_count){
			mal_checker =true;
		}

		int final_size = string_stack.size();
		string r_str = "";
		for (int z = 0; z < final_size; z ++ )
		{
			r_str += string_stack.top();
			string_stack.pop();
		}

		for (unsigned int q = 0; q < r_str.size(); q++){
			if(r_str[q] == '-'||r_str[q] == '+'){
				mal_checker = true;
			}
		}

		string result_str = "";
		result_str = stack_last_evaluate(r_str,mal_checker);
		reverse(result_str.begin(),result_str.end());

		if (mal_checker){
			outfile << "Malformed" << endl;
		}
		else{
		outfile << result_str << endl;
		}	
	}

	infile.close();

}
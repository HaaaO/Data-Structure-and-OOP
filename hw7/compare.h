#include "hypercube.h"
#include<cmath>
#include <set>


class Compare
{
public:
    bool operator() (const Node &lhs,const Node & rhs)
    {
        bool result;
        if(lhs.f_value != rhs.f_value){
        	result = lhs.f_value > rhs.f_value;
        }
        else{
        	if(lhs.h_value != rhs.h_value){
        	//	std::cout << "compare h" << lhs.h_value  << " " <<  lhs.h_value << std::endl;
        		result = lhs.h_value > rhs.h_value;
        	}
        	else{
        	//	std::cout << "compare integer" << toInteger(lhs.value)  << " " <<  toInteger(rhs.value) << std::endl;
        		for(unsigned int i =0; i < lhs.value.size(); i++){
        			if(lhs.value[i] != rhs.value[i]){
        				if(lhs.value[i] == '1'){
        					result = true;
        					break;
        				}
        				else{
        					result = false;
        					break;
        				}
        			}
        		}
        	}

        }
        return result;
    }
};
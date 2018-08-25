#include "functor.h"



    int NumStrComp::get_value(char ch){
      int value;

      if(ch >= 48 && ch <=57){
        value =  int(ch) -48;
      }
      else if (ch >=65 && ch <= 90){
        value =  int(ch) - 55;
      }
      else if (ch >=97 && ch <= 122){
        value = int(ch) - 87;
      }
      else{
        value = 0;
      }
      return value;
    }

    bool NumStrComp::operator()(const std::string& lhs, const std::string& rhs)
    {
      int sum_l = 0;
      int sum_r = 0;
      for (unsigned int i = 0; i < lhs.size(); i++){
        sum_l += get_value(lhs[i]);
      }
      for (unsigned int i = 0; i < rhs.size(); i++){
        sum_r += get_value(rhs[i]);
      }
      if(sum_l > sum_r){
        return sum_l < sum_r;
      }
      else if (sum_l < sum_r){
        return sum_l < sum_r;
      }
      else{
        return lhs < rhs;
      }
    }
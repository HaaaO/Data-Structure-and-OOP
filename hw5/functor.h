
#include <string>
#include <iostream>

class NumStrComp{

  public:
    int get_value(char ch);
    bool operator()(const std::string& lhs, const std::string& rhs);

};





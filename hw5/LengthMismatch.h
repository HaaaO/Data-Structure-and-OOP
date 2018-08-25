
#include <stdexcept>
#include <iostream>



class LengthMismatch: public std::exception 
{
public:
  LengthMismatch(int i,int j);
  virtual const char* what() const noexcept;
private:
  std::string msg;
};